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

// These global variables are used for typechecking for FunCall arguments
node_st *tempSteFunCallLink = NULL;
node_st *tempSteFunCallNode = NULL;
int tempArgumentIndex = 0;

// Helper function to check if an argument type is the same as the parameter type
bool compareFunCallArgumentsTypes(enum Type argumentType) {
    // Check if the link is not NULL
    if (tempSteFunCallLink != NULL) {
        // Check if there are any params
        if (STEFUN_PARAMS(tempSteFunCallLink) != NULL) {
            // Get the first param from the SteFun node
            node_st *paramIterator = STEFUN_PARAMS(tempSteFunCallLink);
            int counter = 0;
            // Go to the nTh argument using the linkedlist of the Params
            do {
                // Found parameter in SteFun link
                if (counter == tempArgumentIndex) {
                    if (argumentType == PARAM_TYPE(paramIterator)) {
                        // Return true if the argument and the corresponding parameter type match
                        return true;
                    }
                }

                // Update parameter and counter
                paramIterator = PARAM_NEXT(paramIterator);
                counter++;
            } while (paramIterator != NULL && counter <= tempArgumentIndex);
        } else {
            // No params in FunDef, so no types to check, return true
            return true;
        }
    }
    
    // Not equal argument and parameter type
    return false;
}
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
// Helper function to get the type signature of the Binop built-in operators
enum Type getTypeSignatureBinOp(enum Type firstType, enum Type secondType, enum BinOpEnum operator) {
    /*
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

    if (firstType != NULL && secondType != NULL && operator != NULL) {
        // Use BinOp

        /*
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
        */
        if (operator == BO_add) {

        } else if (operator == BO_sub) {
            
        } else if (operator == BO_mul) {
            
        } else if (operator == BO_div) {
            
        } else if (operator == BO_mod) {
            
        }

        /*
        Relational operators:
        
        'T' denotes any basic type (bool, int, or float)
        The relational operators for equality and inequality are defined on all basic types
        On Boolean operands they complement strict logic disjunction and conjunction 
        in supporting all potential relationships between two Boolean values
        '==' : T x T -> bool, where T is any basic type
        '!=' : T x T -> bool, where T is any basic type
        The remaining four relational operators are only defined for integer and floating point numbers as operand values
        '<' : int x int -> bool
        '<' : float x float -> bool
        '<=' : int x int -> bool
        '<=' : float x float -> bool
        '>' : int x int -> bool
        '>' : float x float -> bool
        '>=' : int x int -> bool
        '>=' : float x float -> bool
        */
        if (operator == BO_eq) {
            
        } else if (operator == BO_ne) {

        } else if (operator == BO_lt) {

        } else if (operator == BO_le) {
            
        } else if (operator == BO_gt) {
            
        } else if (operator == BO_ge) {
            
        }

        /*
        Logical operators:

        '&&' : bool x bool -> bool (short-circuits evaluation)
        '||' : bool x bool -> bool (short-circuits evaluation)
        */
        if (operator == BO_and) {
            
        } else if (operator == BO_or) {

        }
    }

    // No type signature found, return NULL
    return CT_NULL; // CT_NULL is the NULL type
}

// Helper function to get the type signature of the Binop built-in operators
enum Type getTypeSignatureMonOp(enum Type firstType, enum MonOpEnum operator) {
    // Create type signatures for MonOp nodes
    if (firstType != NULL && operator != NULL) {
        /*
         Unary operators:
        '-' : int -> int
        '-' : float -> float
        // TODO: can unary minus be done on bool values???
        // '-' : bool x bool -> bool (implements negation)
        '!' : bool -> bool
        */
        if (operator == MO_neg) {
            // unary minus (-, MO_neg), arithmetic negation, used for arithmetic values (=numbers, etc)
            if (firstType == CT_int) {
                printf("unary minus on int -> -\n");
                return CT_int;
            } else if (firstType == CT_float) {
                printf("unary minus on float -> -\n");
                return CT_float;
            }
        } else if (operator == MO_not) {
            // logical negation (!, MO_not), used for boolean values (true, false)
            if (firstType == CT_bool) {
                printf("bool logical negation -> !\n");
                return CT_bool;
            }
        }
    }

    // No type signature found, return NULL
    return CT_NULL; // CT_NULL is the NULL type
}

