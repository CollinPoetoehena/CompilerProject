/**
 * @file
 *
 * Traversal: CreateFunctionSymbolTableEntries
 * UID      : CFS
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums, for the Type and SymbolTableType
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

// Two scopes for basic: Program and FunBody
int currentScope = 0; // Start at global scope
// Used to fill the Program symbol table for Functions
node_st *firstSymbolTable = NULL;

// Check for argument numbers matching parameter numbers
bool compareFunCallArgumentsLength(node_st *funcallNode, node_st *steLink) {
    // Get the parameter count
    int parameterCount = 0;
    // Get the first param from the Ste
    node_st *paramIterator = STE_PARAMS(steLink);
    do {
        // Increment parameter count
        parameterCount++;

        // Update parameter
        paramIterator = PARAM_NEXT(paramIterator);
    } while (paramIterator != NULL);

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
    } else {
        // Not equal arguments and parameter numbers
        return false;
    }
}

/**
 * @fn CFSprogram
 */
node_st *CFSprogram(node_st *node)
{
    // TODO: function is the same as previous, but then in separate symbol table for function
    return node;
}

/**
 * @fn CFSfundef
 */
node_st *CFSfundef(node_st *node)
{
    return node;
}

/**
 * @fn CFSparam
 */
node_st *CFSparam(node_st *node)
{
    printf("param\n");

    // TODO: convert to new implementation, you can probably reuse a lot or almost all from the previous CA traversal!

    // Use the previousSymbolTable because that is the FunDef which contains the params
    // If it is not null it contains the LinkedList of type Param from the FunDef
    // if (STE_PARAMS(previousSymbolTable) != NULL) {
    //     // Get the first param from the Ste
    //     node_st *paramIterator = STE_PARAMS(previousSymbolTable);
    //     do {
    //         // Create a symbol table entry for param (link it later in the Var, Varlet and Funcall)
    //         createSymbolTableEntry(PARAM_NAME(paramIterator), PARAM_TYPE(paramIterator), STT_var, NULL);

    //         // Update symbolTable
    //         paramIterator = PARAM_NEXT(paramIterator);
    //     } while (paramIterator != NULL);
    // }

    // // If this param has a next, do the same for the next param in the function definition
    // TRAVnext(node);

    return node;
}

/**
 * @fn CFSfuncall
 */
node_st *CFSfuncall(node_st *node)
{
    return node;
}

