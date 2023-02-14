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
    // node_st is 

    if (BINOP_TYPE(node) == BO_mul) {
        if (NODE_TYPE(BINOP_LEFT(node)) == NT_NUM || BINOP_RIGHT(node) == NT_NUM) {
            // Both Binop children need to be a num value
            node_st *leftNum = BINOP_LEFT(node);
            node_st *rightNum = BINOP_RIGHT(node);
            // node_st is altijd pointer (*) 
            // 2 verschillende stukken data, wijzen naar hetzelfde
            // segmentation fault is pointers die pointen naar iets dat niet mag, use valgrind and gdb

            if (NUM_VAL(leftNum) == 2) {
                new = ASTbinop(rightNum, rightNum, BO_add);
            } else if (NUM_VAL(rightNum) == 2) {
                new = ASTbinop(leftNum, leftNum, BO_add);
            } else if (NUM_VAL(leftNum) == 3) {
                new = ASTbinop(ASTbinop(leftNum, leftNum, BO_add), leftNum, BO_add);
            } else if (NUM_VAL(leftNum) == 3) {
                // TODO: Change k*3 to k+k+k add new Binop because 
                // Expr (child type of Binop) can also be of type Binop
                // 3 * k -> k+k+k
                new = ASTbinop(ASTbinop(rightNum, rightNum, BO_add), rightNum, BO_add);
            }
        }
    }

    // return new Binop
    return new;
}