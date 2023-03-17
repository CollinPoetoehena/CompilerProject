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
// Include hash tables and memory from Palm
#include "palm/hash_table.h"
#include "palm/memory.h"

// Global helper variable to save the fundef type in to use for checking return type
node_st *tempFundefSteLink = NULL;

// Global helper variable to save the type in
enum Type tempType = CT_NULL; // CT_NULL is the NULL type

// Save the currentFunCallIndex to use for getting the last funcall node from the hash table
int currentFunCallIndex = 0;
// This pointer variable is used to get something from the hash table
int *currentFunCallIndexHashTablePointer = NULL;

void TMAFinit() { 
    // initialize hash table, ensures there is a hash table
    // Use Int hash tables to work with an index, this way we can support funcalls with the same name
    htable_st *hash_table_paramIndex = HTnew_Int(100);
    htable_st *hash_table_funCallCount = HTnew_Int(100);

    // Get the hash table from the travdata of the TMAF traversal
    struct data_tmaf *data = DATA_TMAF_GET();
    //data->funcalls_id_stelink = hash_table;
    data->funcalls_funcallIndex_paramIndex = hash_table_paramIndex;
    data->funcalls_funcallIndex_node = hash_table_funCallCount;

    return; 
}
void TMAFfini() { return; }

// Helper function to check if an argument type is the same as the parameter type
bool compareFunCallArgumentsTypes(enum Type argumentType, int paramIndex, node_st *steLink) {
    // Check if the link is not NULL
    if (steLink != NULL) {
        // Check if there are any params
        if (STEFUN_PARAMS(steLink) != NULL) {
            // Get the first param from the SteFun node
            node_st *paramIterator = STEFUN_PARAMS(steLink);
            int counter = 0;
            // Go to the nTh argument using the linkedlist of the Params
            do {
                // Found parameter in SteFun link
                if (counter == paramIndex) {
                    if (argumentType == PARAM_TYPE(paramIterator)) {
                        // Return true if the argument and the corresponding parameter type match
                        return true;
                    }
                }

                // Update parameter and counter
                paramIterator = PARAM_NEXT(paramIterator);
                counter++;
            } while (paramIterator != NULL && counter <= paramIndex);
        } else {
            // No params in FunDef, so no types to check, return true
            return true;
        }
    }
    
    // Not equal argument and parameter type
    return false;
}

// Helper function to get the type signature of the BinOp built-in operators
enum Type getTypeSignatureBinOp(enum Type firstType, enum Type secondType, enum BinOpEnum operator) {
    // Check if the variables are not NULL to avoid Segmentation fault and bugs
    if (firstType != CT_NULL && secondType != CT_NULL && operator != BO_NULL) {
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
        if (operator == BO_add || operator == BO_mul) {
            // Addition and Multiplication can be performed on int, float and bool
            if (firstType == CT_int && secondType == CT_int) {
                return CT_int;
            } else if (firstType == CT_float && secondType == CT_float) {
                return CT_float;
            } else if (firstType == CT_bool && secondType == CT_bool) {
                return CT_bool;
            }
        } else if (operator == BO_sub || operator == BO_div) {
            // Subtraction and Division can be performed on int and float
            if (firstType == CT_int && secondType == CT_int) {
                return CT_int;
            } else if (firstType == CT_float && secondType == CT_float) {
                return CT_float;
            }
        } else if (operator == BO_mod) {
            // Modulo can only be performed on int
            if (firstType == CT_int && secondType == CT_int) {
                return CT_int;
            }
        }

        /*
        Relational operators:
        
        'T' denotes any basic type (bool, int, or float)
        The relational operators for equality and inequality are defined on all basic types
        On Boolean operands they complement strict logic disjunction and conjunction 
        in supporting all potential relationships between two Boolean values.
        
        '==' : T x T -> bool, where T is any basic type, where T must be the same as the other T after x
        '!=' : T x T -> bool, where T is any basic type, where T must be the same as the other T after x

        The remaining four relational operators are only defined for integer and floating point numbers as operand values.
        '<' : int x int -> bool
        '<' : float x float -> bool
        '<=' : int x int -> bool
        '<=' : float x float -> bool
        '>' : int x int -> bool
        '>' : float x float -> bool
        '>=' : int x int -> bool
        '>=' : float x float -> bool
        */
        if (operator == BO_eq || operator == BO_ne) {
            // equal and not equal expressions can be of any basic type in any combination (int, float, bool)
            if ((firstType == CT_int || firstType == CT_float || firstType == CT_bool) &&
                ((secondType == CT_int || secondType == CT_float || secondType == CT_bool))) {
                return CT_bool;
            }
        } else if (operator == BO_lt || operator == BO_le || operator == BO_gt || operator == BO_ge) {
            // The remaining 4 relational operators can be performed on int or float and yield bool
            if (firstType == CT_int && secondType == CT_int) {
                return CT_bool;
            } else if (firstType == CT_float && secondType == CT_float) {
                return CT_bool;
            }
        }

        /*
        Logical operators:

        '&&' : bool x bool -> bool (short-circuits evaluation)
        '||' : bool x bool -> bool (short-circuits evaluation)
        */
        if (operator == BO_and || operator == BO_or) {
            // Logical operators can only be performed on bool
            if (firstType == CT_bool && secondType == CT_bool) {
                return CT_bool;
            }
        }
    }

