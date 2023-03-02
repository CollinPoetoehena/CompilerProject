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

/**
 * @fn CAprogram
 */
node_st *CAprogram(node_st *node)
{
    // Create a new symbol table with a new scope (program == global scope)
    node_st *new = NULL;
    

    // Nothing is changed to the program node, so just return the node again
    return node;
}

/**
 * @fn CAfunbody
 */
node_st *CAfunbody(node_st *node)
{
    // Create a new symbol table with a new scope (funbody == one scope under global)
    return node;
}

/**
 * @fn CAfuncall
 */
node_st *CAfuncall(node_st *node)
{
    // Create a function call symbol
    // Also update the Link node attribute of this node to link it to the symbol table
    return node;
}

/**
 * @fn CAvar
 */
node_st *CAvar(node_st *node)
{
    // Create a var call symbol
    // Also update the Link node attribute of this node to link it to the symbol table
    return node;
}

/**
 * @fn CAvarlet
 */
node_st *CAvarlet(node_st *node)
{
    // Create a varlet call symbol
    // Also update the Link node attribute of this node to link it to the symbol table
    return node;
}

