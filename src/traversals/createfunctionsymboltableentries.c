/**
 * @file
 *
 * Traversal: CreateFunctionSymbolTableEntries
 * UID      : CFS
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums, for the Type and SymbolTableType
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

/**
 * @fn CFSprogram
 */
node_st *CFSprogram(node_st *node)
{
    return node;
}

/**
 * @fn CFSfundef
 */
node_st *CFSfundef(node_st *node)
{
    return node;
}

/**
 * @fn CFSfuncall
 */
node_st *CFSfuncall(node_st *node)
{
    return node;
}

