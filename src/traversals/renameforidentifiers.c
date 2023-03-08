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
// Palm library for easy working with strings
#include "palm/str.h"
#include  <string.h>

// Global counter for renaming the identifiers
int counter = 1;
// Global currentRenamedId is used to rename the occurrences of the old for loop id
char *currentRenamedId = NULL;
// Global currentForNode is used to save the new for loop node in and 
node_st *currentForNode = NULL;

/**
 * @fn RFIfor
 */
node_st *RFIfor(node_st *node)
{
    // TODO
    // makkelijker: eerst een traversal alleen op for loop en al die iterators renamen naar een counter met zoals hier
    //TODO: multiple i's in one function scope should return an error right because they are now in the same funbody?
    // first i, gets i_, second becomes i__, can be done with a global counter. With a double forloop be careful with what i's 
    // can be done in a separate traversal
    // dan simpel gewoon hier uitvoern met Ste

    // Save the old for loop id
    currentRenamedId = FOR_VAR(node);

    // Rename the identifier of the For node (do not create a new node, this is much easier!)
    // '_' because it is a valid identifier (see lexer)
    for( int i = 0; i < counter; i++ ){
        // Use for loop and concat an '_' for count times
        FOR_VAR(node) = STRcat(FOR_VAR(node), "_");
    }
 
    // // plak integers
    // char *previousId = FOR_VAR(node);
    // FOR_VAR(node) = MEMmalloc(strlen(previousId) + sizeof(int) + 2); // allocate memory for a string of up to 99 characters
    // // Initialize with empty string to avoid weird memory address value being used at the start
    // sprintf(FOR_VAR(node), "%s%d_", previousId, counter);

    // printf("for loop identifier: %s\n", FOR_VAR(node));

    // Save the For node in the global helper variable
    currentForNode = node;

    // Update the counter
    counter++;

    
    TRAVblock(node);
    // TRAVchildren(node);

    // TODO: a block can consist of funcalls and assignments and they have vars and varlets, update those values as well!

    return node;
}

/**
 * @fn RFIfuncall
 */
node_st *RFIfuncall(node_st *node)
{
    printf("coming to funcall\n");

    // Will go to the traversal functions of the Exprs
    TRAVargs(node);

    return node;
}

/**
 * @fn RFIassign
 */
node_st *RFIassign(node_st *node)
{
    printf("coming to assign\n");

    // Will go to the traversal functions of the Exprs
    TRAVexpr(node);
    // Will go to the varlet traversal function
    TRAVlet(node);

    return node;
}

/**
 * @fn RFIvarlet
 */
node_st *RFIvarlet(node_st *node)
{
    printf("varlet occurrence\n");

    // TODO: also rename the occurrence of the for identifier
    // TODO: check if it does not rename other identifiers not from the for loop
    if (currentRenamedId != NULL && currentForNode != NULL) {
        if (strcmp(FOR_VAR(currentForNode), VARLET_NAME(node)) == 0) {
            // Create a copy of the id to avoid pointing to the same id of the For node
            char *newVarLetName = STRcpy(FOR_VAR(currentForNode));
            VARLET_NAME(node) = newVarLetName;
        }
    }

    return node;
}

/**
 * @fn RFIvar
 */
node_st *RFIvar(node_st *node)
{
    printf("Var occurrence\n");

    // TODO: also rename the occurrence of the for identifier
    // Test if it is not renaming other occurrences of i
    if (currentRenamedId != NULL && currentForNode != NULL) {
        if (strcmp(FOR_VAR(currentForNode), VAR_NAME(node)) == 0) {
            // Create a copy of the id to avoid pointing to the same id of the For node
            char *newVarName = STRcpy(FOR_VAR(currentForNode));
            VAR_NAME(node) = newVarName;
        }
    }

    return node;
}