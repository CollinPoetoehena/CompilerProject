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

// This global variable is used for appending the for loop Var Assignment
node_st *lastStmtsNodeBeforeForLoop = NULL;
node_st *previousStmtsNode = NULL;

node_st *newForLoopAssignNode = NULL;
// This global variable is used for appending the for loop start expr VarDecl to
node_st *lastVarDeclNode = NULL;
node_st *lastFunBodyNode = NULL;
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

    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();
    data->for_identifiers_table = hash_table;

    return; 
}
void RFIfini() { return; }

/**
 * @fn RFIfunbody
 */
node_st *RFIfunbody(node_st *node)
{
    // // No VarDecl nodes, so first For node identifiers should also become first VarDecl node
    // if (FUNBODY_DECLS(node) == NULL) {
    //     // Save this FunBody node to the global helper variable
    //     lastFunBodyNode = node;
    // } else {
        // First traverse the VarDecls to save the last VarDecl node to append the for identifiers to
    //     TRAVdecls(node);
    // }

    // Save this FunBody node to the global helper variable
    lastFunBodyNode = node;

    // First traverse the VarDecls to save the last VarDecl node to append the for identifiers to
    TRAVdecls(node);

    // Then traverse the statements to convert and rename the for loop identifiers
    //previousStmtsNode = NULL;
    TRAVstmts(node);

    // Reset last FunBody after every FunBody traversal
    lastFunBodyNode = NULL;

    return node;
}

/**
 * @fn RFIvardecl
 */
node_st *RFIvardecl(node_st *node)
{
    // Update last VarDecl node
    lastVarDeclNode = node;

    // Traverse to the next VarDecl
    TRAVnext(node);

    return node;
}

/**
 * @fn RFIstmts
 */
node_st *RFIstmts(node_st *node)
{
    // TODO:
    if (NODE_TYPE(STMTS_STMT(node)) == NT_FOR) {
        // Then traverse the Stmt that is a for loop and come back here and update the sequence of Stmts
        lastStmtsNodeBeforeForLoop = node;

        TRAVstmt(node);

        // If the new Assign node is not NULL then the For node created a new one, update Stmts sequence
        if (newForLoopAssignNode != NULL) {
            // Create the new Stmts node with the Assign node from the For node
            // node_st *prependStmtsNode = ASTstmts(newForLoopAssignNode, NULL);

            // TODO: this is a try to do it differently by only changing this node
            node_st *prependStmtsNode = CCNcopy(node);
            node = ASTstmts(newForLoopAssignNode, prependStmtsNode);

            previousStmtsNode = node;

            // TODO: minor bug: it renames the assignments of the deepest for loop when nested, otherwise it works fine with one for

            // Skip traversing this node again to avoid a loop, instead go to the next of the next node
            TRAVnext(STMTS_NEXT(node));

            //return node;
        }
    } else {
        TRAVstmt(node);
        previousStmtsNode = node;
        TRAVnext(node);
    }

    return node;
}

// /**
//  * @fn RFIstmts
//  */
// node_st *RFIstmts(node_st *node)
// {
//     // 
//     //TODO: remove after debugging
    // printf("Node type is For??? %s\n", NODE_TYPE(STMTS_STMT(node)) == NT_FOR ? "true" : "false");


//     // Check if the type of the Stmt is a For node: NT_FOR
//     if (NODE_TYPE(STMTS_STMT(node)) == NT_FOR) {
//         printf("for stmts\n");
//         // Update lastStmtsNodeBeforeForLoop, this node will be used to prepend for id assignment to

//         // TODO: 1 extra variabele van de Stmts ervoor.
//         printf("UPDATING LAST STMTS NODE BEFORE FOR LOOP*****\n");
//         lastStmtsNodeBeforeForLoop = node;

//         // Then traverse the Stmt that is a for loop and come back here and update the sequence of Stmts
//         printf("TRAVAERSING NODE FOR\n");
//         TRAVstmt(node);

