/**
 * @file
 *
 * This file contains the code for the Print traversal.
 * The traversal has the uid: PRT
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/dbug.h"

/**
 * @fn PRTprogram
 */
node_st *PRTprogram(node_st *node)
{
    // Go to child and print it
    TRAVdecls(node);

    // TODO: how to print newline at the end of the program
    // Print new line at the end of the program
    // printf("\n");

    //TODO: change everything to correctly TRAV to make a good representation. When you use TRAVnodechildren
    // It goes to the print function of that node, that way you can properly create the representation of the nodes
    // Remove TRAVchildren(node) and change it to TRAVchild(node) or TRAVchildren(node) for Decls for example

    // You want to print the program to look almost exactly the same like the run file, but then with the AST nodes
    //glob variable for indentation and function to prints indents

    // printf("\n-----------Printing Program node--------------:\n");
    // printf("This node does not have a representation to print, so it is empty, there is nothing going wrong in this part!\n");
    
    return node;
}

/**
 * @fn PRTdecls
 */
node_st *PRTdecls(node_st *node)
{
    TRAVchildren(node);

    // printf("\n-----------Printing Decls node--------------:\n");
    // char *bool_str = DECLS_NEXT(node) ? "true" : "false";
    // printf("  Has next decl: %s\n", bool_str);

    return node;
}

/**
 * @fn PRTexprs
 */
node_st *PRTexprs(node_st *node)
{
  // Go to current expr
  TRAVexpr(node);
  // Then go to the next expr
  TRAVnext(node);
    // printf("\n-----------Printing Exprs node--------------:\n");

    // char *bool_str = EXPRS_NEXT(node) ? "true" : "false";
    // printf("  Has next expr: %s\n", bool_str);

    return node;
}

/**
 * @fn PRTarrexpr
 */
node_st *PRTarrexpr(node_st *node)
{
    // NOT USED FOR NOW BECAUSE THERE ARE NO EXTENSIONS YET
    return node;
}

/**
 * @fn PRTids
 */
node_st *PRTids(node_st *node)
{
    // NOT USED FOR NOW BECAUSE THERE ARE NO EXTENSIONS YET
    return node;
}

/**
 * @fn PRTexprstmt
 */
node_st *PRTexprstmt(node_st *node)
{
    // Go to the expr node, will automatically go to the types of Expr 
    // in main.ccn and print it with this traversal for that node type
    TRAVexpr(node);
    return node;
}

/**
 * @fn PRTreturn
 */
node_st *PRTreturn(node_st *node)
{
    // Go to the expr node
    TRAVexpr(node);
    return node;
}

/**
 * @fn PRTfuncall
 */
node_st *PRTfuncall(node_st *node)
{
    
    return node;
}

/**
 * @fn PRTcast
 */
node_st *PRTcast(node_st *node)
{
    char *tmp = NULL;

    // Get the type
    switch (CAST_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }
    
    // Print cast
    printf("(%s)", tmp);

    return node;
}

/**
 * @fn PRTfundefs
 */
node_st *PRTfundefs(node_st *node)
{
    bool hasNext = FUNDEFS_NEXT(node) != NULL ? true : false;
    // Go to the fundef
    TRAVfundef(node);

    if (hasNext) {
      // Then go to the next
      TRAVnext(node);
    }
    
    return node;
}

/**
 * @fn PRTfundef
 */
node_st *PRTfundef(node_st *node)
{    
    bool isExported = FUNDEF_EXPORT(node) ? true : false;
    if (isExported) {
      // TODO: how to determine if it is export or extern????
      printf("EXPORT");
    }

    // Print function type
    char *tmp = NULL;

    // Get the type
    switch (FUNDEF_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }

    // Print spaces and function type and then function name
    printf(" %s %s", tmp, FUNDEF_NAME(node));

    // If function has params, print params
    if (FUNDEF_PARAMS(node) != NULL) {
      printf("(");
      // Print the params in between the fundef (no new lines)
      // No need for a for loop because Param is a LinkedList and the next is automatically printed there
      TRAVparams(node);
      // Close the params with a brace
      printf(")");
    } else {
      printf("()");
    }

    // If function has funbody, print funbody
    if (FUNDEF_BODY(node) != NULL) {
      // Open funbody
      printf(" {\n");
      // Print funbody
      TRAVbody(node);
      // Close funbody
      printf("\n}");
    }

    return node;
}

