/**
 * @file
 *
 * Traversal: RegularAssignments
 * UID      : RA
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"

/**
 * @fn RAvardecl
 */
node_st *RAvardecl(node_st *node)
{
    // if init then it has an initialization: "= Expr"
    if (VARDECL_INIT(node) != NULL) {
      //TODO: HOW TO CREATE THE __init function for the compiler
      
      // Create a copy of the nodes and then free this node to create separate nodes
      //TODO: is this correct????
      node_st *nodeOne = CCNcopy(node);
      node_st *nodeTwo = CCNcopy(VARDECL_INIT(node));
      // Free the node
      CCNfree(node);
    }
    
    return node;
}


/**
 * @fn RAassign
 */
node_st *RAassign(node_st *node)
{
    return node;
}

/**
 * @fn RAglobdef
 */
node_st *RAglobdef(node_st *node)
{
    return node;
}

/**
 * @fn RAfor
 */
node_st *RAfor(node_st *node)
{
    return node;
}

