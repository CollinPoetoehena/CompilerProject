/**
 * @file
 *
 * Traversal: RenameForIdentifiers
 * UID      : RFI
 *
 * This traversal renams all identifiers from all For nodes and creates a VarDecl
 * for it without an init Expr and appends it to the last VarDecl.
 * Then it creates an Assign node and inserts it BEFORE the For node it came from.
 * The VarDecl will be unique with an _ per for loop extra. Nested for loops should
 * have unique identifiers, but for loops in the same scope level of the FunDef node
 * can have the same identifier. For example:
 * for (int i = 0, 10) {
 *   for (int i = 0, 10) {
 *  }
 * }
 * THIS IS NOT A VALID SYNTAX because there are two i's in the For scope, but this is valid:
 * for (int i = 0, 10) {
 *   for (int j = 0, 10) {
 *  }
 * }
 *
 * And this is also valid:
 * for (int i = 0, 10) {
 * }
 * for (int i = 0, 10) {
 * }
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Palm library for easy working with strings
#include "palm/str.h"
#include  <string.h>

// Global counter for renaming the identifiers with a number of _
int counter = 1;

// This global variable is used for appending the for loop start expr VarDecl to
node_st *lastVarDeclNode = NULL;
// This global helper variable is used to update the last FunBody with its VarDecl nodes
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
    htable_st *hash_table_assignNodes = HTnew_String(100);

    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();
    data->for_identifiers_table = hash_table;
    data->for_assignNodes_table = hash_table_assignNodes;

    return; 
}
void RFIfini() { return; }

/**
 * @fn RFIfunbody
 */
node_st *RFIfunbody(node_st *node)
{
    // Save this FunBody node to the global helper variable
    lastFunBodyNode = node;

    // First traverse the VarDecls to save the last VarDecl node to append the for identifiers to
    TRAVdecls(node);

    // Then traverse the statements to convert and rename the for loop identifiers
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
    // Check if the type of the Stmt is a For node: NT_FOR, if so, traverse the For node
    if (NODE_TYPE(STMTS_STMT(node)) == NT_FOR) {
        // Then traverse the Stmt that is a for loop and come back here and update the sequence of Stmts
        TRAVstmt(node);

        // Get the hash table from the travdata of the RFI traversal
        struct data_rfi *data = DATA_RFI_GET();

        // Get the value from the assignNodes hash table
        // Use the updated Var identifier from this For Stmt node to find the correct new Assign node
        node_st *value = (node_st *) HTlookup(data->for_assignNodes_table, FOR_VAR(STMTS_STMT(node)));

        // If the new Assign node is not NULL then the For node created a new one, update Stmts sequence
        if (value != NULL) {
            // Create the new Stmts node with the Assign node from the For node
            // Create a copy of the old Stmts node you want to prepend the new Assign node to
            node_st *oldStmtsNode = CCNcopy(node);
            // Replace the current node with the new Stmts node containing the new Assign node
            // and a next reference to the oldStmtsNode
            node = ASTstmts(value, oldStmtsNode);

            // Skip traversing this node again to avoid a loop, instead go to the next of the next node
            TRAVnext(STMTS_NEXT(node));
        }
    } else {
        // Otherwise, just traverse the other Stmts nodes and Stmt nodes
        TRAVstmt(node);
        TRAVnext(node);
    }

    return node;
}

/**
 * @fn RFIfor
 *
 * This will rename all the iterators from the for loop to 
 * <CountUnderscores><variableName>, such as: '__i'
 * This is done in this way because it is basically a variable that a user 
 * cannot create because it starts with an _
 */
node_st *RFIfor(node_st *node)
{
    // Save the old for loop id
    char *oldForIdentifier = FOR_VAR(node);

    // Rename the identifier of the For node (do not create a new node, this is much easier!)
    // '_' because it is a valid identifier that the use will not use
    for( int i = 0; i < counter; i++ ){
        // Use for loop and concat an '_' for count times
        FOR_VAR(node) = STRcat("_", FOR_VAR(node));
    }

    // Get the hash table from the travdata of the RFI traversal and save the current for identifiers in the hash table
    struct data_rfi *data = DATA_RFI_GET();

    // Insert newValue (== type char *)
    // Cast to void * because the parameter of the HTinsert is of type void *
    HTinsert(data->for_identifiers_table, oldForIdentifier, (void *) FOR_VAR(node));

    // Update the counter for the next For node
    counter++;

    /*
    Create a new VarDecl node, use CCNcopy here because you are saving this new AST node to the AST without 
    returning it in this traversal function, otherwise it is lost. Do it here because otherwise the chain 
    of VarDecl nodes will not be correctly appended in the below if statement with multiple for loops!
    */
    node_st *newVarDeclNode = CCNcopy(ASTvardecl(NULL, NULL, NULL, FOR_VAR(node), CT_int));
    // Save the For assignment Expr before updating it with the new Var node in the below if statement
    node_st *newForLoopAssignNode = CCNcopy(ASTassign(ASTvarlet(FOR_VAR(node)), FOR_START_EXPR(node)));
    // Save the assignment node in the hash table to insert in the Stmts nodes in the AST later
    HTinsert(data->for_assignNodes_table, FOR_VAR(node), (void *) newForLoopAssignNode);
    
    // If there is an existing lastVarDeclNode, update it
    if (lastVarDeclNode != NULL) {
        // Update the next vardecl to append the new VarDecl to the already existing VarDecl nodes
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
 *
 * Also rename the occurrence of the for identifier in the For node
 * No need to check for other variables because the For node traversal function traverses that body
 * so only variables in that body will be changed that are also in the hash table
 */
node_st *RFIvarlet(node_st *node)
{
    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();

    // Get the value from the identifier from the hash table
    char *value = (char *) HTlookup(data->for_identifiers_table, VARLET_NAME(node));

    // If the value is in the hash table, rename it
    if (value != NULL) {
        // Create a copy of the id to avoid pointing to the same id of the For node
        VARLET_NAME(node) = STRcpy(value);
    }

    return node;
}

/**
 * @fn RFIvar
 *
 * Also rename the occurrence of the for identifier in the For node
 * No need to check for other variables because the For node traversal function traverses that body
 * so only variables in that body will be changed that are also in the hash table
 */
node_st *RFIvar(node_st *node)
{
    // Get the hash table from the travdata of the RFI traversal
    struct data_rfi *data = DATA_RFI_GET();

    // Get the value from the identifier from the hash table
    char *value = (char *) HTlookup(data->for_identifiers_table, VAR_NAME(node));

    // If the value is in the hash table, rename it
    if (value != NULL) {
        // Create a copy of the id to avoid pointing to the same id of the For node
        VAR_NAME(node) = STRcpy(value);
    }

    return node;
}