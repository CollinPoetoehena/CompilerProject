/**
 * @file
 *
 * Traversal: TypeMatchingAssignmentsFunCalls
 * UID      : TMAF
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums and types, for the Type
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
// Include error functionality
#include "palm/ctinfo.h"

// Global helper variable to save the type in
enum Type tempType = CT_NULL; // CT_NULL is the NULL type

// Helper function to get the string type of the enum Type
// Define at the top to avoid C return type error
char *getTypeForPrinting(enum Type type) {
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

// TODO: create type signature lookup for built-in operators
enum Type getTypeSignatureBuiltinOperator(enum Type firstType, enum Type secondType) {
    /*
    list of all the type signatures of the operators in CiviC (see chapter 4: expression language):

    Arithmetic operators:
    '+' : int x int -> int
    '+' : float x float -> float
    '+' : bool x bool -> bool (implements strict logic disjunction)
    '-' : int x int -> int
    '-' : float x float -> float
    '*' : int x int -> int
    '*' : float x float -> float
    '*' : bool x bool -> bool (implements strict logic conjunction)
    '/' : int x int -> int
    '/' : float x float -> float
    '%' : int x int -> int

    Relational operators:
    // The relational operators for equality and inequality are defined on all basic types
    //  On Boolean operands they complement strict logic disjunction and conjunction 
    // in supporting all potential relationships between two Boolean values
    '==' : T x T -> bool, where T is any basic type
    '!=' : T x T -> bool, where T is any basic type
    // The remaining four relational operators are only defined for integer and floating point numbers as operand values
    '<' : int x int -> bool
    '<' : float x float -> bool
    '<=' : int x int -> bool
    '<=' : float x float -> bool
    '>' : int x int -> bool
    '>' : float x float -> bool
    '>=' : int x int -> bool
    '>=' : float x float -> bool

    Logical operators:
    '&&' : bool x bool -> bool (short-circuits evaluation)
    '||' : bool x bool -> bool (short-circuits evaluation)
    
    Unary operators:
    '-' : int -> int
    '-' : float -> float
    // TODO: can unary minus be done on bool values???
    // '-' : bool x bool -> bool (implements negation)
    '!' : bool -> bool

    Note: 'x' denotes the Cartesian product, and 'T' denotes any basic type (bool, int, or float).

    Explanation about Strict logic disjunction and conjunction:
        Strict logic disjunction and conjunction are logical operations that implement the logical OR 
        and AND operations on Boolean operands. However, in the case of strict logic disjunction and 
        conjunction, the operators are defined as arithmetic operators for addition and multiplication, respectively, 
        and not as logical operators. This means that they operate on Boolean values as if they were integers, 
        with the value true being treated as 1 and the value false being treated as 0.

        In strict logic disjunction, the result is true if either or both operands are true, and false otherwise. 
        It is implemented by the addition operator (+).

        In strict logic conjunction, the result is true only if both operands are true, and false otherwise. 
        It is implemented by the multiplication operator (*).
    */

    // TODO: if secondType is NULL, then do unary operators, otherwise binop operators
    if (firstType != NULL && secondType != NULL) {
        // Use BinOp
    }

    if (firstType != NULL && secondType == NULL) {
        // Use MonOp
    }
}

// Helper function to reset all the temp variables
void resetTempVariables() {
    tempType = CT_NULL; // CT_NULL is the NULL type
}

// Check for argument types matching parameter types
bool compareFunCallArgumentsTypes(node_st *steLink) {
    // TODO: implement this function with argument types of funcall


    // If the arguments are NULL, then there are no parameter types
    if (STEFUN_PARAMS(steLink) != NULL) {
        // Get the first param from the SteFun node
        node_st *paramIterator = STEFUN_PARAMS(steLink);
        do {
            // TODO: add check for funcall argument

            // Update parameter
            paramIterator = PARAM_NEXT(paramIterator);
        } while (paramIterator != NULL);
    }
    
    // Got through every check, types are correct
    return true;
}

/**
 * @fn TMAFfundef
 */
node_st *TMAFfundef(node_st *node)
{
    // Foreach function definition: Traverse into function body:
    TRAVbody(node);

    return node;
}

/**
 * @fn TMAFfunbody
 */
node_st *TMAFfunbody(node_st *node)
{
    // Traverse the VarDecls for init expressions
    // TODO: necessary??? because of regular assignments traversal???
    TRAVdecls(node);

    // Traverse into the Stmts
    TRAVstmts(node);

    return node;
}

/**
 * @fn TMAFassign
 *
 * Case assignment: Infer expression type. Compare with variable type
 */
node_st *TMAFassign(node_st *node)
{
    printf("assign in typechecking\n");

    // Traverse the expr type to infer the type of the expression
    TRAVexpr(node);

    // Get the varlet type from the Ste's link and compar it with the expr type
    if (tempType != STEVAR_TYPE(VARLET_STE_LINK(ASSIGN_LET(node)))) {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in assignment %s", VARLET_NAME(ASSIGN_LET(node)));
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }
    // TODO: remove after debugging
    char *printVarLetType = getTypeForPrinting(STEVAR_TYPE(VARLET_STE_LINK(ASSIGN_LET(node))));
    char *printexprType = getTypeForPrinting(tempType);
    printf("expr type is: %s, type for assign is: %s\n", printexprType, printVarLetType);

    return node;
}

