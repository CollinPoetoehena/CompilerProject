/**
 * @file
 *
 * Traversal: CountOperators
 * UID      : CO
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

void COinit() { return; }
void COfini() { return; }

/**
 * @fn CObinop
 */
node_st *CObinop(node_st *node)
{
    int addCount = 0;
    int subCount = 0;
    int mulCount = 0;
    int divCount = 0;
    int modCount = 0;

    //TODO: how can I store this in the module node?
    if (BINOP_TYPE(node) == BO_add) {
        addCount++;
    }
    if (BINOP_TYPE(node) == BO_sub) {
        subCount++;
    }
    if (BINOP_TYPE(node) == BO_mul) {
        mulCount++;
    }
    if (BINOP_TYPE(node) == BO_div) {
        divCount++;
    }
    if (BINOP_TYPE(node) == BO_mod) {
        modCount++;
    }

    return node;
}

