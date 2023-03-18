/**
 * @file
 *
 * Traversal: LinkFunCallsToSteFunNode
 * UID      : LFTSF
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
node_st *globalFirstSteFunNode = NULL;

// Helper to avoid code duplication. Returns a found Ste node or NULL if no match is found
node_st *findSteFunNodeInSteChain(node_st *firstChainSte, char *name) {
    node_st *steIterator = firstChainSte;
    do {
        // Match found, return Ste node. Use string comparison 
        // to check for equality, 0 means equal. == only checks if memory references are equal
        char *tempSteName = STEVAR_NAME(steIterator);
        // Add NULL check to avoid Segmentation fault
        if (tempSteName != NULL && strcmp(tempSteName, name) == 0) {
            // Return Ste found, automatically stops the execution of this function with the return
            return steIterator;
        }

        // Update steIterator
        steIterator = STEVAR_NEXT(steIterator);
    } while (steIterator != NULL);

    // No link found
    return NULL;
}

// Find an Ste node that has the specified name
node_st *findSteFunLink(char *name) {
    /*
    With basic, the SteFun chain only has one scope: global (level 0), so
    there is only one chain that should be searched to find a SteFun link.
    */
    // Search in the global chain to find the FunDef SteFun link
    if (globalFirstSteFunNode != NULL) {
        node_st *foundSteNodeInChain = findSteFunNodeInSteChain(globalFirstSteFunNode, name);
        if (foundSteNodeInChain != NULL) {
            // Return Ste found, automatically stops the execution of this function with the return
            return foundSteNodeInChain;
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
 * @fn LFTSFprogram
 */
node_st *LFTSFprogram(node_st *node)
{
    // Save global Ste's to search in later in the linking process
    globalFirstSteFunNode = PROGRAM_FIRST_STE_FUNCTIONS(node);

    // Go to the traversal functions of the children
    TRAVchildren(node);

    return node;
}

/**
 * @fn LFTSFfuncall
 */
node_st *LFTSFfuncall(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteFunLink(FUNCALL_NAME(node));

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

    // Go to the traversal functions of the args (Exprs node type) to traverse the parameters (such as potential FunCall nodes)
    TRAVargs(node);
    // Var and VarLet nodes should already be linked in the traversal for creating SteVar entries and linking them!

    return node;
    
}