/**
 * @fn TMAFifelse
 *
 * Case if-then-else: Infer type of predicate expression: Boolean?
 * Traverse into then-branch. Traverse into else-branch
 */
node_st *TMAFifelse(node_st *node)
{
    // Traverse the expr type to infer the type of the expression
    TRAVcond(node);

    // Check if the condition expr is a Boolean, if so, traverse into then and else block
    // TODO: add check
    if (true) {
        TRAVthen(node);
        TRAVelse_block(node);
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in if-else statement: condition is not a Boolean expression");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn TMAFwhile
 *
 * Case while-/do-loop:
 * Infer type of predicate expression: Boolean?
 * Traverse into loop body
 */
node_st *TMAFwhile(node_st *node)
{
    // Traverse the expr type to infer the type of the expression
    TRAVcond(node);

    // Check if the condition expr is a Boolean, if so, traverse into the loop body
    // TODO: add check
    if (true) {
        TRAVblock(node);
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in while loop: condition is not a Boolean expression");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn TMAFdowhile
 *
 * Case while-/do-loop:
 * Infer type of predicate expression: Boolean?
 * Traverse into loop body
 */
node_st *TMAFdowhile(node_st *node)
{
    // Traverse the expr type to infer the type of the expression
    TRAVcond(node);

    // Check if the condition expr is a Boolean, if so, traverse into the loop body
    // TODO: add check
    if (true) {
        TRAVblock(node);
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in do-while loop: condition is not a Boolean expression");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn TMAFfor
 *
 * Case for-loop:
 * Infer types of bound/step expressions: Integer?
 * Traverse into loop body
 */
node_st *TMAFfor(node_st *node)
{
    // Traverse the expr type to infer the type of the expression
    TRAVstop(node);
    // Then traverse into the step expression to find the step Expression type 
    TRAVstep(node);

    // Check if the stop expr is an Integer, if so, traverse into the loop body
    // TODO: add check
    if (true && true) {
        TRAVblock(node);
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in for loop: stop or step expression is not an Integer expression");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn TMAFreturn
 *
 * Case return: ...
 */
node_st *TMAFreturn(node_st *node)
{
    // TODO: what to do here????
    return node;
}

/*
*************************************************************************************************************************************************
This part is for the type inference of the Expr
TODO: is this correct or does it need to be in a separate traversal??
*/
/**
 * @fn TMAFcast
 */
node_st *TMAFcast(node_st *node)
{
    // TODO: what to do with cast expression????
    //TRAVexpr(node);

    // Yield the type of the Cast for now
    tempType = CAST_TYPE(node);

    return node;
}

/**
 * @fn TMAFfuncall
 *
 * Case FunCall: Foreach argument expression: Infer argument type.
 * Compare with corresponding parameter type. Yield function return type.
 */
node_st *TMAFfuncall(node_st *node)
{
    // Traverse to the arguments to infer the type of each argument
    TRAVargs(node);

    // Compare with corresponding parameter types of fundef
    // TODO: maybe use SteFuns for it???? Implement the function
    //compareFunCallArgumentsTypes(FUNCALL_STE_LINK(node));

    // Yield function return type
    // TODO: remove after debugging
    char *printingType = getTypeForPrinting(STEFUN_TYPE(FUNCALL_STE_LINK(node)));
    printf("return type for funcall is: %s\n", printingType);

    return node;
}

/**
 * @fn TMAFexprs
 */
node_st *TMAFexprs(node_st *node)
{
    TRAVexpr(node);
    TRAVnext(node);

    return node;
}

/**
 * @fn TMAFbinop
 *
 * Case BinOp: Infer left operand type. Infer right operand type. 
 * Yield operator result type
 */
node_st *TMAFbinop(node_st *node)
{
    // Infer left operand type
    TRAVleft(node);

    // Infer right operand type
    TRAVright(node);

    // Yield operator result type (use helper function)
    // TODO

    return node;
}

/**
 * @fn TMAFmonop
 *
 * Case MonOp: Infer operand type. Yield operator result type
 */
node_st *TMAFmonop(node_st *node)
{
    // Infer operand type
    TRAVoperand(node);

    // Yield operator result type (use helper function)
    // TODO

    return node;
}

/**
 * @fn TMAFnum
 *
 * Case IntConstant: Yield int
 */
node_st *TMAFnum(node_st *node)
{
    printf("num node in typechecking\n");
    
    // Yield int
    tempType = CT_int;

    return node;
}

/**
 * @fn TMAFfloat
 *
 * Case FloatConstant: Yield float
 */
node_st *TMAFfloat(node_st *node)
{
    printf("float node in typechecking\n");

    // Yield float
    tempType = CT_float;

    return node;
}

/**
 * @fn TMAFbool
 *
 * Case BoolConstant: Yield bool
 */
node_st *TMAFbool(node_st *node)
{
    printf("bool node in typechecking\n");
        
    // Yield bool
    tempType = CT_bool;

    return node;
}