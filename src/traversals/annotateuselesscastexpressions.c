/**
 * @file
 *
 * Traversal: EliminateUselessCastExpressions
 * UID      : AUCE
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums, for the Type 
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"

// Global helper variable to save the type in
enum Type tempCastExpressionType = CT_NULL; // CT_NULL is the NULL type

/**
 * @fn AUCEcast
 */
node_st *AUCEcast(node_st *node)
{
    // Reset the boolean value and the temp type at the start for every Cast node
    tempCastExpressionType = CT_NULL;

    // First traverse the expression to also convert those Cast nodes first and find the expression types
    TRAVexpr(node);

    // If the cast type and the cast expression are the same type, remove the useless cast
    if (CAST_TYPE(node) == tempCastExpressionType) {
        // Update this node by setting useless cast to true
        CAST_USELESS(node) = true;

        // Save the tempCastExpressionType of this cast expression for the next Cast node
        tempCastExpressionType = CAST_TYPE(node);
    }

    // If no changes were made, just return the original Cast node again
    return node;
}

/**
 * @fn AUCEbinop
 */
node_st *AUCEbinop(node_st *node)
{
    // First traverse the children expressions to find other binops
    TRAVleft(node);
    TRAVright(node);

    // Save the temp type
    tempCastExpressionType = BINOP_OPERATOR_TYPE_SIGNATURE(node);

    return node;
}

/**
 * @fn AUCEmonop
 */
node_st *AUCEmonop(node_st *node)
{
    // First traverse the children expressions to find other monops
    TRAVoperand(node);

    // Save the temp type
    tempCastExpressionType = MONOP_OPERATOR_TYPE_SIGNATURE(node);

    return node;
}

/**
 * @fn AUCEfuncall
 */
node_st *AUCEfuncall(node_st *node)
{
    // First traverse the args to convert them if they need to be converted
    TRAVargs(node);

    // Save the temp type
    tempCastExpressionType = STEFUN_TYPE(FUNCALL_STE_LINK(node));

    return node;
}

/**
 * @fn AUCEvar
 */
node_st *AUCEvar(node_st *node)
{
    // Save the temp type
    tempCastExpressionType = STEVAR_TYPE(VAR_STE_LINK(node));

    return node;
}

/**
 * @fn AUCEnum
 */
node_st *AUCEnum(node_st *node)
{
    // Save the temp type
    tempCastExpressionType = CT_int;

    return node;
}

/**
 * @fn AUCEfloat
 */
node_st *AUCEfloat(node_st *node)
{
    // Save the temp type
    tempCastExpressionType = CT_float;

    return node;
}

/**
 * @fn AUCEbool
 */
node_st *AUCEbool(node_st *node)
{
    // Save the temp type
    tempCastExpressionType = CT_float;

    return node;
}