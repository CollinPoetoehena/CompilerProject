/**
 * @file
 *
 * Traversal: UpdateGlobalVardeclScopes
 * UID      : UGVS
 *
 * 
 * This traversal is used to fix the scoping of the RegularAssignment traversal for Assign 
 * nodes. The scoping of Assign nodes is not correctly done in the above traversal because we
 * chose to do the RegularAssignment traversal before ContextAnalysis, these benefits outweigh the
 * drawbacks of having it after ContextAnalysis, however, to fix the scoping that is not 
 * correctly done because of that this traversal is needed to fix that.
 *
 * In short, the scopes of Var nodes (variables in Expressions) should be updated.
 * For example:
    int a;
    int b;
    void foo() {
        int a = a + a + 1;
        int c = a;
    }
 * This program will first be converted to split the initialization from the VarDecl node by
    the RegularAssignments traversal. Then after that the traversal for creating and linking
    the Ste's will be performed. However, the program will look like this when that is performed:
    int a;
    int b;
    void foo() {
        int a;
        int c;
        a = a + a + 1;
        c = a;
    }
 * So, after those traversal functions the scoping of the Ste links will be like this:
    int a; -> scope 0 SteVar
    int b; -> scope 0 SteVar
    void foo() { -> scope 0 SteFun
        int a; -> scope 1 SteVar
        int c; -> scope 1 SteVar
        a = a + a + 1; -> scope 1 link, scope 1 link, scope 1 link
        c = a; -> scope 1 link, scope 1 link
    }
 * But that is not what you want, this part "a = a + a + 1" ahould 
    link to the global scope level, so like this "a(1) = a(0) + a(0) + 1"
    with the scope level between (). This is because the original declaration had a 
    variable "a" that was refering to the global "a" because it was not initialized before the
    RegularAssignments traversal!
 * That is what this traversal should update and only that needs to be updated here, nothing else!
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

// This node is used for searching the global Ste's
node_st *globalFirstSymbolTableEntryVar = NULL;
// This variable is used to save the current assign node in for the hash table
node_st *currentAssignNode = NULL;
// This helper variable is used to also update the Var nodes in the same Assign node expression
bool isUpdating = false;

void UGVSinit() {
    // initialize hash table, ensures there is a hash table
    htable_st *hash_table = HTnew_String(100);

    // Get the hash table from the travdata of the UGVS traversal
    struct data_ugvs *data = DATA_UGVS_GET();
    data->assign_var_occurred = hash_table;

    return; 
}
void UGVSfini() {
    // Get the hash table from the travdata of the UGVS traversal
    struct data_ugvs *data = DATA_UGVS_GET();

    // Delete the hash table at the end of this traversal
    HTdelete(data->assign_var_occurred);

    return; 
}

// Helper to avoid code duplication. Returns a found Ste node or NULL if no match is found
node_st *findSteNodeInGlobalSteChain(char *name) {
    // First check if the global Ste chain exists, otherwise, do nothing and return NULL
    if (globalFirstSymbolTableEntryVar != NULL) {
            printf("GETTING HERE ! *****************\n");

        node_st *steIterator = globalFirstSymbolTableEntryVar;
        do {
            // Match found, return Ste node. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            char *tempSteName = STEVAR_NAME(steIterator);
            printf("name in find function: %s\n", tempSteName);
            // Add NULL check to avoid Segmentation fault
            if (tempSteName != NULL && strcmp(tempSteName, name) == 0) {
                // Return Ste found, automatically stops the execution of this function with the return
                return steIterator;
            }

            // Update steIterator
            steIterator = STEVAR_NEXT(steIterator);
        } while (steIterator != NULL);
    } else {
                    printf("GLOBAL CHAIN IS NULL ! *****************\n");

    }
    
    // No link found
    return NULL;
}

// TODO: remove after debugging
void * printElement(void * key, void * item) {
    // Dereference int with * operator, char * == type string
    printf("name in hash table: %s\n", (char *) key);

    // Return nothing to avoid warning
    return 0;
}

/**
 * @fn UGVSprogram
 */
node_st *UGVSprogram(node_st *node)
{
    // Save global Ste's to search in later in the linking process
    globalFirstSymbolTableEntryVar = PROGRAM_FIRST_STE_VARIABLES(node);
    printf("IS IT NULL IN PROGRAM, THE CHAIN?? %s\n", PROGRAM_FIRST_STE_VARIABLES(node) == NULL ? "true" : "false");

    // Go to the traversal functions of the children
    TRAVchildren(node);

    // TODO: remove after debugging
    // Get travdata from CI traversal
    struct data_ugvs *data = DATA_UGVS_GET();
    // Print hash table
    HTmapWithKey(data->assign_var_occurred, printElement);

    return node;
}

/**
 * @fn UGVSassign
 */
node_st *UGVSassign(node_st *node)
{
    // Save the current Assign node before traversing the assign expression
    currentAssignNode = node;

    TRAVexpr(node);
    printf("back from trav expr*****************\n");

    // After traversing the expression, set the isUpdating to false for the next Assign node
    isUpdating = false;

    return node;
}


/**
 * @fn UGVSvar
 */
node_st *UGVSvar(node_st *node)
{
    printf("var **************\n");

    // First check if the Var ste link is not at scope 0 (global scope does not need updating here)
    if (VAR_STE_LINK(node) != NULL && STEVAR_NESTING_LEVEL(VAR_STE_LINK(node)) != 0) {
        // Get the hash table from the travdata of the UGVS traversal
        struct data_ugvs *data = DATA_UGVS_GET();
        
        node_st *assignNodeFromVar = (node_st *) HTlookup(data->assign_var_occurred, VAR_NAME(node));

        /*
        Check if the Var is in the hash table, if it is, it means that it has occurred in a 
        previous assign node already, so it was not a VarDecl before.
        If it is not in the hash table, it means that it was from the original VarDecl and 
        it should therefore be updated to the SteVar from the global scope if it is in the global
        SteVar chain, if it is not in that chain, then not update anything.

        Or if the isUpdating variable is true, that means that this is still the sequence
        of the same Assign node, so also then update the link.
        */
        if (assignNodeFromVar == NULL || isUpdating) {
            printf("name: %s\n", VAR_NAME(node));
            node_st *globalSteLinkVar = findSteNodeInGlobalSteChain(VAR_NAME(node));
            // If it is not in the global chain, not update the link
            if (globalSteLinkVar != NULL) {
                printf("LINK UPDATED!********************\n");
                VAR_STE_LINK(node) = globalSteLinkVar;
            }

            // Set updating to true
            isUpdating = true;

            // If the assign node is NULL, then insert this one to not update future Assign node
            // because this was the first VarDecl of this node before the RegularAssignments traversal
            if (assignNodeFromVar == NULL) {
                HTinsert(data->assign_var_occurred, VAR_NAME(node), (void *) currentAssignNode);
            }
        } else {
            printf("IT IS NOT NULL IN VAR!*****************\n");
        }
    }

    return node;
}

