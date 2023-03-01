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
 * @fn PRTste
 */
node_st *PRTste(node_st *node)
{
    return node;
}

/**
 * @fn PRTprogram
 */
node_st *PRTprogram(node_st *node)
{
    // You want to print the program to look almost exactly the same like the run file, but then with the AST nodes
    // Some programs print an extra new line for example, but it does not change anything about the functionality!

    // Go to child and print it
    TRAVdecls(node);

    // Print a new line at the end of the program
    printf("\n");

    // TODO: float values are float types but rounded, why is that!?!?
    //  ./civicc ../test/basic/check_success/boolop.cvc 

    // TODO: do_while is not parsed well, see files with these commands:
    // Possible problem: empty funbody does not seem to work with stmts, with a vardecl it works!
    // ./civicc ../test/basic/check_success/parse_do_while.cvc

    // TODO: these file is also not working, also funbody and block not working that is not working, also with vardecl it works!
    // ./civicc ../test/basic/check_success/params_funcall.cvc
    // ./civicc ../test/basic/check_success/parse_for.cvc 
    // ./civicc ../test/basic/check_success/parse_funbody.cvc 
    // ./civicc ../test/basic/check_success/parse_funcall.cvc

    // This file is not working because of whitespace probably, why?? and same applies with the funbody, need to add vardecl, why???
    // ./civicc ../test/basic/check_success/parse_if_else.cvc 
    // The rest of the files are all working (maybe the print is not perfect sometimes with an extra new line, but that does not change anything!)
    
    // TODO: add indentation global variable, add a function that has a parameter int tabs to print tabs!
    
    return node;
}

/**
 * @fn PRTdecls
 */
node_st *PRTdecls(node_st *node)
{
    // Print the declaration, this will automatically go to the types of Decl 
    // in main.ccn and print it with this traversal for that node type
    TRAVdecl(node);

    // Then, if it has a next go to those declaration(s) and print them
    if (DECLS_NEXT(node) != NULL) {
      // Print new line for next decl
      printf("\n");
      TRAVnext(node);
    }

    return node;
}

/**
 * @fn PRTexprs
 */
node_st *PRTexprs(node_st *node)
{
    // Go to current expr
    TRAVexpr(node);

    // Then go to the next expr, if there is a next
    if (EXPRS_NEXT(node) != NULL) {
      TRAVnext(node);
    }

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
    // Print return
    printf("return");

    // Go to the print traversal function for the expr child to print it, if is not NULL
    if (RETURN_EXPR(node) != NULL) {
      // Start with a space
      printf(" ");
      TRAVexpr(node);
    }

    // End return statement
    printf(";");

    return node;
}

/**
 * @fn PRTfuncall
 */
node_st *PRTfuncall(node_st *node)
{
    printf("%s", FUNCALL_NAME(node));

    // IF the function call has arguments, print them, otherwise just use ()
    if (FUNCALL_ARGS(node) != NULL) {
      // Start the funcall arguments
      printf("(");
      // Print the arguments
      TRAVargs(node);
      // End the funcall arguments
      printf(")");
    } else {
      printf("()");
    }

    // End funcall with a semicolon and a new line
    printf(";\n");

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

    // Print expression after type cast
    TRAVexpr(node);

    return node;
}

/**
 * @fn PRTfundefs
 */
