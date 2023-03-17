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
    if (globalFirstSymbolTableEntryVar = NULL) {
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
    }
    
    // No link found
    return NULL;
}

/**
 * @fn UGVSprogram
 */
node_st *UGVSprogram(node_st *node)
{
    // Save global Ste's to search in later in the linking process
    globalFirstSymbolTableEntryVar = PROGRAM_FIRST_STE_VARIABLES(node);

    // Go to the traversal functions of the children
    TRAVchildren(node);

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

    // After traversing the expression, save the VarLet name in the hash table
    // so that a next assign with the same Var name will not be updated
    struct data_ugvs *data = DATA_UGVS_GET();
    HTinsert(data->assign_var_occurred, VARLET_NAME(ASSIGN_LET(node)), (void *) node);

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
        */
        if (assignNodeFromVar == NULL) {
            printf("name: %s\n", VAR_NAME(node));
            node_st *globalSteLinkVar = findSteNodeInGlobalSteChain(VAR_NAME(node));
            // If it is not in the global chain, not update the link
            if (globalSteLinkVar != NULL) {
                printf("LINK UPDATED!********************\n");
                VAR_STE_LINK(node) = globalSteLinkVar;
            }
        }
    }

    return node;
}