// Helper function to check for condition type of statements
bool checkConditionExpression(enum Type conditionType, char *statementType) {
    if (conditionType == CT_bool) {
        // Return true if the condition expression is of type Boolean
        return true;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in %s: condition is not a bool expression", statementType);
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return false;
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
    // Traverse the VarDecls
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
    // printf("assign in typechecking\n");

    // Traverse the expr type to infer the type of the expression
    TRAVexpr(node);

    // Get the varlet type from the Ste's link and compar it with the expr type
    if (tempType != STEVAR_TYPE(VARLET_STE_LINK(ASSIGN_LET(node)))) {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in assignment %s", VARLET_NAME(ASSIGN_LET(node)));
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type
    
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

    // TODO: remove after debugging
    char *printexprType = getTypeForPrinting(tempType);
    //printf("expr type of if else is: %s\n", printexprType);

    // Check if the condition expr is a Boolean, if so, traverse into then and else block
    if (checkConditionExpression(tempType, "if-statement")) {
        TRAVthen(node);
        TRAVelse_block(node);
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type

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
    if (checkConditionExpression(tempType, "while-loop")) {
        TRAVblock(node);
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type

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
    if (checkConditionExpression(tempType, "dowhile-loop")) {
        TRAVblock(node);
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type

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
    // Save the tempType variable to save the stop expression type
    enum Type forStopExprType = tempType;
    // Reset global type helper variable before going to the next for Expr
    tempType = CT_NULL;

    // Then traverse into the step expression to find the step Expression type 
    TRAVstep(node);
    // Save the tempType variable to save the step expression type
    enum Type forStepExprType = tempType;

    // Check if the stop expr is an Integer, if so, traverse into the loop body
    if (forStopExprType == CT_int && forStepExprType == CT_int) {
        TRAVblock(node);
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in for-loop: stop and/or step expressions is not an int expression");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type

    return node;
}

/**
 * @fn TMAFreturn
 *
 * Case return: ...
 */
node_st *TMAFreturn(node_st *node)
{
    // TODO: what to do here with the return????

    TRAVexpr(node);

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
    // Start the tempArgumentIndex at 0
    tempArgumentIndex = 0;
    // Save the FunCall link to use for checking the arguments
    tempSteFunCallLink = FUNCALL_STE_LINK(node);
    // Save the FunCall node itself for giving a specific type error
    tempSteFunCallNode = node;
    // Then, traverse to the arguments to infer the type of each argument using these variables
    TRAVargs(node);

    // Reset global type helper variables after traversing arguments
    tempType = CT_NULL; // CT_NULL is the NULL type
    tempSteFunCallLink = NULL;
    tempSteFunCallNode = NULL;
    tempArgumentIndex = 0;

    // Yield function return type after checking arguments
    tempType = STEFUN_TYPE(FUNCALL_STE_LINK(node));
    
    // TODO: remove after debugging
    // char *printingType = getTypeForPrinting(STEFUN_TYPE(FUNCALL_STE_LINK(node)));
    // printf("return type for funcall is: %s\n", printingType);

    return node;
}

/**
 * @fn TMAFexprs
 *
 * With basic exprs is only used for FunCall arguments
 */
node_st *TMAFexprs(node_st *node)
{
    // Traverse the first expr
    TRAVexpr(node);
    // Save the tempType variable to save the stop expression type
    enum Type currentArgumentType = tempType;

    // Then check if the current argument type matches the corresponding parameter type
    if (!compareFunCallArgumentsTypes(currentArgumentType)) {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in funcall '%s': argument number %d's type does not match corresponding parameter type",
            FUNCALL_NAME(tempSteFunCallNode), (tempArgumentIndex+1));
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    } 

    // Increment the argument index before the next to find the corresponding parameter in the FunDef node
    tempArgumentIndex++;
    // Reset global type helper variable before going to the next argument
    tempType = CT_NULL;
    // Then, do the same for the next argument
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

    // Update this operator node with the type signature just obtained to use later in code generation
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
    // Save the tempType variable to save expression type
    enum Type monopExprType = tempType;

    // Yield operator result type (use helper function)
    enum Type inferedTypeMonOp = getTypeSignatureMonOp(monopExprType, MONOP_OP(node));
    if (inferedTypeMonOp != NULL) {
        // Save the infered operator type to the global helper variable
        tempType = inferedTypeMonOp;
        // Update this operator node with the type signature just obtained to use later in code generation
        MONOP_OPERATOR_TYPE_SIGNATURE(node) = inferedTypeMonOp;
        // TODO
    }    

    return node;
}

/**
 * @fn TMAFvar
 *
 */
node_st *TMAFvar(node_st *node)
{
    // Yield type from Ste link
    tempType = STEVAR_TYPE(VAR_STE_LINK(node));

    return node;
}

/**
 * @fn TMAFnum
 *
 * Case IntConstant: Yield int
 */
node_st *TMAFnum(node_st *node)
{    
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
    // Yield bool
    tempType = CT_bool;

    return node;
}