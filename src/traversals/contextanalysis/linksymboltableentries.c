/**
 * @file
 *
 * Traversal: LinkSymbolTableEntries
 * UID      : LSTE
 *
 *
 */

// Include enums and types, for the Type
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

// These node are used for searching the global Ste's
node_st *globalFirstSteVarLinking = NULL;
node_st *globalFirstSteFunLinking = NULL;

// These node are used for searching the fundef Ste's
node_st *fundefFirstSteVarLinking = NULL;
node_st *fundefFirstSteFunLinking = NULL;

// This helper VarDecl node is used for checking if a Var is the same as the declaration (then use global var first)
node_st *currentVarDeclNode = NULL;

// Helper to avoid code duplication. Returns the name of an Ste
char *getSteName(node_st *steNode, char *steType) {
    if (strcmp("var", steType) == 0) {
        return STEVAR_NAME(steNode);
    } else {
        return STEFUN_NAME(steNode);
    }
}

// Helper to avoid code duplication. Returns the next Ste
node_st *getNextSte(node_st *steNode, char *steType) {
    if (strcmp("var", steType) == 0) {
        return STEVAR_NEXT(steNode);
    } else {
        return STEFUN_NEXT(steNode);
    }
}

// Helper to avoid code duplication. Returns a found Ste node or NULL if no match is found
node_st *findSteNodeInSteChain(node_st *firstChainSte, char *name, char *steType) {
    node_st *steIterator = firstChainSte;
    do {
        // Match found, return Ste node. Use string comparison 
        // to check for equality, 0 means equal. == only checks if memory references are equal
        char *tempSteName = getSteName(steIterator, steType);
        // Add NULL check to avoid Segmentation fault
        if (tempSteName != NULL && strcmp(tempSteName, name) == 0) {
            // Return Ste found, automatically stops the execution of this function with the return
            return steIterator;
        }

        // Update steIterator
        steIterator = getNextSte(steIterator, steType);
    } while (steIterator != NULL);

    // No link found
    return NULL;
}

// Find an Ste node that has the specified name
node_st *findSteLink(char *name, char *steType) {
    // Create pointers and use a parameter steType to avoid creating two almost the same functions
    node_st *firstSteFunDefChain = NULL;
    node_st *firstSteGlobalChain = NULL;

    if (strcmp("var", steType) == 0) {
        // Set to SteVar chain
        firstSteFunDefChain = fundefFirstSteVarLinking;
        firstSteGlobalChain = globalFirstSteVarLinking;
    } else {
        // Set to SteFun chain
        firstSteFunDefChain = fundefFirstSteFunLinking;
        firstSteGlobalChain = globalFirstSteFunLinking;
    }

    /*
    If the current VarDecl is not equal to NULL and the name of the VarDecl is equal
    equal to 0 (means the name of the ste link and the VarDecl name are equal), 
    then skip the current fundef chain and search in the global chain only!
    If not:
    First search in the fundef chain because you want the closest Ste to be linked.
    If it is not in the current fundef chain, then search in the global chain.
    If it is not in the global chain then give an error that there is no link found!
    */
    if (currentVarDeclNode != NULL && strcmp(VARDECL_NAME(currentVarDeclNode), name) == 0) {
        // Search in the global chain only, skip searching in the current fundef chain
        if (firstSteGlobalChain != NULL) {
            node_st *foundSteNodeInChain = findSteNodeInSteChain(firstSteGlobalChain, name, steType);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }
    } else {
        // First search in the current FunDef chain
        if (firstSteFunDefChain != NULL) {
            node_st *foundSteNodeInChain = findSteNodeInSteChain(firstSteFunDefChain, name, steType);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }

        // Search in the global chain if fundef chain is NULL or symbol not found there
        // If the return statement of the previous search is not called it will get to this part
        if (firstSteGlobalChain != NULL) {
            node_st *foundSteNodeInChain = findSteNodeInSteChain(firstSteGlobalChain, name, steType);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }
    }
    

    // No existing symbol found, return NULL
    return NULL;
}

