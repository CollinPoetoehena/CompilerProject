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

// Global helper variable to save the type in
enum Type tempTypeForCastConversion = CT_NULL; // CT_NULL is the NULL type

/**
 * @fn CBCEcast
 */
node_st *CBCEcast(node_st *node)
{
    // Reset the boolean value and the temp type at the start for every Cast node
    operatorTypeIsBool = false;
    tempTypeForCastConversion = CT_NULL;

    // First traverse the expression to also convert those Cast nodes first if they are Casts
    TRAVexpr(node);

    // If the Cast type is bool than it needs to be converted
    // Or if the result features boolean operators it needs to be converted
    if (CAST_TYPE(node) == CT_bool) {
        // Will be transformed to TernaryOp node: predicate ? true : false
        // where the predicate will use the numbers num >=1 -> true; num < 1 -> false;
        // resulting type will be bool, so set the type signature to bool
        if (tempTypeForCastConversion == CT_int) {
            // Create a Binop for an int type, also set the left operand and type signature type for assembly generation!
            node_st *newBinopNode = ASTbinop(CAST_EXPR(node), ASTnum(1), BO_ge);
            BINOP_LEFT_OPERAND_TYPE(newBinopNode) = tempTypeForCastConversion;
            // Resulting type of the BinOp ge operation will be bool
            BINOP_OPERATOR_TYPE_SIGNATURE(newBinopNode) = CT_bool;

            // Then create the TernaryOp node
            node_st *newConvertedNode = ASTternaryop(newBinopNode, ASTbool(true), 
                ASTbool(false), CT_bool);

            // Set temp variable for boolean operator to true because there is a bool cast
            operatorTypeIsBool = true;
            // Do the same for the temp type but then with the corresponding type
            tempTypeForCastConversion = CT_int;

            // Return the new TernaryOp node
            return newConvertedNode;
        } else if (tempTypeForCastConversion == CT_float) {
            // Create a Binop for a float type, also set the left operand and type signature type for assembly generation!
            node_st *newBinopNode = ASTbinop(CAST_EXPR(node), ASTfloat(1.0), BO_ge);
            BINOP_LEFT_OPERAND_TYPE(newBinopNode) = tempTypeForCastConversion;
            // Resulting type of the BinOp ge operation will be bool
            BINOP_OPERATOR_TYPE_SIGNATURE(newBinopNode) = CT_bool;

            // Then create the TernaryOp node
            node_st *newConvertedNode = ASTternaryop(newBinopNode, ASTbool(true), 
                ASTbool(false), CT_bool);

            // Set temp variable for boolean operator to true because there is a bool cast
            operatorTypeIsBool = true;
            // Do the same for the temp type but then with the corresponding type
            tempTypeForCastConversion = CT_float;

            // Return the new TernaryOp node
            return newConvertedNode;
        }
    } else if (operatorTypeIsBool && CAST_TYPE(node) == CT_int) {
        // Will be transformed to TernaryOp node: predicate ? 1 : 0
        // resulting type will be int, so set the type signature to int
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTnum(1), 
            ASTnum(0), CT_int);

        // Set temp variable for boolean operator to true because there is a bool result cast
        operatorTypeIsBool = true;
        // Do the same for the temp type but then with the corresponding type
        tempTypeForCastConversion = CT_int;

        // Return the new TernaryOp node
        return newConvertedNode;
    } else if (operatorTypeIsBool && CAST_TYPE(node) == CT_float) {
        // Will be transformed to TernaryOp node: predicate ? 1.0 : 0.0
        // resulting type will be float, so set the type signature to float
        node_st *newConvertedNode = ASTternaryop(CAST_EXPR(node), ASTfloat(1.0), 
            ASTfloat(0.0), CT_float);

        // Set temp variable for boolean operator to true because there is a bool result cast
        operatorTypeIsBool = true;
        // Do the same for the temp type but then with the corresponding type
        tempTypeForCastConversion = CT_float;

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

    // Save the temp type
    tempTypeForCastConversion = BINOP_OPERATOR_TYPE_SIGNATURE(node);

    return node;
}

/**
 * @fn CBCEmonop
 */
node_st *CBCEmonop(node_st *node)
{
    // First traverse the children expressions to find other monops
    TRAVoperand(node);

    // Then after traversing determine if the monop is a bool result
    if (MONOP_OPERATOR_TYPE_SIGNATURE(node) == CT_bool) {
        // Set the bool result value to true
        operatorTypeIsBool = true;
    }

    // Save the temp type
    tempTypeForCastConversion = MONOP_OPERATOR_TYPE_SIGNATURE(node);

    return node;
}

/**
 * @fn CBCEternaryop
 */
node_st *CBCEternaryop(node_st *node)
{
    // First traverse the children expressions to find other ternary operators
    TRAVpredicate(node);
    TRAVthen_expr(node);
    TRAVelse_expr(node);

    // Then after traversing determine if the ternaryop is a bool result
    if (TERNARYOP_TYPE_SIGNATURE(node) == CT_bool) {
        // Set the bool result value to true
        operatorTypeIsBool = true;
    }

    // Save the temp type
    tempTypeForCastConversion = TERNARYOP_TYPE_SIGNATURE(node);

    return node;
}

/**
 * @fn CBCEfuncall
 */
node_st *CBCEfuncall(node_st *node)
{
    // First traverse the args to convert them if they need to be converted
    TRAVargs(node);

    // Get SteFun link and see if it is a bool return type, then set to true, otherwise do nothing
    if (STEFUN_TYPE(FUNCALL_STE_LINK(node)) == CT_bool) {
        // Set the bool result value to true
        operatorTypeIsBool = true;
    }

    // Save the temp type
    tempTypeForCastConversion = STEFUN_TYPE(FUNCALL_STE_LINK(node));

    return node;
}

/**
 * @fn CBCEvar
 */
node_st *CBCEvar(node_st *node)
{
    // Get SteVar link and see if it is a bool type, then set to true, otherwise do nothing
    if (STEVAR_TYPE(VAR_STE_LINK(node)) == CT_bool) {
        // Set the bool result value to true
        operatorTypeIsBool = true;
    }

    // Save the temp type
    tempTypeForCastConversion = STEVAR_TYPE(VAR_STE_LINK(node));

    return node;
}

/**
 * @fn CBCEnum
 */
node_st *CBCEnum(node_st *node)
{
    // Save the temp type
    tempTypeForCastConversion = CT_int;

    return node;
}

/**
 * @fn CBCEfloat
 */
node_st *CBCEfloat(node_st *node)
{
    // Save the temp type
    tempTypeForCastConversion = CT_float;

    return node;
}

/**
 * @fn CBCEbool
 */
node_st *CBCEbool(node_st *node)
{
    // Set the bool result value to true because it has a bool result type 
    operatorTypeIsBool = true;

    // Save the temp type
    tempTypeForCastConversion = CT_bool;

    return node;
}