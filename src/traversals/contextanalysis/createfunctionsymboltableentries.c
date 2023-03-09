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
// Include enums, for the Type
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

// Two scopes for basic: Program and FunBody
int currentScopeFun = 0; // Start at global scope
// Used to fill the Program symbol table for Functions
node_st *firstSymbolTableFun = NULL;

// bool createSymbolTableEntry(char *name, enum Type type, node_st *params) 
// node_st *newSte = ASTstefun(NULL, NULL, name, type, currentScopeFun, params);

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