//         // If the new Assign node is not NULL then the For node created a new one, update Stmts sequence
//         if (newForLoopAssignNode != NULL) {
//             printf("newForLoop ... is not NULL!\n");
//             // Create the new Stmts node with the Assign node from the For node
//             node_st *prependStmtsNode = ASTstmts(newForLoopAssignNode, node);
//             // If the previousStmtsNode is still NULL, that means that the For node is the first Stmts
//             if (previousStmtsNode == NULL) {
//                 printf("Getting into previous is NULL!\n");
//                 // Update this node by appending the current Stmts node to this new Stmts node
//                 STMTS_NEXT(prependStmtsNode) = node;

//                 return prependStmtsNode;
//             } else {
//                 // Otherwise, insert it in between the Stmts

//                 printf("Getting into previous is NOTTTTT NULL!\n");
//             }
//         } else {
//             printf("newForLoop ... is NULLLLLLL!\n");
//         }

//         printf("getting here?????**************************\n");

//         // TODO: return new node???
//         // TODO: design something that resets the newForLoopAssignNode 
//         // then also add in the if newForLoopAssignNode != NULL, to not update it again!
//         // maybe this can be at the top if statement
//         // TODO: CREATE NEW TEST CASES TO TEST THIS FUNCTIONALITY FOR FOR LOOPS
//         // TODO: THEN AFTER EVERYTHING IS TESTED, TEST EVERYTHING THOROUGLY AND GOOD WITH EVERYTHING ON
//         // SO ALL THE COMPILER FEATURES ON UNTIL MILESTONE 10, THEN TEST ALL OF THAT THOROUGLY, THEN YOU
//         // KNOW FOR SURE THAT EVERYTHING BEFORE CODE GENERATION WORKS PERFECTLY!
//         // TODO: THEN AFTER THAT, UPDATE THE REPORT WITH EVERYTHING UP UNTIL THE LAST MILESTONE (10)
//     } else {
//         // Just traverse the Stmt witout updating the Stmts nodes
//         printf("TRAVAERSING NODE STMTS THAT IS NOT FOR, NOTHING HERE, JUST DO NEXT\n");
//         //TRAVstmt(node);
//     }

//     // Before going to the next, save the previous Stmts node
//     // Then, traverse the next Stmts
//     printf("TRAVERSING NEXT STMTS!***********\n");
//     printf("updating************\n");
//     // TODO: this is getting done before 
//     //previousStmtsNode = node;
//     TRAVnext(node);

//     return node;
// }

/**
 * @fn RFIfor
 */
