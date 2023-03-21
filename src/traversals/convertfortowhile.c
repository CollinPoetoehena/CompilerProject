/**
 * @file
 *
 * Traversal: ConvertForToWhile
 * UID      : CFTW
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Palm library for easy working with strings
#include "palm/str.h"
// Include enums and types, for the Type
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"

// Helper function to append a new Stmts node to the end of an Stmts node's chain
node_st *appendStmtsNodeToTail(node_st *firstSmtsNode, node_st *newStmtsNode) {
    node_st *stmtsIterator = firstSmtsNode;
    do {        
        // Check if the next is NULL, if so, it is the last, so append the new Stmts node
        if (STMTS_NEXT(stmtsIterator) == NULL) {
            STMTS_NEXT(stmtsIterator) = newStmtsNode;

            // Return the new Stmts nodes chain
            return firstSmtsNode;
        }

        // Update stmtsIterator
        stmtsIterator = STMTS_NEXT(stmtsIterator);
    } while (stmtsIterator != NULL);

    // Nothing updated, return NULL
    return NULL;
}

/**
 * @fn CFTWfor
 */
node_st *CFTWfor(node_st *node)
{
    // First go through the Stmts to first convert the most inner For nodes if they are possible
    TRAVblock(node);

    // Then after that, convert this node to a While node

    // Create the condition Expr for the new While node, copy Var node from start_expr (used multiple times)
    // no copy necessary for stop expression, because it is only used once, here.
    // node_st *newWhileCondition = ASTbinop(CCNcopy(FOR_START_EXPR(node)), FOR_STOP(node), BO_lt);

    //     // TODO: this does not go very well, the negative numbers do not always go to > operator in the binop!
    //     // TODO: this is probably because it is a memory address or something and is only negative sometimes, see print!
    //     if (FOR_STEP(node) != NULL) {
    //         printf("num value of For node step expr: %d\n", NUM_VAL(FOR_STEP(node)));
    //     }
        // TODO: so why is a positive value a value and a negative value some sort of memory address???


        // So, how to do this and determine when it is > or < because it can also be an Expr node that is not
// a num value right?? So, NUM_VALUE(node) cannot work!

// // Check if the Num node is smaller than 0, if so use > operator, otherwise use < operator for positive numbers
//     // TODO: the above print prints a weird value for negative numbers, why and how is that???
//     if (FOR_STEP(node) != NULL && NUM_VAL(FOR_STEP(node)) < 0) {
//         // Use greater than operator: >
//         BINOP_OP(newWhileCondition) = BO_gt;
//     }
//     // TODO: is stop expression from for loop: "i < FOR_STOP(node)"??? So, the < operator???

    
    // TODO: Implement in the report the for loop syntax and how and when to use the < and > operator, etc!


    // TODO: remove the above if this works
    // Create a TernaryOp node for the while expression
    node_st *whileConditionExprNode;
    if (FOR_STEP(node) != NULL) {        
        /*
        TernaryOp node:
        predicate Expr is (step > 0)
        then_expr Expr is for example: _i < stop
        else_expr Expr is for example: _i > stop

        The format is step > 0 ? _i < stop : _i > stop
        This selects the correct operator for the While condition.
        Type signature is bool.
        Copy Var node from start_expr (used multiple times).
        */
        whileConditionExprNode = ASTternaryop(
            ASTbinop(FOR_STEP(node), ASTnum(0), BO_gt),
            ASTbinop(CCNcopy(FOR_START_EXPR(node)), FOR_STOP(node), BO_lt),
            ASTbinop(CCNcopy(FOR_START_EXPR(node)), FOR_STOP(node), BO_gt),
            CT_bool
        );
        // TODO: type signature correct as bool???
    } else {
        // If the step is NULL, then it is the standard: +1, so < operator
        whileConditionExprNode = ASTbinop(CCNcopy(FOR_START_EXPR(node)), FOR_STOP(node), BO_lt);
    }

    // Create the new While node, use CCNcopy for the new Expr condition node
    node_st *newWhileNode = ASTwhile(CCNcopy(whileConditionExprNode), FOR_BLOCK(node));
    
    // Then append the step expression of the For node to the end of the While block
    node_st *forStepAssignNode = NULL;
    
    // Create the VarLet node with the Var node from the For node for the new Assign node
    // Create a copy of the name because the Var is already used in the new Assign node
    char *copiedVarName = STRcpy(VAR_NAME(FOR_START_EXPR(node)));
    // Then create the VarLet node (separate from the STRcpy because otherwise there is a Segmentation fault)
    node_st *newVarLetNode = ASTvarlet(copiedVarName);
    // Then set the link of that VarLet node (links should be correct because the renaming
    // of for identifiers happened before linking of Ste's in the CA phase)
    VARLET_STE_LINK(newVarLetNode) = VAR_STE_LINK(FOR_START_EXPR(node));

    if (FOR_STEP(node) != NULL) {
        /*
        Create the Assign node with the step expression as a BinOP node
        The start_expr should contain a Var node with the correct linking already
        from the renaming of for loops in the CA phase.
        Create a copy of the Var node in the start_expression because it is used multiple times.

        No need to introduce a BO_sub operator, because negative step values are correctly executed:
        _i = _i + -3;
        is correctly executed to "_i = _i -3;" because in math +- will be -
        */
        forStepAssignNode = ASTassign(newVarLetNode,
            ASTbinop(CCNcopy(FOR_START_EXPR(node)), FOR_STEP(node), BO_add));
    } else {
        // Create the Assign node with + 1 (the standard step expression) BinOP node
        forStepAssignNode = ASTassign(newVarLetNode,
            ASTbinop(CCNcopy(FOR_START_EXPR(node)), ASTnum(1), BO_add));
    }

    // If the Stmts block is not NULL (== not empty), then append the new Stmts node at the end
    if (WHILE_BLOCK(newWhileNode) != NULL && forStepAssignNode != NULL) {
        appendStmtsNodeToTail(WHILE_BLOCK(newWhileNode), ASTstmts(forStepAssignNode, NULL));
    } else if (WHILE_BLOCK(newWhileNode) == NULL && forStepAssignNode != NULL) {
        // If the Stmts block is NULL (== empty), then make the new Stmts node the new one
        WHILE_BLOCK(newWhileNode) = ASTstmts(forStepAssignNode, NULL);
    }
    
    // Return the new While node
    return newWhileNode;
}
