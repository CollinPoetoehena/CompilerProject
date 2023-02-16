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
 * @fn COmodule
 */
node_st *COmodule(node_st *node)
{
    // Go through the whole tree and come back to this function
    TRAVchildren(node);

    // Get travdata from CO traversal
    struct data_co *data = DATA_CO_GET();

    // Save the travdata variables at the end of the tree cycle (TRAVchildren(node))
    MODULE_ADD(node) = data->add;
    MODULE_SUB(node) = data->sub;
    MODULE_MUL(node) = data->mul;
    MODULE_DIV(node) = data->div;
    MODULE_MOD(node) = data->mod;

    return node;
}

/**
 * @fn CObinop
 */
node_st *CObinop(node_st *node)
{
    // Get travdata from CO traversal
    struct data_co *data = DATA_CO_GET();

    // Increment data->attribute by 1
    if (BINOP_TYPE(node) == BO_add) {
        data->add += 1;
    }
    if (BINOP_TYPE(node) == BO_sub) {
        data->sub += 1;
    }
    if (BINOP_TYPE(node) == BO_mul) {
        data->mul += 1;
    }
    if (BINOP_TYPE(node) == BO_div) {
        data->div += 1;
    }
    if (BINOP_TYPE(node) == BO_mod) {
        data->mod += 1;
    }

    return node;
}

