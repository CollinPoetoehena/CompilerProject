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
    // TODO: what does this do and how do I test this traversal?
    TRAVchildren(node);
    // node_st *new = NULL;

    if (BINOP_TYPE(node) == BO_mul) {
        if (NUM_VAL(BINOP_LEFT(node)) == 2) {
            // Change left binop to right binop value
            BINOP_LEFT(node) = TRAVopt(BINOP_RIGHT(node));
        } else if (NUM_VAL(BINOP_RIGHT(node)) == 2) {
            // Change right binop to left binop value
            BINOP_RIGHT(node) = TRAVopt(BINOP_LEFT(node));
        } else if (NUM_VAL(BINOP_LEFT(node)) == 3) {
            // TODO: Change k*3 to k+k+k
            
        } else if (NUM_VAL(BINOP_RIGHT(node)) == 3) {
            // TODO: Change k*3 to k+k+k

        }
    }

    return node;
}