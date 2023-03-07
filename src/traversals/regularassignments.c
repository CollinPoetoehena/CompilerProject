/**
 * @file
 *
 * Traversal: RegularAssignments
 * UID      : RA
 * 
 * This traversal should separate the declaration from the initilizations.
 * This will be handy with code generation.
 *
 * Example:
 * int a = 5 * 6;
 * int b = 3;
 * a = 6;
 * Should become (still with the equivalent code):
 * int a; int b; a = 5 * 6; b = 3; a = 6;
 * 
 * So, you should first only have declarations and then the statements
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"

// vardecls in een lijst
// __init maak je aan met ASTfundef, alle initializaties, worden stmts
// int a = 3; 
// init func heeft dan a = 3;

// funbd\ody travdecls
// daarna travstmts initalizaties normale stmts maken en prependen aan de bestaande stmts

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
      // Important: only use Copy when you want to have it at two different locations
      // No need to Copy here because it is re-used here because it is set to NULL afterwards
      node_st *init = VARDECL_INIT(node);
      // Set init to NULL, to only keep declaration (such as int a;)
      VARDECL_INIT(node) = NULL;
    }
    
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
    //
    return node;
}

