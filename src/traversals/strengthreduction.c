/**
 * @file
 *
 * Traversal: StrengthReduction
 * UID      : SR
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

/**
 * @fn SRbinop
 */
node_st *SRbinop(node_st *node)
{
    node_st *new = NULL;

    if (BINOP_TYPE(node) == BO_mul) {
        //CCNCopy 
        node_st *left = CCNcopy(BINOP_LEFT(node));
        node_st *leftTwo = CCNcopy(BINOP_LEFT(node));
        node_st *right = CCNcopy(BINOP_RIGHT(node));
        node_st *rightTwo = CCNcopy(BINOP_RIGHT(node));

        if (NODE_TYPE(left) == NT_VAR && 
            (NODE_TYPE(right) == NT_NUM && NUM_VAL(right) == 2)) {
                // Use one deep copy and one reference because otherwise
                // you have children who point to the same node_st
                new = ASTbinop(left, BINOP_LEFT(node), BO_add);
        } else if (NODE_TYPE(right) == NT_VAR && 
            (NODE_TYPE(left) == NT_NUM && NUM_VAL(left) == 2)) {
                new = ASTbinop(right, BINOP_RIGHT(node), BO_add);
        } else if (NODE_TYPE(left) == NT_VAR && 
            (NODE_TYPE(right) == NT_NUM && NUM_VAL(right) == 3)) {
                new = ASTbinop(ASTbinop(left, leftTwo, BO_add), BINOP_LEFT(node), BO_add);
        } else if (NODE_TYPE(right) == NT_VAR && 
            (NODE_TYPE(left) == NT_NUM && NUM_VAL(left) == 3)) {
                new = ASTbinop(ASTbinop(right, rightTwo, BO_add), BINOP_RIGHT(node), BO_add);
        } 
    }

    if (new != NULL) {
        // Return new Binop if changes were made
        return new;
    }

    // Return node if no changes were made
    return node;
}