/**
 * @fn PRTfunbody
 */
node_st *PRTfunbody(node_st *node)
{
    // If the funbody has vardecls, print them
    if (FUNBODY_DECLS(node) != NULL) {
      // Print vardecls
      // No need for a for loop because Vardecl is a LinkedList and the next is automatically printed there
      TRAVdecls(node);
    }

    // If the funbody has statements, print them
    if (FUNBODY_DECLS(node) != NULL) {
      // Print stmts
      // No need for a for loop because Stmts is a LinkedList and the next is automatically printed there
      TRAVstmts(node);
    }
    
    return node;
}

/**
 * @fn PRTifelse
 */
node_st *PRTifelse(node_st *node)
{
    // Add the condition if the if statement has a condition
    if (IFELSE_COND(node) != NULL) {
      // Start the if statement
      printf("if (");
      // Print the expr condition
      TRAVcond(node);
      // End the if statement and start the then block
      printf(") {\n");
    } else {
      // Print an if statement without a body and start the then block
      printf("if () {\n");
    }

    // Check if it has a then block, if not do nothing (=print an empty block)
    if (IFELSE_THEN(node) != NULL) {
      TRAVthen(node);
    }

    // End the then block
    printf("\n}");

    // If it has an else block, print it
    if (IFELSE_ELSE_BLOCK(node) != NULL) {
      // Start the else block
      printf("else {\n");
      // Goes to the print traversal for the Stmts node type else_block
      TRAVelse_block(node);
      // End the else bock
      printf("\n}");
    }

    return node;
}

/**
 * @fn PRTwhile
 */
node_st *PRTwhile(node_st *node)
{
    printf("\n-----------Printing While node--------------:\n");
    printf("This node does not have a representation to print, so it is empty, there is nothing going wrong in this part!\n");

    return node;
}

/**
 * @fn PRTdowhile
 */
node_st *PRTdowhile(node_st *node)
{
    printf("\n-----------Printing DoWhile node--------------:\n");
    printf("This node does not have a representation to print, so it is empty, there is nothing going wrong in this part!\n");

    return node;
}

/**
 * @fn PRTfor
 */
node_st *PRTfor(node_st *node)
{
    printf("\n-----------Printing For node--------------:\n");
    printf("This node does not have a representation to print, so it is empty, there is nothing going wrong in this part!\n");

    return node;
}

/**
 * @fn PRTglobdecl
 */
node_st *PRTglobdecl(node_st *node)
{
    printf("\n-----------Printing GlobDecl node--------------:\n");
    char *tmp = NULL;

    // Get the type
    switch (GLOBDECL_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }
    
    printf("Globdecl name: %s\nGlobdecl type: %s", GLOBDECL_NAME(node), tmp);

    return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node)
{
    printf("\n-----------Printing GlobDef node--------------:\n");
    char *tmp = NULL;

    // Get the type
    switch (GLOBDEF_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }
    
    printf("Globdef name: %s\nGlobdef type: %s\n", GLOBDEF_NAME(node), tmp);

    char *bool_str = GLOBDEF_EXPORT(node) ? "true" : "false";
    printf("  Is exported: %s\n", bool_str);

    return node;
}

/**
 * @fn PRTparam
 */
node_st *PRTparam(node_st *node)
{
    char *tmp = NULL;

    // Get the type
    switch (PARAM_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }

    // If param has next add a comma and a space for the next param
    if (PARAM_NEXT(node) != NULL) {
      printf("%s %s, ", tmp, PARAM_NAME(node));
      // Go to the next param and print that param
      TRAVnext(node);
    } else {
      // Print the param without a comma at the end and without a space at the end
      printf("%s %s", tmp, PARAM_NAME(node));
    }

    return node;
}

/**
 * @fn PRTvardecl
 */
