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
    // TODO this file does not work correctly: ./civicc ../test/basic/functional/for_to_while.cvc
    // nested for loops and its i do not work correctly
    // the i from the previous for loop is not renamed in the nested for loop, fix that




    // This will rename all the iterators from the for loop to xCountUnderscores (with count x underscore)
    // such as: 'i__'

    // Save the old for loop id
    currentRenamedId = FOR_VAR(node);

    // Rename the identifier of the For node (do not create a new node, this is much easier!)
    // '_' because it is a valid identifier (see lexer)
    for( int i = 0; i < counter; i++ ){
        // Use for loop and concat an '_' for count times
        FOR_VAR(node) = STRcat(FOR_VAR(node), "_");
    }
 
    // Save the For node in the global helper variable
    currentForNode = node;

    // Update the counter
    counter++;

    // Go to the traversal functions of the children
    TRAVblock(node);

    return node;
}

/**
 * @fn RFIfuncall
 */
node_st *RFIfuncall(node_st *node)
{
    // Will go to the traversal functions of the Exprs
    TRAVargs(node);

    return node;
}

/**
 * @fn RFIassign
 */
node_st *RFIassign(node_st *node)
{
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
    // Also rename the occurrence of the for identifier
    // No need to check for other variables, because there is only the globdecl and globdef that can have
    // the same name and they will not be changed by this. Also, the same identifier in the scope of the
    // for loop identifier will give a context analysis error because that identifier of the for loop
    // needs to be saved in the scope above the for loop!
    if (currentRenamedId != NULL && currentForNode != NULL) {
        if (strcmp(currentRenamedId, VARLET_NAME(node)) == 0) {
            // Create a copy of the id to avoid pointing to the same id of the For node
            VARLET_NAME(node) = STRcpy(FOR_VAR(currentForNode));
        }
    }

    return node;
}

/**
 * @fn RFIvar
 */
node_st *RFIvar(node_st *node)
{
    // Also rename the occurrence of the for identifier
    // No need to check for other variables, because there is only the globdecl and globdef that can have
    // the same name and they will not be changed by this. Also, the same identifier in the scope of the
    // for loop identifier will give a context analysis error because that identifier of the for loop
    // needs to be saved in the scope above the for loop!
    if (currentRenamedId != NULL && currentForNode != NULL) {
        if (strcmp(currentRenamedId, VAR_NAME(node)) == 0) {
            // Create a copy of the id to avoid pointing to the same id of the For node
            VAR_NAME(node) = STRcpy(FOR_VAR(currentForNode));
        }
    }

    return node;
}