/**
 * @file
 *
 * Traversal: CreateVariableSymbolTableEntries
 * UID      : CVS
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
 * @fn CVSprogram
 */
node_st *CVSprogram(node_st *node)
{
    // Print the start of the context analysis variables
    printf("\n\n\n****************************************************************************************************************************************************************************** \
    \t\tStart of context analysis variables\n");

    // TODO: does this also work instead of TRAVdecls(node)??? Otherwise, link them again such as in the old traversal!
    // TODO: Tested and works, still works, maybe error is coming from here then?
    TRAVchildren(node);

    // TODO: uncomment print and convert print function from old traversal to this one! Or: print in print traversal, 
    // decide what is better with new attributes of the Ste's in the Program and other nodes!
    // Print all the symbol tables at the end of the traversal
    // printSymbolTables();

    printf("\n\n\n\t\tEnd of context analysis variables\n****************************************************************************************************************************************************************************** \
        \n");
    return node;
}

/**
 * @fn CVSfundef
 */
node_st *CVSfundef(node_st *node)
{
    printf("getting here!");
    return node;
}

/**
 * @fn CVSfunbody
 */
node_st *CVSfunbody(node_st *node)
{
    return node;
}

/**
 * @fn CVSfor
 */
node_st *CVSfor(node_st *node)
{
    return node;
}

/**
 * @fn CVSglobdecl
 */
node_st *CVSglobdecl(node_st *node)
{
    return node;
}

/**
 * @fn CVSglobdef
 */
node_st *CVSglobdef(node_st *node)
{
    return node;
}

/**
 * @fn CVSparam
 */
node_st *CVSparam(node_st *node)
{
    return node;
}

/**
 * @fn CVSvardecl
 */
node_st *CVSvardecl(node_st *node)
{
    return node;
}

/**
 * @fn CVSvar
 */
node_st *CVSvar(node_st *node)
{
    return node;
}

/**
 * @fn CVSvarlet
 */
node_st *CVSvarlet(node_st *node)
{
    return node;
}