node_st *PRTvardecl(node_st *node)
{
    char *tmp = NULL;

    // Get the type
    switch (VARDECL_TYPE(node)) {
    case CT_int:
      tmp = "int";
      break;
    case CT_float:
      tmp = "float";
      break;
    case CT_bool:
      tmp = "bool";
      break;
    case CT_void:
      tmp = "void";
      break;
    case CT_NULL:
      DBUG_ASSERT(false, "unknown type detected!");
    }

    // TODO: how to print the expr init???
    printf("%s %s", tmp, VARDECL_NAME(node));
    // if init then = expr
    if (VARDECL_INIT(node) != NULL) {
      printf(" = ");
      // Print the expr
      TRAVinit(node);
      // End the vardecl with a semicolon (;)
      printf(";");
    }

    // If vardecl has next add a newline for the next vardecl
    if (VARDECL_NEXT(node) != NULL) {
      printf("\n");
      // Go to the next vardcel and print that vardecl using their print traversal
      TRAVnext(node);
    }

    return node;
}

/**
 * @fn PRTstmts
 */
node_st *PRTstmts(node_st *node)
{
    // Print the statement, this will automatically go to the types of Stmt 
    // in main.ccn and print it with this traversal for that node type
    TRAVstmt(node);

    // If it has a next go to those statement(s) and print them
    TRAVnext(node);

    return node;
}

/**
 * @fn PRTassign
 */
node_st *PRTassign(node_st *node)
{
    // Print the Varlet node type let if it is not NULL
    if (ASSIGN_LET(node) != NULL) {
      TRAVlet(node);
    }

    // Print the Expr node type exor if it is not NULL
    if (ASSIGN_EXPR(node) != NULL) {
      TRAVexpr(node);
    }

    return node;
}

/**
 * @fn PRTbinop
 */
node_st *PRTbinop(node_st *node)
{
    printf("\n-----------Printing Binop node--------------:\n");

    char *tmp = NULL;
    printf( "( ");

    TRAVleft(node);

    // Type of the operator
    switch (BINOP_OP(node)) {
    case BO_add:
      tmp = "+";
      break;
    case BO_sub:
      tmp = "-";
      break;
    case BO_mul:
      tmp = "*";
      break;
    case BO_div:
      tmp = "/";
      break;
    case BO_mod:
      tmp = "%";
      break;
    case BO_lt:
      tmp = "<";
      break;
    case BO_le:
      tmp = "<=";
      break;
    case BO_gt:
      tmp = ">";
      break;
    case BO_ge:
      tmp = ">=";
      break;
    case BO_eq:
      tmp = "==";
      break;
    case BO_ne:
      tmp = "!=";
      break;
    case BO_or:
      tmp = "||";
      break;
    case BO_and:
      tmp = "&&";
      break;
    case BO_NULL:
      DBUG_ASSERT(false, "unknown binop detected!");
    }

    printf( " %s ", tmp);
    
    TRAVright(node);

    printf( ")(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));

    return node;
}

/**
 * @fn PRTmonop
 */
node_st *PRTmonop(node_st *node)
{
    printf("\n-----------Printing Monop node--------------:\n");
    char *tmp = NULL;
    printf( "( ");

    TRAVoperand(node);

    // Type of the operator
    switch (MONOP_OP(node)) {
    case MO_not:
      tmp = "!";
      break;
    case MO_neg:
      tmp = "-";
      break;
    case MO_NULL:
      DBUG_ASSERT(false, "unknown monop detected!");
    }

    printf( " %s ", tmp);

    printf( ")(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));    
    
    return node;
}

/**
 * @fn PRTvarlet
 */
node_st *PRTvarlet(node_st *node)
{
    printf("\n-----------Printing Varlet node--------------:\n");

    printf("%s(%d:%d)", VARLET_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
    return node;
}

/**
 * @fn PRTvar
 */
node_st *PRTvar(node_st *node)
{
    printf("\n-----------Printing Var node--------------:\n");
    printf("%s", VAR_NAME(node));
    return node;
}

/**
 * @fn PRTnum
 */
node_st *PRTnum(node_st *node)
{
    printf("\n-----------Printing Num node--------------:\n");
    printf("%d", NUM_VAL(node));
    return node;
}

/**
 * @fn PRTfloat
 */
node_st *PRTfloat(node_st *node)
{
    printf("\n-----------Printing Float node--------------:\n");
    printf("%f", FLOAT_VAL(node));
    return node;
}

/**
 * @fn PRTbool
 */
node_st *PRTbool(node_st *node)
{
    printf("\n-----------Printing Bool node--------------:\n");
    char *bool_str = BOOL_VAL(node) ? "true" : "false";
    printf("%s", bool_str);
    return node;
}