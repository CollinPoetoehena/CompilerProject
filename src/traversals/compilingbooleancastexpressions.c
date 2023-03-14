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

// Include enums, for the Type 
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"

// Helper variable to determine if the Cast expression result is binop
bool operatorTypeIsBool = false;

/**
 * @fn CBCEcast
 */
node_st *CBCEcast(node_st *node)
{
    // TODO: how to do this??? because you do not know the value here right??? only the types, etc??

    // First traverse the expression to also convert those Cast nodes if they are Casts
    TRAVexpr(node);

    // If the Cast type is bool than it needs to be converted
    if (CAST_TYPE(node) == CT_bool) {
        
    }
    // Or if the result features boolean operators it needs to be converted
    // TODO: traverse operators of cast expression and use there type signature, or if it has a boolean constant do it
    if (operatorTypeIsBool) {
        
    }


    // TODO: what to do with funcalls???

    // Reset the boolean value at the end for the next Cast operator
    operatorTypeIsBool = false;

    return node;
}

/**
 * @fn CBCEbinop
 */
node_st *CBCEbinop(node_st *node)
{
    // First traverse the children expressions to find other binops
    TRAVleft(node);
    TRAVright(node);

    // Then after traversing determine if the binop is a bool result
    if (BINOP_OPERATOR_TYPE_SIGNATURE(node) == CT_bool) {
        // Set the bool result value to true
        operatorTypeIsBool = true;
    }
    return node;
}

/**
 * @fn CBCEbool
 */
node_st *CBCEbool(node_st *node)
{
    // Set the bool result value to true because it has a bool result type 
    operatorTypeIsBool = true;

    return node;
}