node_st *PRTfundefs(node_st *node)
{
    // Go to the fundef print traversal function and print it
    TRAVfundef(node);

    if (FUNDEFS_NEXT(node) != NULL) {
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
    // Get function type
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

    // No funBody means that it is a FunDeclaration, so print that, else print FunDefinition
    if (FUNDEF_BODY(node) != NULL) {
      bool isExported = FUNDEF_EXPORT(node) ? true : false;
      if (isExported) {
        // Print export with a space
        printf("export ");
      }

      // Print spaces and function type and then function name
      printf("%s %s", tmp, FUNDEF_NAME(node));

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

      // Open funbody
      printf(" {\n");
      // Print funbody
      TRAVbody(node);
      // Close funbody
      printf("\n}");
    } else {
      // FunDeclaration is always extern
      printf("extern %s %s", tmp, FUNDEF_NAME(node));

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

      printf("\n");
    }

    // If the funbody has statements, print them
    if (FUNBODY_DECLS(node) != NULL) {
      // Print stmts
      // No need for a for loop because Stmts is a LinkedList and the next is automatically printed there
      TRAVstmts(node);

      printf("\n");
    }

    // Print nothing if it is an empty function body
    
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
    // Add the condition while the while statement has a condition
    if (WHILE_COND(node) != NULL) {
      // Start the while statement
      printf("while (");
      // Print the expr condition
      TRAVcond(node);
      // End the while statement and start the block
      printf(") {\n");
    } else {
      // Print a while statement without a body and start the block
      printf("while () {\n");
    }

    // End the block
    printf("\n}");

    return node;
}

/**
 * @fn PRTdowhile
 */
node_st *PRTdowhile(node_st *node)
{
    // Start the do statement
    printf("do {\n");

    // Add the block if it has a block
    if (DOWHILE_BLOCK(node) != NULL) {
      // Print the Stmts block
      TRAVblock(node);
    }

    // End the do statement
    printf("\n} ");

    // Add the while statement
    if (WHILE_COND(node) != NULL) {
      // Start the while statement
      printf("while (");
      // Print the expr condition
      TRAVcond(node);
      // End the while statement
      printf(");");
    } else {
      // Print a while statement without a expr condition
      printf("while ();");
    }

    return node;
}

/**
 * @fn PRTfor
 */
node_st *PRTfor(node_st *node)
{
    // Start the for statement
    printf("for (int %s = ", FOR_VAR(node));
    // Print the start expression
    TRAVstart_expr(node);

    // Print the stop expression
    printf(", ");
    TRAVstop(node);

    // Print the step expression if it is present
    if (FOR_STEP(node) != NULL) {
      // Print step expression
      printf(", ");
      TRAVstep(node);
    }
    
    // End start if statement and start for block
    printf(") {\n");

    // Print Stmts block if it has any
    if (FOR_BLOCK(node) != NULL) {
      // Print the block
      TRAVblock(node);
    }

    // End for loop block
    printf("\n}");

    return node;
}

/**
 * @fn PRTglobdecl
 */
node_st *PRTglobdecl(node_st *node)
{
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

    // Print Global declaration
    printf("extern %s %s;", tmp, GLOBDECL_NAME(node));
    
    return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node)
{
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

    // Print export with a space if it is exported
    if (GLOBDEF_EXPORT(node)) {
      printf("export ");
    }

    // Print type and id
    printf("%s %s", tmp, GLOBDEF_NAME(node));

    // Print expression if there is any
    if (GLOBDEF_INIT(node) != NULL) {
      printf(" = ");
      // Print the expr
      TRAVinit(node);
    }

    // End the globdef with a semicolon (;) and a new line
    printf(";\n");

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

    printf("%s %s", tmp, VARDECL_NAME(node));
    // if init then print: "= expr"
    if (VARDECL_INIT(node) != NULL) {
      printf(" = ");
      // Print the expr
      TRAVinit(node);
    }
    
    // End the vardecl with a semicolon (;)
    printf(";");

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
    // Print new line before statement
    TRAVstmt(node);

    // Then, if it has a next go to those statement(s) and print them
    if (STMTS_NEXT(node) != NULL) {
      // Print new line for next stmts
      printf("\n");
      TRAVnext(node);
    }

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

    // Print the assignment operator
    printf(" = ");

    // Print the Expr node type exor if it is not NULL
    if (ASSIGN_EXPR(node) != NULL) {
      TRAVexpr(node);
    }

    // End assignment with a semicolon and a new line
    printf(";\n");

    return node;
}

/**
 * @fn PRTbinop
 */
node_st *PRTbinop(node_st *node)
{
    char *tmp = NULL;

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

    // Start binop
    printf( "( ");

    // Print left expression
    TRAVleft(node);

    // Print operator
    printf( " %s ", tmp);
    
    // Print right expression
    TRAVright(node);

    // End binop
    printf( " )");

    // This prints it with the locations
    // printf( ")(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));

    return node;
}

/**
 * @fn PRTmonop
 */
node_st *PRTmonop(node_st *node)
{
    char *tmp = NULL;

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

    // Start monop
    printf( "( ");

    // Print monop operator (in front of expression with a monop)
    printf( " %s ", tmp);

    // Print expression
    TRAVoperand(node);
    
    // End monop
    printf( " )");

    // This prints it with the locations
    // printf( ")(%d:%d-%d)", NODE_BLINE(node), NODE_BCOL(node), NODE_ECOL(node));    
    
    return node;
}

/**
 * @fn PRTvarlet
 */
node_st *PRTvarlet(node_st *node)
{
    // Print varlet (variable in assignment)
    printf("%s", VARLET_NAME(node));

    // This prints it with the locations
    // printf("%s(%d:%d)", VARLET_NAME(node), NODE_BLINE(node), NODE_BCOL(node));
    return node;
}

/**
 * @fn PRTvar
 */
node_st *PRTvar(node_st *node)
{
    // Print var (variable in an expression)
    printf("%s", VAR_NAME(node));

    return node;
}

/**
 * @fn PRTnum
 */
node_st *PRTnum(node_st *node)
{
    // Print num (= int) value
    printf("%d", NUM_VAL(node));

    return node;
}

/**
 * @fn PRTfloat
 */
node_st *PRTfloat(node_st *node)
{
    // Print float value
    printf("%f", FLOAT_VAL(node));
    return node;
}

/**
 * @fn PRTbool
 */
node_st *PRTbool(node_st *node)
{
    // Print boolean value, represented by a string
    char *bool_str = BOOL_VAL(node) ? "true" : "false";
    printf("%s", bool_str);
    
    return node;
}