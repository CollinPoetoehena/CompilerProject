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

// For fundefs there is only one scope for basic: global scope (0)
int currentScopeFun = 0; // Start at global scope

// firstSymbolTableVar is used to fill the Program symbol table for Variables
node_st *firstSymbolTableFun = NULL;
// lastSteVarGlobal is used to keep track of the last global Ste to use for appending to the LinkedList
node_st *lastSteFunGlobal = NULL;

// bool createSymbolTableEntrySteFun(char *name, enum Type type, node_st *params) 
// node_st *newSte = ASTstefun(NULL, NULL, name, type, currentScopeFun, params);

// Update the global symbol tables used for iterating over the Ste's
void updateGlobSymbolTablesSteFun(node_st *newSte) {
    if (firstSymbolTableFun == NULL) {
        firstSymbolTableFun = newSte;
        lastSteFunGlobal = newSte;
    } else {
        // Update next of previous symbol table
        STEVAR_NEXT(lastSteFunGlobal) = newSte;
        lastSteFunGlobal = newSte;
    }
}

// Check if a symbol is unique
bool isSymbolUniqueSteFun(char *name) {
    // Check if the name is not already present in the symbol table entries (use linear search)

    // Only one scope for basic for fundefs: global (0)
    node_st *symtbolTableChainFun = firstSymbolTableFun;
    // Go through the current chain to check if it contains the symbol already
    if (symtbolTableChainFun != NULL) {
        // TODO: remove after debugging
        // printf("\n\n\n\n\n\n\nPRINTING STE CHAIN IT IS SERACHING IN********************\n");
        // printSteVarChain(symtbolTableChainFun);
        do {
            // Symbol already present, return not unique/false. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STEFUN_NAME(symtbolTableChainFun), name) == 0) {
                printf("**********************Link found for %s\n", name);
                printf("First stefun that occured is: %s\n", STEFUN_NAME(symtbolTableChainFun));
                return false;
            }

            // Update symbolTable
            symtbolTableChainFun = STEVAR_NEXT(symtbolTableChainFun);
        } while (symtbolTableChainFun != NULL);
    }
    
    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

// Create a symbol table entry node, declared after helper functions, because otherwise it gives an error!
bool createSymbolTableEntrySteFun(char *name, enum Type type) {
    // First check if the name is already present, if so, save it in errors
    if (isSymbolUniqueSteFun(name)) {
        // Parent of fundefs is in basic always NULL, next is set later, so for now NULL
        node_st *newSte = ASTstevar(NULL, NULL, name, type, currentScopeFun);

        // Update global symbol tables in this traversal
        updateGlobSymbolTablesSteFun(newSte);

        // TODO: remove after debugging
        //printSteVar(newSte);

        // Ste creation succeeded
        return true;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "multiple matching declarations/definitions found for %s", name);
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    // Creation failed
    return false;
}

/**
 * @fn CFSprogram
 */
node_st *CFSprogram(node_st *node)
{
    // Go to the traversal functions of the children
    TRAVchildren(node);

    // Update Ste first occurrence of a global symbolTableEntry to put into the Program node
    if (firstSymbolTableFun != NULL) {
        PROGRAM_FIRST_STE_FUNCTIONS(node) = firstSymbolTableFun;
    }
    // If the firstSymbolTableFun is NULL, then no global symbol tables are created

    return node;
}

/**
 * @fn CFSfundef
 */
node_st *CFSfundef(node_st *node)
{
    // Create a new SteFun 
    // newSteFun = true;

    // Create a SteFun for this function definition
    createSymbolTableEntrySteFun(FUNDEF_NAME(node), FUNDEF_TYPE(node));

    // Then traverse the params to add to this Ste
    TRAVparams(node);

    // Reset the fundef for the next params
    // newSteFun = false;

    return node;
}

/**
 * @fn CFSparam
 */
node_st *CFSparam(node_st *node)
{
    printf("param\n");

    // Use the lastSteFunGlobal because that is the FunDef which contains the params
    // If it is not null it contains the LinkedList of type Param from the FunDef
    // if (STEFUN_PARAMS(lastSteFunGlobal) != NULL) {
    //     // Get the first param from the Ste
    //     node_st *paramIterator = STEFUN_PARAMS(lastSteFunGlobal);
    //     do {
    //         // Create a symbol table entry for param (link it later in the Var, Varlet and Funcall)
    //         createSymbolTableEntrySteFun(PARAM_NAME(paramIterator), PARAM_TYPE(paramIterator), STT_var, NULL);

    //         // Update symbolTable
    //         paramIterator = PARAM_NEXT(paramIterator);
    //     } while (paramIterator != NULL);
    // }

    // TODO: convert to new implementation, you can probably reuse a lot or almost all from the previous CA traversal!



    // Use the previousSymbolTable because that is the FunDef which contains the params
    // If it is not null it contains the LinkedList of type Param from the FunDef
    // if (STE_PARAMS(previousSymbolTable) != NULL) {
    //     // Get the first param from the Ste
    //     node_st *paramIterator = STE_PARAMS(previousSymbolTable);
    //     do {
    //         // Create a symbol table entry for param (link it later in the Var, Varlet and Funcall)
    //         createSymbolTableEntrySteFun(PARAM_NAME(paramIterator), PARAM_TYPE(paramIterator), STT_var, NULL);

    //         // Update symbolTable
    //         paramIterator = PARAM_NEXT(paramIterator);
    //     } while (paramIterator != NULL);
    // }

    // // If this param has a next, do the same for the next param in the function definition
    // TRAVnext(node);

    return node;
}

