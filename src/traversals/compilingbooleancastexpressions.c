/**
 * @file
 *
 * Traversal: CompilingBooleanCastExpressions
 * UID      : CBCE
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn CBCEcast
 */
node_st *CBCEcast(node_st *node)
{
    // TODO: how to do this??? because you do not know the value here right??? only the types, etc??

    // See message from Simon about milestone 10, the assignment is to implement a new Ternary Operator node in the AST!
    // Add this node to the nodeset operation

    // First traverse the expression to also convert those Cast nodes if they are Casts


    // If the Cast type is bool than it needs to be converted
    if (CAST_TYPE(node) == CT_bool) {
        
    }

    // Or if the result features boolean operators it needs to be converted


    // TODO: what to do with funcalls???

    return node;
}

