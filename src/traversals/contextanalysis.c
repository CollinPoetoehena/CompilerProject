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
    return node;
}

/**
 * @fn CAvar
 */
node_st *CAvar(node_st *node)
{
    // Create a var call symbol
    return node;
}

/**
 * @fn CAvarlet
 */
node_st *CAvarlet(node_st *node)
{
    // Create a varlet call symbol
    return node;
}

