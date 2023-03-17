/**
 * @file
 *
 * This file contains the code for the Print traversal.
 * The traversal has the uid: PRT
 * You want to print the program to look almost exactly the same like the run file, but then with the AST nodes
 * Some programs print an extra new line for example, but it does not change anything about the functionality!
 * Some prints are not perfect, such as a funcall always ends with a ;, but it does not change anything to the 
 * functionality so therefore it is not fixed because it would take a lot of time to fix with little result,
 * this is a choice we made to have as much time for our compiler and still have the functionality of print.c to test our parser
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "palm/memory.h"
#include  <string.h>
#include "palm/dbug.h"
// Include enums, for the Type 
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"

// Helper function to get the string type of the enum Type
// Define at the top to avoid C return type error
char *getPrintType(enum Type type) {
  // Get the type
  char *printType = NULL;

  switch (type) {
    case CT_int:
    printType = "int";
    break;
    case CT_float:
    printType = "float";
    break;
    case CT_bool:
    printType = "bool";
    break;
    case CT_void:
    printType = "void";
    break;
    case CT_NULL:
    DBUG_ASSERT(false, "unknown type detected!");
  }

  return printType;
}

/**
 * @fn PRTprogram
 *
 */
node_st *PRTprogram(node_st *node)
{ 
    // Print a couple of new lines before printing the print traversal
    printf("\n\n\n****************************************************************************************************************************************************************************** \
    \t\tStart of the print traversal:\n\n");

    /*
    Uncomment and comment the ones you do and do not want to print!
    This is left here with a purpose for teachers to if they would like to see the Ste's!
    */
    // Print the ste's for the global variables and global fundefs here on the top!
    // printSteVarChain(PROGRAM_FIRST_STE_VARIABLES(node));
    // printSteFunChain(PROGRAM_FIRST_STE_FUNCTIONS(node));

    // Go to child and print it
    TRAVdecls(node);

    // End the Print traversal
    printf("\n\n\t\tEnd of the print traversal\n****************************************************************************************************************************************************************************** \
    \n\n");
        
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
 * @fn PRTfundef
 */
node_st *PRTfundef(node_st *node)
{    
    // Get function type
    char *tmp = getPrintType(FUNDEF_TYPE(node));

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

    /*
    Uncomment and comment the ones you do and do not want to print!
    This is left here with a purpose for teachers to if they would like to see the Ste's!
    */
    // Print the ste's of the variables as a structured comment
    // printSteVarChain(FUNDEF_FIRST_STE_VARIABLES(node));
    // // Print its own symbol table for its function definition
    // printOneSteFun(FUNDEF_SYMBOL_TABLE(node));

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
      // Print the arguments, these are not printed with spaces, they are Exprs so keep that in mind!
      TRAVargs(node);
      // End the funcall arguments
      printf(")");
    } else {
      printf("()");
    }

    // End funcall with a semicolon and a new line
    printf(";\n");

    /*
    Uncomment and comment the ones you do and do not want to print!
    This is left here with a purpose for teachers to if they would like to see the Ste's!
    */
    // Print the SteFun link to this VarLet node
    // if (FUNCALL_STE_LINK(node) != NULL) {
    //   printOneSteFun(FUNCALL_STE_LINK(node));
    // }

    return node;
}

/**
 * @fn PRTvarlet
 */
