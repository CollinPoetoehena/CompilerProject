/**
 * @file
 *
 * Traversal: CompilingBooleanCastExpressions
 * UID      : CBCE
 *
 * Milestone 10: 
 * In assembly booleans are handled differently. There are no assembly
 * instructions to cast to and from booleans for example. So, this needs
 * to be done in some way, and that is where this traversal comes in.
 * This converts the Cast nodes that have a bool type or bool expr into
 * the semantically equivalent non-cast expression using the TernaryOp node.
 * numbers >= 1 should yield true 
 * numbers < 1 should yield false
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
    // Reset the boolean value at the start for every Cast node
    operatorTypeIsBool = false;

    // First traverse the expression to also convert those Cast nodes first if they are Casts
    TRAVexpr(node);

    // If the Cast type is bool than it needs to be converted
    // Or if the result features boolean operators it needs to be converted
    if (CAST_TYPE(node) == CT_bool) {
        // Will be transformed to TernaryOp node: predicate  ? true : false
        // where the predicate will use the numbers num >=1 -> true; num < 1 -> false;
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTbool(true), 
            ASTbool(false), CT_bool);
        // TODO: what to do with type signature, is it correct?

        // Set temp variable for boolean operator to true because there is a bool cast
        operatorTypeIsBool = true;

        // Return the new TernaryOp node
        return newConvertedNode;
    } else if (operatorTypeIsBool && CAST_TYPE(node) == CT_int) {
        // Will be transformed to TernaryOp node: predicate ? 1 : 0
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTnum(1), 
            ASTnum(0), CT_bool);
        // TODO: what to do with type signature, is it correct?

        // Set temp variable for boolean operator to true because there is a bool result cast
        operatorTypeIsBool = true;

        // Return the new TernaryOp node
        return newConvertedNode;
    } else if (operatorTypeIsBool && CAST_TYPE(node) == CT_float) {
        // Will be transformed to TernaryOp node: predicate ? 1.0 : 0.0
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTfloat(1.0), 
            ASTfloat(0.0), CT_bool);
        // TODO: what to do with type signature, is it correct?

        // Set temp variable for boolean operator to true because there is a bool result cast
        operatorTypeIsBool = true;

        // Return the new TernaryOp node
        return newConvertedNode;
    }

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
    // Get SteFun link and see if it is a bool return type, then set to true, otherwise do nothing
    if (STEFUN_TYPE(FUNCALL_STE_LINK(node)) == CT_bool) {
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