node_st *RFIfor(node_st *node)
{
    printf("GETTING INTO FOR TRAVERSAL FUNCTION!!!***\n");
    // TODO: afterwards check if any global variables are also not renamed, probably not because before it did not as well! but check still!


    // TODO this file does not work correctly: ./civicc ../test/basic/functional/for_to_while.cvc
    // nested for loops and its i do not work correctly
    // the i from the previous for loop is not renamed in the nested for loop, fix that
    // The problem is because it first goes in to the block part, wich is a new for loop first, and
    // then after that the vars occur that are not renamed because the identifier is from the new for loop
    // TODO: skip for now, but ask in the lesson next week!

    // This will rename all the iterators from the for loop to <CountUnderscores><variableName>
    // such as: '__i'
    // This is done in this way because it is basically a variable that a user cannot create because it starts with an _

    // Save the old for loop id
    char *oldForIdentifier = FOR_VAR(node);

    // Rename the identifier of the For node (do not create a new node, this is much easier!)
    // '_' because it is a valid identifier (see lexer)
    for( int i = 0; i < counter; i++ ){
        // Use for loop and concat an '_' for count times
        FOR_VAR(node) = STRcat("_", FOR_VAR(node));
    }

    // Get the hash table from the travdata of the RFI traversal and save the current for identifiers in the hash table
    struct data_rfi *data = DATA_RFI_GET();

    // Insert newValue (== type char *)
    // Cast to void * because the parameter of the HTinsert is of type void *
    HTinsert(data->for_identifiers_table, oldForIdentifier, (void *) FOR_VAR(node));

    // Update the counter
    counter++;

    // TODO: removed start expr and make the start expr the new occurrence and create a new VarDecl by appending
    // it to the last VarDecl
    // TODO: maybe do it with CCNcopy if it gives an error of invalid pointer or segmentation
    // Append new For variable as a VarDecl node to the last VarDecl node of this FunDef and update it
    // Expr init from the VarDecl node needs to be NULL because the Stmts should be done before the for loop

    /*
    Create a new VarDecl node, use CCNcopy here because you are saving this new AST node to the AST without 
    returning it in this traversal function, otherwise it is lost. Do it here because otherwise the chain 
    of VarDecl nodes will not be correctly appended in the below if statement with multiple for loops!
    */
    node_st *newVarDeclNode = CCNcopy(ASTvardecl(NULL, NULL, NULL, FOR_VAR(node), CT_int));

    // Also, save the start expression assignment, because this needs to be separated
    // also applies to the regular assignments traversal that was done before ContextAnalysis
    //FOR_START_EXPR(node);
    // Prepend the assignment to this For node
    // node_st *newStmtsNode = ASTstmts(ASTassign)
    // STMTS_NEXT(lastStmtsNodeBeforeForLoop) = 
    // TODO

    // Save the For assignment Expr before updating it with the new Var node
    newForLoopAssignNode = CCNcopy(ASTassign(ASTvarlet(FOR_VAR(node)), FOR_START_EXPR(node)));
    // TODO: same here for the AST assign node with CCNcopy???
    printf("previousStmtsNode is NULL??? %s\n", previousStmtsNode == NULL ? "true" : "false");
                printf("lastStmtsNodeBeforeForLoop is NULL??? %s\n", lastStmtsNodeBeforeForLoop == NULL ? "true" : "false");

    // if (lastStmtsNodeBeforeForLoop != NULL) {
    //     // Create the new Stmts node with the Assign node from the For node
    //     node_st *prependStmtsNode = ASTstmts(newForLoopAssignNode, NULL);
    //     // If the previousStmtsNode is still NULL, that means that the For node is the first Stmts
    //     if (previousStmtsNode == NULL) {
    //         printf("FIRST DOING THE IF\n");
    //         // Update this node by appending the current Stmts node to this new Stmts node
    //         // node_st *tempStmts = lastStmtsNodeBeforeForLoop;
    //         // lastStmtsNodeBeforeForLoop = prependStmtsNode;
           
    //         // TODO: this funbody does not update anything
    //         // if i do this code exactly in the funbody itself then it works, how???
    //         // it does work with the decls this works, how???: FUNBODY_DECLS(lastFunBodyNode) = NULL;

    //         //STMTS_NEXT(lastStmtsNodeBeforeForLoop) = prependStmtsNode;

    //         // TODO: this does not yet work
    //         // tested if the assign node works correctly and it does if you append it to the lastStmtsNodeBeforeForLoop
    //         // So this works, but now it needs to be prepended!
    //         //         node_st *prependStmtsNode = ASTstmts(newForLoopAssignNode, NULL);
    //                     //STMTS_NEXT(lastStmtsNodeBeforeForLoop) = prependStmtsNode;
    //                     STMTS_STMT(lastStmtsNodeBeforeForLoop) = NULL;
    //                     //STMTS_NEXT(prependStmtsNode) = prependStmtsNode;

    //         // Otherwise, set the new VarDecl as the first one to the current FunBody node
    //         // FUNBODY_STMTS(lastFunBodyNode) = prependStmtsNode;


    //         // STMTS_NEXT(prependStmtsNode) = lastStmtsNodeBeforeForLoop;

    //         //return prependStmtsNode;
    //     } else {
    //         printf("FIRST DOING THE ELSE\n");
    //         // printf("previousStmtsNode is NULL??? %s\n", previousStmtsNode == NULL ? "true" : "false");
    //         // printf("lastStmtsNodeBeforeForLoop is NULL??? %s\n", lastStmtsNodeBeforeForLoop == NULL ? "true" : "false");

    //         STMTS_NEXT(previousStmtsNode) = prependStmtsNode;
    //         STMTS_NEXT(prependStmtsNode) = lastStmtsNodeBeforeForLoop;
    //     }
    // }
    
    // If there is an existing lastVarDeclNode, update it
    if (lastVarDeclNode != NULL) {
        //Update the next vardecl
        VARDECL_NEXT(lastVarDeclNode) = newVarDeclNode;
        // Update the last VarDecl with the new VarDecl to append the next For identifier to
        // No need to copy here because it is a global pointer only used in this traversal file, not in the AST
        lastVarDeclNode = newVarDeclNode;
        /*
        Update the For node start expr to have a Var node that can be linked with Symbol tables later
        Create a copy of the string to avoid pointing to the FOR_VAR(node) twice
        No need to use CCNcopy here because you are changing this node in this traversal function
        and you are returning this node at the end, so therefore CCNcopy is not necessary here
        */
        FOR_START_EXPR(node) = ASTvar(STRcpy(FOR_VAR(node)));
    } else {
        // Otherwise, set the new VarDecl as the first one to the current FunBody node
        FUNBODY_DECLS(lastFunBodyNode) = newVarDeclNode;
        // Update the last VarDecl with the new VarDecl to append the next For identifier to
        lastVarDeclNode = newVarDeclNode;
        // Update the For node start expr to have a Var node that can be linked with Symbol tables later
        FOR_START_EXPR(node) = ASTvar(STRcpy(FOR_VAR(node)));
    }

    // Go to the traversal functions of the children
    TRAVblock(node);
    
    // Remove current old identifier from the for loop after traversing every for block. This is 
    // mainly done for nested for loops so that the next nested for loop uses the right variable
    HTremove(data->for_identifiers_table, oldForIdentifier);

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
    //printf("varlet\n");

    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();

    // Get the value from the identifier from the hash table
    char *value = (char *) HTlookup(data->for_identifiers_table, VARLET_NAME(node));

    // If the value is in the hash table, rename it
    if (value != NULL) {
        // Create a copy of the id to avoid pointing to the same id of the For node
        VARLET_NAME(node) = STRcpy(value);
    }


    // Also rename the occurrence of the for identifier
    // No need to check for other variables, because there is only the globdecl and globdef that can have
    // the same name and they will not be changed by this. Also, the same identifier in the scope of the
    // for loop identifier will give a context analysis error because that identifier of the for loop
    // needs to be saved in the scope above the for loop!
    // if (currentRenamedId != NULL && currentForNode != NULL) {
        // if (strcmp(currentRenamedId, VARLET_NAME(node)) == 0) {
        //     // Create a copy of the id to avoid pointing to the same id of the For node
        //     VARLET_NAME(node) = STRcpy(FOR_VAR(currentForNode));
        // }
    // }

    return node;
}

/**
 * @fn RFIvar
 */
node_st *RFIvar(node_st *node)
{
    //printf("varlet\n");

    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();

    // Get the value from the identifier from the hash table
    char *value = (char *) HTlookup(data->for_identifiers_table, VAR_NAME(node));

    // If the value is in the hash table, rename it
    if (value != NULL) {
        // Create a copy of the id to avoid pointing to the same id of the For node
        VAR_NAME(node) = STRcpy(value);
    }


    // Also rename the occurrence of the for identifier
    // No need to check for other variables, because there is only the globdecl and globdef that can have
    // the same name and they will not be changed by this. Also, the same identifier in the scope of the
    // for loop identifier will give a context analysis error because that identifier of the for loop
    // needs to be saved in the scope above the for loop!
    // if (currentRenamedId != NULL && currentForNode != NULL) {
    //     if (strcmp(currentRenamedId, VAR_NAME(node)) == 0) {
    //         // Create a copy of the id to avoid pointing to the same id of the For node
    //         VAR_NAME(node) = STRcpy(FOR_VAR(currentForNode));
    //     }
    // }

    return node;
}