// Check for argument numbers matching parameter numbers
bool compareFunCallArgumentsLength(node_st *funcallNode, node_st *steLink) {
    // Get the parameter count
    int parameterCount = 0;
    // If the arguments are NULL, then the parameterCount should remain 0
    if (STEFUN_PARAMS(steLink) != NULL) {
        // Get the first param from the SteFun node
        node_st *paramIterator = STEFUN_PARAMS(steLink);
        do {
            // Increment parameter count
            parameterCount++;

            // Update parameter
            paramIterator = PARAM_NEXT(paramIterator);
        } while (paramIterator != NULL);
    }

    // Get the count of the arguments in the funcall node
    int argumentsCount = 0;
    if (FUNCALL_ARGS(funcallNode) != NULL) {
        // Get the first param from the Ste
        node_st *funcallArgsIterator = FUNCALL_ARGS(funcallNode);
        do {
            // Increment parameter count
            argumentsCount++;

            // Update parameter
            funcallArgsIterator = EXPRS_NEXT(funcallArgsIterator);
        } while (funcallArgsIterator != NULL);
    }

    if (parameterCount == argumentsCount) {
        // Equal arguments and parameter numbers
        return true;
    }
    
    // Not equal arguments and parameter numbers
    return false;
}

/**
 * @fn LSTEprogram
 */
node_st *LSTEprogram(node_st *node)
{
    // Save global Ste's to search in later in the linking process
    globalFirstSteVarLinking = PROGRAM_FIRST_STE_VARIABLES(node);
    globalFirstSteFunLinking = PROGRAM_FIRST_STE_FUNCTIONS(node);

    // Go to the traversal functions of the children
    TRAVchildren(node);

    return node;
}

/**
 * @fn LSTEfundef
 */
node_st *LSTEfundef(node_st *node)
{
    // Save the temp Ste's to search in later in the linking process
    fundefFirstSteVarLinking = FUNDEF_FIRST_STE_VARIABLES(node);
    fundefFirstSteFunLinking = FUNDEF_SYMBOL_TABLE(node);
    
    // Go to the traversal functions of the children (nodes that need to be linked)
    TRAVchildren(node);

    // Reset temp global variables for next fundef
    fundefFirstSteVarLinking = NULL;
    fundefFirstSteFunLinking = NULL;

    return node;
}

/**
 * @fn LSTEfuncall
 */
node_st *LSTEfuncall(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteLink(FUNCALL_NAME(node), "fun");
    if (steNode != NULL) {
        // If the arguments and parameter numbers are not equal, then error
        if (!compareFunCallArgumentsLength(node, steNode)) {
            // Prints the error when it occurs, so in this line
            CTI(CTI_ERROR, true, "argument numbers for function '%s' do not match parameter numbers", FUNCALL_NAME(node));
            // Create error action, will stop the current compilation after this Action (contextanalysis traversal)
            CCNerrorAction();
        } else {
            // Save Ste node in link attribute
            FUNCALL_STE_LINK(node) = steNode;
        }
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "no matching declaration/definition for funcall: %s", FUNCALL_NAME(node));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    // Go to the traversal functions of the args (Exprs node type) to traverse the parameters
    TRAVargs(node);

    return node;
}

/**
 * @fn LSTEvardecl
 */
node_st *LSTEvardecl(node_st *node)
{
    // Update the current vardecl node
    currentVarDeclNode = node;

    // Traverse the init Expr to find potential links
    TRAVinit(node);

    // Then traverse the next VarDecl node
    TRAVnext(node);

    // Reset the currentVarDeclNode to NULL at the end to not link it unnecessary later
    currentVarDeclNode = NULL;

    // TODO: after this fixing of the scopes, test everything thorougly again with the Regular Assignments
    // do this with every file and see if the linking is good, then after only seeing the linking
    // do it all over again without the linking to see if everything else works

    return node;
}

/**
 * @fn LSTEvar
 */
node_st *LSTEvar(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteLink(VAR_NAME(node), "var");
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VAR_STE_LINK(node) = steNode;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "no matching declaration/definition for var: %s", VAR_NAME(node));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn LSTEvarlet
 */
node_st *LSTEvarlet(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteLink(VARLET_NAME(node), "var");
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VARLET_STE_LINK(node) = steNode;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "no matching declaration/definition for varlet: %s", VARLET_NAME(node));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }
    
    return node;
}