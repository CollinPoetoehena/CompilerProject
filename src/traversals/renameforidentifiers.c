/**
 * @file
 *
 * Traversal: RenameForIdentifiers
 * UID      : RFI
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include  <string.h>

// Global counter for renaming the identifiers
int counter = 1;

/**
 * @fn RFIfor
 */
node_st *RFIfor(node_st *node)
{
    // TODO
    // makkelijker: eerst een traversal alleen op for loop en al die iterators renamen naar een counter met zoals hier
    //TODO: multiple i's in one function scope should return an error right because they are now in the same funbody?
    // first i, gets _i1, second becomes _i2, can be done with a global counter. With a double forloop be careful with what i's 
    // can be done in a separate traversal
    // dan simpel gewoon hier uitvoern met Ste

    // Update the counter
    char *previousId = FOR_VAR(node);
    FOR_VAR(node) = MEMmalloc(strlen(previousId) + sizeof(int) + 2); // allocate memory for a string of up to 99 characters
    // Initialize with empty string to avoid weird memory address value being used at the start
    sprintf(FOR_VAR(node), "%s%d_", previousId, counter);

    printf("for loop identifier: %s\n", FOR_VAR(node));

    return node;
}

/**
 * @fn RFIvar
 */
node_st *RFIvar(node_st *node)
{

    return node;
}

/**
 * @fn RFIvarlet
 */
node_st *RFIvarlet(node_st *node)
{

    return node;
}

