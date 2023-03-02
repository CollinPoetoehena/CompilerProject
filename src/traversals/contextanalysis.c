/**
 * @file
 *
 * Traversal: ContextAnalysis
 * UID      : CA
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

// Global variable for the current Ste to use as next
node_st *previousSymbolTable = NULL;
int currentScope = 0; // Start at global scope

/**
 * @fn CAprogram
 */
node_st *CAprogram(node_st *node)
{
    // Create a new symbol table with a new scope (program == global scope)
    // node_st *new = ASTste();
    // Update the current symbol table to use in the other traversals

    // Nothing is changed to the program node, so just return the node again
    return node;
}

/**
 * @fn CAfunbody
 */
node_st *CAfunbody(node_st *node)
{
    // Create a new symbol table with a new scope (funbody == one scope under global)
    //TODO: is the currentScope variable correct???

    // Update the global scope to 1 inside a function body for every function body
    currentScope++;

    return node;
}

/**
 * @fn CAfuncall
 */
node_st *CAfuncall(node_st *node)
{
    // Create a function call symbol
    // TODO: how to get the type inside the symbol table?
    node_st *newSte = ASTste(NULL, FUNCALL_NAME(node), CT_int, currentScope, STT_funcall);

    // Update previous symbol table
    if (previousSymbolTable != NULL) {
        // Update previous symbol table next
        STE_NEXT(previousSymbolTable) = newSte;
    }   

    // Update symbol table, if previous is NULL it would not have updated the next!
    previousSymbolTable = newSte;

    // Update the Link node attribute of this node to link it to the symbol table
    FUNCALL_STE_LINK(node) = newSte;

    printf("*************************symbol table made\n");

    // TODO: is scope 1?? And what about statements (such as inside a funbody and inside a while statement????)

    return node;
}

/**
 * @fn CAvar
 */
node_st *CAvar(node_st *node)
{
    // Create a var symbol
    // TODO: how to get the type inside the symbol table?
    node_st *newSte = ASTste(NULL, VAR_NAME(node), CT_int, currentScope, STT_var);

    // Update previous symbol table
    if (previousSymbolTable != NULL) {
        // Update previous symbol table next
        STE_NEXT(previousSymbolTable) = newSte;
    }   

    // Update symbol table, if previous is NULL it would not have updated the next!
    previousSymbolTable = newSte;

    // Update the Link node attribute of this node to link it to the symbol table
    VAR_STE_LINK(node) = newSte;

    printf("*************************symbol table made\n");

    // Changes made to the node directly, so no need to return a new node here
    return node;
}

/**
 * @fn CAvarlet
 */
node_st *CAvarlet(node_st *node)
{
    // Create a varlet symbol
    // TODO: how to get the type inside the symbol table?
    node_st *newSte = ASTste(NULL, VARLET_NAME(node), CT_int, currentScope, STT_varlet);

    // Update previous symbol table
    if (previousSymbolTable != NULL) {
        // Update previous symbol table next
        STE_NEXT(previousSymbolTable) = newSte;
    }   

    // Update symbol table, if previous is NULL it would not have updated the next!
    previousSymbolTable = newSte;

    // Update the Link node attribute of this node to link it to the symbol table
    VARLET_STE_LINK(node) = newSte;

    printf("*************************symbol table made\n");

    return node;
}