    // No type signature found, return NULL
    return CT_NULL; // CT_NULL is the NULL type
}

// Helper function to get the type signature of the MonOp built-in operators
enum Type getTypeSignatureMonOp(enum Type firstType, enum MonOpEnum operator) {
    // Create type signatures for MonOp nodes
    if (firstType != CT_NULL && operator != MO_NULL) {
        /*
        Unary operators:
        '-' : int -> int
        '-' : float -> float
        '!' : bool -> bool
        */
        if (operator == MO_neg) {
            // unary minus (-, MO_neg), arithmetic negation, used for arithmetic values (=numbers, etc)
            if (firstType == CT_int) {
                return CT_int;
            } else if (firstType == CT_float) {
                return CT_float;
            }
        } else if (operator == MO_not) {
            // logical negation (!, MO_not), used for boolean values (true, false)
            if (firstType == CT_bool) {
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
 *
 * Foreach function definition: Traverse into function body:
 */
node_st *TMAFfundef(node_st *node)
{
     // Save the fundef return type by using the Ste
    tempFundefSteLink = FUNDEF_SYMBOL_TABLE(node);

    // Then, traverse into function body
    TRAVbody(node);

    // Reset global type helper variable for the FunDef type at the end
    tempFundefSteLink = NULL;

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
    // Traverse the expr type to infer the type of the expression
    TRAVexpr(node);

    // Get the varlet type from the Ste's link and compar it with the expr type
    if (tempType != STEVAR_TYPE(VARLET_STE_LINK(ASSIGN_LET(node)))) {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in assignment: %s", VARLET_NAME(ASSIGN_LET(node)));
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

    // If the step expression is not NULL, check that type to, otherwise skip that part
    enum Type forStepExprType;
    if (FOR_STEP(node) != NULL) {
        // Then traverse into the step expression to find the step Expression type 
        TRAVstep(node);
        // Save the tempType variable to save the step expression type
        forStepExprType = tempType;
    }

    if (FOR_STEP(node) != NULL) {
        // Perform checks with step expression (no step expr in the for synax means NULL step Expr)
        if (forStopExprType == CT_int && forStepExprType == CT_int) {
            // Check if the stop expr is an Integer, if so, traverse into the loop body
            TRAVblock(node);
        } else {
            // Prints the error when it occurs, so in this line
            CTI(CTI_ERROR, true, "type error in for-loop: stop and/or step expression is not an int expression");
            // Create error action, will stop the current compilation at the end of this Phase
            CCNerrorPhase();
        }
    } else {
        // Perform checks without step expression is it is NULL
        if (forStopExprType == CT_int) {
            // Check if the stop expr is an Integer, if so, traverse into the loop body
            TRAVblock(node);
        } else {
            // Prints the error when it occurs, so in this line
            CTI(CTI_ERROR, true, "type error in for-loop: stop expression is not an int expression");
            // Create error action, will stop the current compilation at the end of this Phase
            CCNerrorPhase();
        }
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type

    return node;
}

/**
 * @fn TMAFreturn
 *
 * Case return: check return type with fundef return type
 */
node_st *TMAFreturn(node_st *node)
{
    // If the expression is not NULL check for a type, otherwise use void (== return;)
    if (RETURN_EXPR(node) != NULL) {
        // Traverse the expr to also find potential type signatures for BinOps or MonOps
        TRAVexpr(node);
    } else {
        tempType = CT_void;
    }

    // Check with FunDef node type
    if (tempFundefSteLink != NULL) {
        // Void function does not have a return type
        if (STEFUN_TYPE(tempFundefSteLink) == CT_void && 
            (tempType == CT_bool || tempType == CT_int || tempType == CT_float)) {
            // Prints the error when it occurs, so in this line
            CTI(CTI_ERROR, true, "type error in return statement for function '%s'", STEFUN_NAME(tempFundefSteLink));
            // Create error action, will stop the current compilation at the end of this Phase
            CCNerrorPhase();
        } else if (tempType != STEFUN_TYPE(tempFundefSteLink) && STEFUN_TYPE(tempFundefSteLink) != CT_void) {
            // Prints the error when it occurs, so in this line
            CTI(CTI_ERROR, true, "type error in return statement for function '%s'", STEFUN_NAME(tempFundefSteLink));
            // Create error action, will stop the current compilation at the end of this Phase
            CCNerrorPhase();
        }
    }

    // Reset global type helper variable at the end
    tempType = CT_NULL; // CT_NULL is the NULL type
    
    return node;
}

/*
*************************************************************************************************************************************************
This part is for the type inference of the Expr
*/
/**
 * @fn TMAFcast
 */
node_st *TMAFcast(node_st *node)
{
    // First traverse the expr to save the type signature of potential BinOp or MonOp nodes!
    TRAVexpr(node);

    // Yield the type of the Cast
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
    // Check if the link is correctly added in ContextAnalysis
    if (FUNCALL_STE_LINK(node) != NULL && FUNCALL_ARGS(node) != NULL) {
        // Get the hash table from the travdata of the TMAF traversal
        struct data_tmaf *data = DATA_TMAF_GET();

        // Increment currentFunCallIndex for every funcall before saving it to the hash table
        currentFunCallIndex++;

        // Update funcall count index before traversing to the args to find the funcall node
        // initialize the currentFunCallIndex to use in the hash tables to find funcall names
        int *funcallCountHashTable = MEMmalloc(sizeof(int));
        // Dereference funcallCount and make it equal to the global helper variable of type int
        *funcallCountHashTable = currentFunCallIndex;

        // Insert the current FunCall node to the hash table with its current index
        HTinsert(data->funcalls_funcallIndex_node, funcallCountHashTable, (void *) node);
        currentFunCallIndexHashTablePointer = funcallCountHashTable;

        // Allocate new memory for an int in C to create a new memory block
        int *newArgumentIndexCounter = MEMmalloc(sizeof(int));
        // Dereference newArgumentIndexCounter pointer and make it equal to 0 before traversing the args
        *newArgumentIndexCounter = 0;
        // First save the new name and newArgumentIndexCounter in the hash table (for every funcall)
        // Cast to void * because the parameter of the HTinsert is of type void *
        HTinsert(data->funcalls_funcallIndex_paramIndex, funcallCountHashTable, (void *) newArgumentIndexCounter);

        // Then traverse the args
        TRAVargs(node);

        // After traversing the args, remove this entry from the hash table, to support another funcall
        HTremove(data->funcalls_funcallIndex_paramIndex, funcallCountHashTable);
        HTremove(data->funcalls_funcallIndex_node, funcallCountHashTable);
        // Decrement the currentFunCallIndex after traversing args of a FunCall
        currentFunCallIndex--;

        // Yield function return type after checking arguments
        tempType = STEFUN_TYPE(FUNCALL_STE_LINK(node));
    } else {
        // If the FunCall node does not have args then just yield the return type of the FunDef
        tempType = STEFUN_TYPE(FUNCALL_STE_LINK(node));
    }

    return node;
}

/**
 * @fn TMAFexprs
 *
 * With basic exprs is only used for FunCall arguments
 */
node_st *TMAFexprs(node_st *node)
{
    // Get the hash table from the travdata of the TMAF traversal
    struct data_tmaf *data = DATA_TMAF_GET();
    // Get the current FunCall node to use for checking
    node_st *currentFunCallNode = (node_st *) HTlookup(data->funcalls_funcallIndex_node, currentFunCallIndexHashTablePointer);
    // Get the param count from the hash table to check the corresponding param
    int *currentParamIndexFunCall = (int *) HTlookup(data->funcalls_funcallIndex_paramIndex, currentFunCallIndexHashTablePointer);

    // Get the SteLink to use for checking the parameters with
    node_st *currentSteLink = FUNCALL_STE_LINK(currentFunCallNode);
    
    // Traverse the expr of this argument to find the type
    TRAVexpr(node);
    // Save the tempType variable to save the type of the argument
    enum Type currentArgumentType = tempType;

    // Check the types of the corresponding parameters
    bool typeCheckResult = compareFunCallArgumentsTypes(currentArgumentType, *currentParamIndexFunCall, currentSteLink);
    // Dereference the currentParamIndexFunCall and increment it by one for the next param
    *currentParamIndexFunCall = *currentParamIndexFunCall + 1;

    // Then check if the current argument type matches the corresponding parameter type
    if (currentFunCallNode != NULL && !typeCheckResult) {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error in funcall '%s': argument number %d's type does not match corresponding parameter type",
            FUNCALL_NAME(currentFunCallNode), (*currentParamIndexFunCall));
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    // Reset global type helper variable before going to the next argument
    tempType = CT_NULL;
    // Then, do the same for the next argument (which can also be a new FunCall node)
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
    // Save the tempType variable to save expression type
    enum Type binopLeftExprType = tempType;

    // Then, infer right operand type
    TRAVright(node);
    // Save the tempType variable to save expression type
    enum Type binopRightExprType = tempType;

    // Yield operator result type (use helper function)
    enum Type inferedTypeBinOp = getTypeSignatureBinOp(binopLeftExprType, binopRightExprType, BINOP_OP(node));
    if (inferedTypeBinOp != CT_NULL) {
        // Save the infered operator type to the global helper variable
        tempType = inferedTypeBinOp;
        // Update this operator node with the type signature just obtained to use later in code generation
        BINOP_OPERATOR_TYPE_SIGNATURE(node) = inferedTypeBinOp;
    } else {
        // If the function returned CT_NULL than it could not infer a type, so error!
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error: could not infer type of binary operator!");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

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
    if (inferedTypeMonOp != CT_NULL) {
        // Save the infered operator type to the global helper variable
        tempType = inferedTypeMonOp;
        // Update this operator node with the type signature just obtained to use later in code generation
        MONOP_OPERATOR_TYPE_SIGNATURE(node) = inferedTypeMonOp;
    } else {
        // If the function returned CT_NULL than it could not infer a type, so error!
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "type error: could not infer type of monary operator!");
        // Create error action, will stop the current compilation at the end of this Phase
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn TMAFvar
 *
 * Case var: get type from Ste and yield that type
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