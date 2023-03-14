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
    // First traverse the expression to also convert those Cast nodes first if they are Casts
    TRAVexpr(node);

    // If the Cast type is bool than it needs to be converted
    if (CAST_TYPE(node) == CT_bool) {
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTnum(1), 
            ASTnum(0), CT_bool);
        // TODO: what to do with type signature, is it correct?

        // Return the new TernaryOp node
        return newConvertedNode;
    }
    // Or if the result features boolean operators it needs to be converted
    // TODO: traverse operators of cast expression and use there type signature, or if it has a boolean constant do it
    if (operatorTypeIsBool && CAST_TYPE(node) == CT_int) {
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTnum(1), 
            ASTnum(0), CT_int);
        // TODO: what to do with type signature, is it correct?

        // Return the new TernaryOp node
        return newConvertedNode;
    } else if (operatorTypeIsBool && CAST_TYPE(node) == CT_float) {
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTfloat(1.0), 
            ASTfloat(0.0), CT_float);
        // TODO: what to do with type signature, is it correct?

        // Return the new TernaryOp node
        return newConvertedNode;
    }

    // TODO: how to do this with the TernaryOp???
    // Do not think about the complext expressions, it will simply be the TernaryOp node:
    // predicate ? 1 : 0
    // TODO: what to do with funcalls??? Just save it as an expr because you do not really care about what expr

    // Reset the boolean value at the end for the next Cast operator
    operatorTypeIsBool = false;

    // If no changes were made, just return the original Cast node again
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
 * @fn CBCEfuncall
 */
node_st *CBCEfuncall(node_st *node)
{
    // TODO: get SteFun link and see if it is a bool return type, then set to true, otherwise nothing

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