/**
 * @file
 *
 * Traversal: CompilingBooleanDisjunctionAndConjunction
 * UID      : CBDC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn CBDCbinop
 */
node_st *CBDCbinop(node_st *node)
{
    // First traverse to the next expressions to also convert those BinOps if they are BinOps
    TRAVleft(node);
    TRAVright(node);

    // TODO: are these correct?????**********************************************************************************

    // Then, convert binop that is a logical operator to TernaryOp node when the children are traversed.
    // This is done after because otherwise a BinOp with a BinOp Expr would not be correctly converted to TernaryOp
    if (BINOP_OP(node) == BO_or) {        
        /*
        Use the type signature from the BinOp node obtained in TypeChecking

        Format for new TernaryOp node for the BinOp ||:
        predicate == true 
        ? 
        then not evaluate then expr because it already is true (== ASTbool with true value)
        :
        otherwise evaluate else expression to find if that returns true
        */
        node_st *newConvertedNode = ASTternaryop(BINOP_LEFT(node), ASTbool(true), 
            BINOP_RIGHT(node), BINOP_OPERATOR_TYPE_SIGNATURE(node));

        // TODO: or is this correct?????
        // Create a new TernaryOp node with the same type signature as the original BinOp
        // node_st* ternaryop = ASTternaryop(NULL, NULL, NULL, BINOP_OPERATOR_TYPE_SIGNATURE(binop));
        // // Set the predicate of the TernaryOp to the left child of the BinOp
        // TERNARY_PREDICATE(ternaryop) = BINOP_LEFT(binop);
        // // Set the then_expr of the TernaryOp to a new TernaryOp with a true predicate and the right child of the BinOp
        // TERNARY_THEN_EXPR(ternaryop) = ASTternaryop(NULL, ASTbool(true), BINOP_RIGHT(binop), NULL);
        // // Set the else_expr of the TernaryOp to a BoolLit node with value false
        // TERNARY_ELSE_EXPR(ternaryop) = ASTboollit(false);
        
        // Return the new TernaryOp node
        return newConvertedNode;
    } else if (BINOP_OP(node) == BO_and) {
        /*
        Use the type signature from the BinOp node obtained in TypeChecking

        Format for new TernaryOp node for the BinOp &&:
        predicate == true 
        ? 
        then evaluate then expression to find if that also returns true
        :
        otherwise not evaluate else expression because it is already false (== ASTbool with false value)
        */  
        node_st *newConvertedNode = ASTternaryop(BINOP_LEFT(node), BINOP_RIGHT(node), 
            ASTbool(false), BINOP_OPERATOR_TYPE_SIGNATURE(node));

        // Return the new TernaryOp node
        return newConvertedNode;
    }

    // If no changes were made, just return the original BinOp node again
    return node;
}

