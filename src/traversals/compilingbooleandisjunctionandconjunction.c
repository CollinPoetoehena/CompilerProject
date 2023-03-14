/**
 * @file
 *
 * Traversal: CompilingBooleanDisjunctionAndConjunction
 * UID      : CBDC
 *
 * Milestone 9:
 * The logical operators (&&, ||) are lazy evaluated, that means that the right expression
 * is only evaluated if following the evaluation of the left operand
 * the right operand determines the result of the operation. So, therefore a ternary operator
 * node should be introduced to the AST and implement this functionality.
 * 
 * An example of this could be the following expression:
 * funCallA() || funCallB()
 * If funcallA() returns true, then funCallB() should not be executed. This is important
 * because funCallB() can have side effects for example.
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

