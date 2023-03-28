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

// This node is used for linking the params to the previous fundef node
node_st *tempFunDefNode = NULL;
// This boolean is used to only link the first param occurrence in a fundef
bool firstParam = false;

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

// Check if the name is not already present in the symbol table entries (use linear search)
bool isSymbolUniqueSteFun(char *name) {
    // Only one scope for basic for fundefs: global (0)
    node_st *symtbolTableChainFun = firstSymbolTableFun;
    // Go through the current chain to check if it contains the symbol already
    if (symtbolTableChainFun != NULL) {
        do {
            // Symbol already present, return not unique/false. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STEFUN_NAME(symtbolTableChainFun), name) == 0) {
                return false;
            }

            // Update symbolTable
            symtbolTableChainFun = STEVAR_NEXT(symtbolTableChainFun);
        } while (symtbolTableChainFun != NULL);
    }
    
    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

// Create a symbol table entry node, declared after helper functions, because otherwise it gives an error in C!
node_st *createSymbolTableEntrySteFun(char *name, enum Type type, node_st *nodeForErrorLoc) {
    // First check if the name is already present, if so, save it in errors
    if (isSymbolUniqueSteFun(name)) {
        // Parent of fundefs is in basic always NULL, next and params are set later, so for now NULL
        node_st *newSte = ASTstefun(NULL, NULL, name, type, currentScopeFun, NULL);

        // Update global symbol tables in this traversal
        updateGlobSymbolTablesSteFun(newSte);

        // Ste creation succeeded, return newSte
        return newSte;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "multiple matching declarations/definitions found for the function: %s, at line %d, column %d",
            name, NODE_BLINE(nodeForErrorLoc), NODE_BCOL(nodeForErrorLoc));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    // Creation failed, return NULL
    return NULL;
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
    // Create a SteFun for this function definition
    node_st *fundefSte = createSymbolTableEntrySteFun(FUNDEF_NAME(node), FUNDEF_TYPE(node), node);

    // Link SteFun creation to this FunDef node if it was successfull
    if (fundefSte != NULL) {
        FUNDEF_SYMBOL_TABLE(node) = fundefSte;
        // Create a new SteFun to use in the params traversal if it was successfull
        tempFunDefNode = fundefSte;
        // Open the new params to link only the first one
        firstParam = true;
    }

    // Then traverse the params to add to this tempFunDefNode
    TRAVparams(node);

    // Then traverse the body
    TRAVbody(node);

    // Reset the fundef for the next params
    tempFunDefNode = NULL;
    firstParam = false;

    return node;
}

/**
 * @fn CFSparam
 */
node_st *CFSparam(node_st *node)
{
    // If the temp FunDef node is not NULL link the params to it by using the previous FunDef
    if (tempFunDefNode != NULL) {
        if (firstParam) {
            // Put the first param in the SteFun node
            STEFUN_PARAMS(tempFunDefNode) = node;
            // Reset the firstParam boolean to only add the first param
            firstParam = false;
        }
    }

    // If this param has a next, do the same for the next param in the function definition
    TRAVnext(node);

    return node;
}