node_st *PRTvarlet(node_st *node)
{
    // Print varlet (variable in assignment)
    printf("%s", VARLET_NAME(node));

    /*
    Uncomment and comment the ones you do and do not want to print!
    This is left here with a purpose for teachers to if they would like to see the Ste's!
    */
    // Print the SteVar link to this VarLet node
    if (VARLET_STE_LINK(node) != NULL) {
      printOneSteVar(VARLET_STE_LINK(node));
    }

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

    /*
    Uncomment and comment the ones you do and do not want to print!
    This is left here with a purpose for teachers to if they would like to see the Ste's!
    */
    // Print the SteVar link to this Var node
    if (VAR_STE_LINK(node) != NULL) {
      printOneSteVar(VAR_STE_LINK(node));
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
      // Separate the next with a COMMA (,)
      printf(", ");
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
 * @fn PRTcast
 */
node_st *PRTcast(node_st *node)
{
    char *tmp = getPrintType(CAST_TYPE(node));
    
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
    if (FUNBODY_STMTS(node) != NULL) {
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

    // Go to the traversal function of the while block
    TRAVblock(node);

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
    printf("for (");

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
    char *tmp = getPrintType(GLOBDECL_TYPE(node));

    // Print Global declaration
    printf("extern %s %s;", tmp, GLOBDECL_NAME(node));
    
    return node;
}

/**
 * @fn PRTglobdef
 */
node_st *PRTglobdef(node_st *node)
{
    char *tmp = getPrintType(GLOBDEF_TYPE(node));

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
    char *tmp = getPrintType(PARAM_TYPE(node));

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
    char *tmp = getPrintType(VARDECL_TYPE(node));

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
    /*
    Print the statement, this will automatically go to the types of Stmt 
    in main.ccn and print it with this traversal for that node type
    Print new line before statement
    */
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
 * @fn PRTternaryop
 */
node_st *PRTternaryop(node_st *node)
{
    // Start TernaryOp
    printf( "( ");

    // Print predicate expression
    TRAVpredicate(node);

    // Print operator
    printf( " ? ");
    
    // Print then expression
    TRAVthen_expr(node);

    // Print operator
    printf( " : ");

    // Print else expression
    TRAVelse_expr(node);

    // End binop
    printf( " )");

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

/**
 * @fn PRTstefun
 */
node_st *PRTstefun(node_st *node)
{
    // Nothing to print here, printing Ste's are handled by a different function
    return node;
}

/**
 * @fn PRTstevar
 */
node_st *PRTstevar(node_st *node)
{
    // Nothing to print here, printing Ste's are handled by a different function
    return node;
}

// Print one SteVar
void printOneSteVar(node_st *steVarNode) {
  if (steVarNode != NULL) {
    // Open the new SteVar node
    printf("\n****************************************************\n\tNew SteVar link:\n");

    // Get the type
    char *type = getPrintType(STEVAR_TYPE(steVarNode));

    // Print var Ste: "name, type"
    printf("SteVar:\n %s : %s\nnesting level: %d\n", 
        STEVAR_NAME(steVarNode), type, STEVAR_NESTING_LEVEL(steVarNode));

    // End the current SteVar chain
    printf("\n\tEnd of SteVar link\n****************************************************\n");
  }
}

/*
  Prints a chain of SteVar's using the LinkedList structure.
  This is easier to use then printing it in the traversal functions of the SteVar
  because this allows to have the chain printed in one function, this is for clarity and readability.
  This also gives more control in the print traversal to print a single SteVar or a whole chain.
*/ 
void printSteVarChain(node_st *steVarFirstNode) {
  if (steVarFirstNode != NULL) {
    // Open the new SteVar chain
    printf("\n****************************************************\n\tNew SteVar chain:\n");

    // Print the parent Ste node's name if it has a parent
    if (STEVAR_PARENT(steVarFirstNode) != NULL) {
          printf("Parent Ste node's name: %s\n\n", STEVAR_NAME(STEVAR_PARENT(steVarFirstNode)));
    }

    // Get the first param from the Ste
    node_st *steIterator = steVarFirstNode;
    do {
        // Get the type
        char *type = getPrintType(STEVAR_TYPE(steIterator));

        // Print var Ste: "name, type"
        printf("SteVar:\n %s : %s\nnesting level: %d\n", 
            STEVAR_NAME(steIterator), type, STEVAR_NESTING_LEVEL(steIterator));

        // Update iterator
        steIterator = STEVAR_NEXT(steIterator);
    } while (steIterator != NULL);

    // End the current SteVar chain
    printf("\n\tEnd of SteVar chain\n****************************************************\n\n");
  }
}

// Helper function to get params types chain of an SteFun (declar above usage to avoid C type error!)
char *getSteFunParamTypes(node_st *steFunNode) {
  // Allocate memory for a string of up to 99 characters
  char *params = MEMmalloc(100 * sizeof(char)); 
  // Initialize with empty string to avoid weird memory address value being used at the start
  strcpy(params, "");
  
  if (STEFUN_PARAMS(steFunNode) != NULL) {
      // Get the first param from the Ste
      node_st *paramIterator = STEFUN_PARAMS(steFunNode);
      do {
          // Get the param type
          char *paramType = getPrintType(PARAM_TYPE(paramIterator));
          // Add the param to the params string to print the fundef
          strcat(params, paramType);
          // Add a comma after every value, except the last one
          if (PARAM_NEXT(paramIterator) != NULL) {
              strcat(params, ", ");
          }

          // Update parameter
          paramIterator = PARAM_NEXT(paramIterator);
      } while (paramIterator != NULL);
  }

  return params;
}

// Print one SteFun
void printOneSteFun(node_st *steFunNode) {
  if (steFunNode != NULL) {
    // Open the new SteVar node
    printf("\n****************************************************\n\tOne SteFun:\n");

    // Get the type
    char *type = getPrintType(STEFUN_TYPE(steFunNode));
    char *paramsTypes = getSteFunParamTypes(steFunNode);

    // Print function Ste: "funName: returnType (param types)"
    printf("SteFun:\n %s : %s (%s)\nnesting level: %d\n", 
        STEFUN_NAME(steFunNode), type, paramsTypes, STEFUN_NESTING_LEVEL(steFunNode));

    // End the current SteVar chain
    printf("\n\tEnd of one SteFun\n****************************************************\n");
  }
}

/*
  Prints a chain of SteFun's using the LinkedList structure.
  This is easier to use then printing it in the traversal functions of the SteFun
  because this allows to have the chain printed in one function, this is for clarity and readability.
  This also gives more control in the print traversal to print a single SteFun or a whole chain.
*/ 
void printSteFunChain(node_st *steFunFirstNode) {
  if (steFunFirstNode != NULL) {
    // Open the new SteFun chain
    printf("\n****************************************************\n\tNew SteFun chain:\n");

    // Basic has no nested functions, so no need to print the parent because it is always NULL for now

    // Get the first param from the Ste
    node_st *steIterator = steFunFirstNode;
    do {
        // Get the return type of the FunDef
        char *type = getPrintType(STEFUN_TYPE(steIterator));
        char *paramsTypes = getSteFunParamTypes(steIterator);

        // Print function Ste: "funName: returnType (param types)"
        printf("SteFun:\n %s : %s (%s)\nnesting level: %d\n", 
            STEFUN_NAME(steIterator), type, paramsTypes, STEFUN_NESTING_LEVEL(steIterator));

        // Update iterator
        steIterator = STEVAR_NEXT(steIterator);
    } while (steIterator != NULL);

    // End the current SteFun chain
    printf("\n\tEnd of SteFun chain\n****************************************************\n\n");
  }
}