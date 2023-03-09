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

// Find an Ste node that has the specified name
// node_st *findSteLink(char *name) {
//     printf("Trying to find Ste for: %s\n", name);

//     //TODO: update this function to fix the finding, think of something smart to solve this, such as a list of 
//     // node_st *, with all the firstCurrentScopes of all the fundefs, then you can loop through them
//     // Or think of something else, you are free to decide, this may not be the best because you probably cannot
//     // make a list, so think of something else!

//     // return the Symbol table entry that is linked to this node (with name)
//     // Use linear search to find the entry, stop when next is NULL
//     if (firstSymbolTableVar != NULL) {
//         node_st *symbolTable = firstSymbolTableVar;
//         do {
//             // Match found, return Ste node. Use string comparison 
//             // to check for equality, 0 means equal. == only checks if memory references are equal
//             if (strcmp(STEVAR_NAME(symbolTable), name) == 0) {
//                 printf("**********************Link found for: %s\n", name);
//                 return symbolTable;
//             }

//             // Update symbolTable
//             symbolTable = STEVAR_NEXT(symbolTable);
//         } while (symbolTable != NULL);
//     }

//     printf("No link found for linking an Ste to a Var, VarLet or FunCall!\n");
//     // No existing symbol found, return NULL
//     return NULL;
// }

// Check for argument numbers matching parameter numbers
// bool compareFunCallArgumentsLength(node_st *funcallNode, node_st *steLink) {
//     // Get the parameter count
//     int parameterCount = 0;
//     // Get the first param from the Ste
//     node_st *paramIterator = STE_PARAMS(steLink);
//     do {
//         // Increment parameter count
//         parameterCount++;

//         // Update parameter
//         paramIterator = PARAM_NEXT(paramIterator);
//     } while (paramIterator != NULL);

//     // Get the count of the arguments in the funcall node
//     int argumentsCount = 0;
//     if (FUNCALL_ARGS(funcallNode) != NULL) {
//         // Get the first param from the Ste
//         node_st *funcallArgsIterator = FUNCALL_ARGS(funcallNode);
//         do {
//             // Increment parameter count
//             argumentsCount++;

//             // Update parameter
//             funcallArgsIterator = EXPRS_NEXT(funcallArgsIterator);
//         } while (funcallArgsIterator != NULL);
//     }

//     if (parameterCount == argumentsCount) {
//         // Equal arguments and parameter numbers
//         return true;
//     } else {
//         // Not equal arguments and parameter numbers
//         return false;
//     }
// }

/**
 * @fn LSTEprogram
 */
node_st *LSTEprogram(node_st *node)
{
    return node;
}

/**
 * @fn LSTEfundef
 */
node_st *LSTEfundef(node_st *node)
{
    return node;
}

/**
 * @fn LSTEfunbody
 */
node_st *LSTEfunbody(node_st *node)
{
    //TODO: need Stmts ifelse, while, etc for linking or do they already work fine when doing a = 5 for example, test!???
    return node;
}

/**
 * @fn LSTEfuncall
 */
node_st *LSTEfuncall(node_st *node)
{
    return node;
}

/**
 * @fn LSTEvar
 */
node_st *LSTEvar(node_st *node)
{
    // // Update this link from var to the Ste with the given name 
    // node_st *steNode = findSteLink(VAR_NAME(node));
    // if (steNode != NULL) {
    //     // Save Ste node in link attribute
    //     VAR_STE_LINK(node) = steNode;
    // } else {
    //     // Prints the error when it occurs, so in this line
    //     CTI(CTI_ERROR, true, "no matching declaration/definition for var: %s", VAR_NAME(node));
    //     // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
    //     CCNerrorPhase();
    // }

    printf("*************************symbol table link var\n");

    return node;
}

/**
 * @fn LSTEvarlet
 */
node_st *LSTEvarlet(node_st *node)
{
    // // Update this link from var to the Ste with the given name 
    // node_st *steNode = findSteLink(VARLET_NAME(node));
    // if (steNode != NULL) {
    //     // Save Ste node in link attribute
    //     VARLET_STE_LINK(node) = steNode;
    // } else {
    //     // Prints the error when it occurs, so in this line
    //     CTI(CTI_ERROR, true, "no matching declaration/definition for varlet: %s", VARLET_NAME(node));
    //     // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
    //     CCNerrorPhase();
    //     // TODP: UNCOMMENT
    // }
    
    printf("*************************symbol table link varlet\n");

    return node;
}

