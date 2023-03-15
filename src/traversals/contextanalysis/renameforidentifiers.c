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

// This global variable is used for appending the for loop Var assignment in front of
node_st *lastStmtsNode = NULL;
// TODO: for loop VarDecl can be appended at the end of the VarDecls, maybe also add FunBody node then??
// again use CCNcopy like regular assignments if it gives an error of invalid pointer or segmentation, first try without!

// TODO: hash table String maken met de variabele en na elke for loop die eruit halen
// use the travdata, like 1.6

// TODO: create VarDecl in above fundef and set for loop to Var call, maybe even in a separate traversal separate the induction var from for???
// for(int i = 0, 5); wordt niet dit want dit gaat fout met nested for loops:
//int i_=0;
//for(i_, 5) 
// Wat je wel wilt is dat de declaratie voor de for loops komen in de fundef.
// daarnaast wil je dat de assignment van de for loop inductie variabele precies voor de for loop komt. Dus bijvoorbeeld:
/*
void foo() {
    for (int i = 0, 10) {
        for (int i = 0, 10) {

        }
    }
}

wordt (ook is de declaratie nu handmatig gescheiden van de assignment omdat de regular assignments voor de Ste's is!):
void foo() {
    int i_;
    int i__;
    i_ = 0;
    for (i_, 10) {
        i__ = 0;
        for (i__, 10) {
        }
    }
}

// TODO: verwerk dit in de report ook nog!
*/

// Stmts traversal
// elke for loop de var decl ervoor plakken

void RFIinit() { 
    // initialize hash table, makes sure there is a hash table
    htable_st *hash_table = HTnew_String(100);

    struct data_rfi *data = DATA_RFI_GET();
    data->for_identifiers_table = hash_table;

    return; 
}
void RFIfini() { return; }

/**
 * @fn RFIstmts
 */
node_st *RFIstmts(node_st *node)
{
    //TODO
    // Check if the type is NT_FOR
    if (NODE_TYPE(STMTS_STMT(node)) == NT_GLOBDEF) {
        // Update last globdef node, this node will be used to append the __init FunDef to
        lastStmtsNode = node;
    }

    return node;
}

/**
 * @fn RFIfor
 */
node_st *RFIfor(node_st *node)
{
    // TODO this file does not work correctly: ./civicc ../test/basic/functional/for_to_while.cvc
    // nested for loops and its i do not work correctly
    // the i from the previous for loop is not renamed in the nested for loop, fix that
    // The problem is because it first goes in to the block part, wich is a new for loop first, and
    // then after that the vars occur that are not renamed because the identifier is from the new for loop
    // TODO: skip for now, but ask in the lesson next week!

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

    // Save the current for identifiers in the hash table
    // Allocate memory for a string of up to 99 characters in C to create a new memory block
    int *newForIdentifier = MEMmalloc(100 * sizeof(char));
 
    // Save the For node in the global helper variable
    currentForNode = node;

    // Update the counter
    counter++;

    // Go to the traversal functions of the children
    TRAVblock(node);

    // Remove current array item after traversing the block
    // TODO

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