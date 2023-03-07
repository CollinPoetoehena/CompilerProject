/**
 * @file
 *
 * Traversal: CreateVariableSymbolTableEntries
 * UID      : CVS
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
// Used to fill the Program symbol table for Variables
node_st *firstSymbolTable = NULL;
node_st *tempSymbolTable = NULL;

// Find an Ste node that has the specified name
node_st *findSteLink(char *name) {
    printf("Trying to find Ste for: %s\n", name);

    // return the Symbol table entry that is linked to this node (with name)
    // Use linear search to find the entry, stop when next is NULL
    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Match found, return Ste node. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STE_NAME(symbolTable), name) == 0) {
                printf("**********************Link found for: %s\n", name);
                return symbolTable;
            }

            // Update symbolTable
            symbolTable = STE_NEXT(symbolTable);
        } while (symbolTable != NULL);
    }

    printf("No link found for linking an Ste to a Var, VarLet or FunCall!\n");
    // No existing symbol found, return NULL
    return NULL;
}

// Check if a symbol is unique
bool isSymbolUnique(char *name) {
    // Check if the name is not already present in the symbol table entries (use linear search)

    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Symbol already present, return not unique/false. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STE_NAME(symbolTable), name) == 0) {
                printf("**********************Link found for %s\n", name);
                return false;
            }

            // Update symbolTable
            symbolTable = STE_NEXT(symbolTable);
        } while (symbolTable != NULL);
    }

    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

// Create a symbol table entry node
bool createSymbolTableEntry(char *name, enum Type type, enum SymbolTableType steType, node_st *params) {
    // First check if the name is already present, if so, save it in errors
    if (isSymbolUnique(name)) {
        // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
        node_st *newSte = ASTste(NULL, name, type, currentScope, steType, params);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        // Ste creation succeeded
        return true;
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("multiple matching declarations/definitions found\n");
    }

    // Creation failed
    return false;
}

/**
 * @fn CVSprogram
 */
node_st *CVSprogram(node_st *node)
{
    printf("program\n");

    // Print the start of the context analysis variables
    printf("\n\n\n****************************************************************************************************************************************************************************** \
    \t\tStart of context analysis variables\n");

    // TODO: does this also work instead of TRAVdecls(node)??? Otherwise, link them again such as in the old traversal!
    // TODO: Tested and works, still works, maybe error is coming from here then?
    // Go to the traversal functions of the children
    TRAVchildren(node);

    // TODO: uncomment print and convert print function from old traversal to this one! Or: print in print traversal, 
    // decide what is better with new attributes of the Ste's in the Program and other nodes!
    // Print all the symbol tables at the end of the traversal
    // printSymbolTables();

    // Update Ste first occurrence to put into the Program node
    if (firstSymbolTable != NULL) {
        PROGRAM_FIRST_STE_VARIABLES(node) = firstSymbolTable;
    }
    // If the firstSymbolTable is NULL, then no symbol tables are created, so nothing to update


    // TODO: symbol tables can probably now be printed in the print traversal with the new implementation via firstsymbol.. of Program

    printf("\n\n\n\t\tEnd of context analysis variables\n****************************************************************************************************************************************************************************** \
    \n");
    return node;
}

/**
 * @fn CVSglobdecl
 */
node_st *CVSglobdecl(node_st *node)
{
    return node;
}

/**
 * @fn CVSglobdef
 */
node_st *CVSglobdef(node_st *node)
{
    return node;
}

/**
 * @fn CVSfundef
 */
node_st *CVSfundef(node_st *node)
{
    printf("fundef\n");

    // No need to create a ste for the fundef here, that is done in the symbol tables for the functions
    // So, only create a pointer to the first SteVar in this functions scope

    // Save the oldScope
    int oldScope = currentScope;
    // Increment the current scope inside a function body for every function body 
    // (basic has global, funbody and statements (if, while, etc) scope)
    currentScope++;

    // First traverse the params, because they come first in the symbol tables implementation
    TRAVparams(node);
    // Create a pointer to the first steVar using the global temp symbol table variable
    if (tempSymbolTable != NULL) {
        FUNDEF_FIRST_STE_VARIABLES(node) = tempSymbolTable;
    }
    // If the tempSymbolTable is NULL, then no symbol tables are created, so nothing to update

    // Then traverse the funbody
    TRAVbody(node);

    // Update the scope to the old scope after the statements when you get back to this fundef
    currentScope = oldScope;

    return node;
}

/**
 * @fn CVSparam
 */
node_st *CVSparam(node_st *node)
{
    // Create ste for the param
    printf("param\n");

    // Use the previousSymbolTable because that is the FunDef which contains the params
    // If it is not null it contains the LinkedList of type Param from the FunDef
    if (STE_PARAMS(previousSymbolTable) != NULL) {
        // Get the first param from the Ste
        node_st *paramIterator = STE_PARAMS(previousSymbolTable);
        do {
            // Create a symbol table entry for param (link it later in the Var, Varlet and Funcall)
            createSymbolTableEntry(PARAM_NAME(paramIterator), PARAM_TYPE(paramIterator), STT_var, NULL);

            // Update symbolTable
            paramIterator = PARAM_NEXT(paramIterator);
        } while (paramIterator != NULL);
    }

    // If this param has a next, do the same for the next param in the function definition
    TRAVnext(node);


    // Save the first SteVar for a param in the tempSymbolTable to link to the FunDef node

    return node;
}

/**
 * @fn CVSfunbody
 */
node_st *CVSfunbody(node_st *node)
{
    // First traverse the VarDecls
    TRAVdecls(node);

    // Then traverse the Stmts
    // Updating scope for Stmts not necessary because there are no VarDecls or FunDefs in Stmts (see language)!
    TRAVstmts(node);

    return node;
}

/**
 * @fn CVSvardecl
 */
node_st *CVSvardecl(node_st *node)
{
    return node;
}

/**
 * @fn CVSfor
 */
node_st *CVSfor(node_st *node)
{
    return node;
}

/**
 * @fn CVSvar
 */
node_st *CVSvar(node_st *node)
{
    return node;
}

/**
 * @fn CVSvarlet
 */
node_st *CVSvarlet(node_st *node)
{
    return node;
}

