/**
 * @file
 *
 * Traversal: AssemblyCodeGeneration
 * UID      : ACG
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include the globals.h for the global output file
#include "global/globals.h"
// Include FILE * from stdio.h in C to work with files
#include <stdio.h>
// Palm library for easy working with strings
#include "palm/str.h"
#include  <string.h>
// Include error functionality
#include "palm/ctinfo.h"
// Include enums, for the Type 
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
// Include memory from Palm to work with memory
#include "palm/memory.h"
#include "palm/dbug.h"

// Save the index of the constant in a global variable to use for creation assembly
int constantIndex = 0;
// Save the index of the VarDecls and Params (local vars) in a global variable to use for creation assembly
int localParamVarDeclsIndex = 0;
// Save the index of the global VarDecls in a global variable to use for creation assembly
int globalVarDeclIndex = 0;
// This is used for the import table index, the above is for the global table
int importTableIndex = 0;
// Global helper variable to save the label index of the current label (starts at 1)
int labelIndex = 1;

// This global variable is used for the number of extern functions (to use in FunCall later)
// Counter variable for functions in this program not necessary, jump to them with the label funName!
int externFunsIndex = 0;

// This helper variable is used to keep track of the number of args for the funcall
int tempFunCallArgsCount = 0;

// Save the current fundef first SteVar to use for return instruction
node_st *currentSteFunFunDef = NULL;

// // This string is used to store all the pseudo instructions for functions in
char *pseudoInstructionsString = NULL;

// This function is performed at the start of the traversal
void ACGinit() {
    // Initialize file pointer, ensures there is a file.
    // Use the global.output_file from globals in CoCoNut to write the assembly to
    FILE *file = fopen(global.output_file, "w");

    // Check if the file is not NULL
    if (file != NULL) {
        // Get the file pointer from the travdata of the ACG traversal and update it
        struct data_acg *data = DATA_ACG_GET();
        data->assembly_output_file = file;
    } else {
        // File is NULL, so failed to get the file, give an error
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "global.output_file for assembly code generation not found");
        // Create error action, will stop the current compilation at the end of this Action
        CCNerrorAction();
    }
    
    return;
}

// This function is performed at the end of the traversal
void ACGfini() {
    // Get the file pointer from the travdata of the ACG traversal and update it
    struct data_acg *data = DATA_ACG_GET();

    // Close the file at the end of the traversal
    if (data->assembly_output_file != NULL) {
        fclose(data->assembly_output_file);
    }

    return;
}

// Helper function to get the string type of the enum Type for assembly instructions
// Define at the top to avoid C return type error
char *getOperandTypeAssembly(enum Type type) {
    // Get the type
    char *assemblyType = NULL;

    // Get the type
    switch (type) {
        case CT_int:
            assemblyType = "i";
            break;
        case CT_float:
            assemblyType = "f";
            break;
        case CT_bool:
            assemblyType = "b";
            break;
        case CT_void:
            // void is empty, such as 'return' for a void return
            assemblyType = "";
            break;
        case CT_NULL:
            DBUG_ASSERT(false, "unknown type detected!");
    }

    return assemblyType;
}

// Helper function to get the string type of the enum Type for printing
char *getTypeForSignature(enum Type type) {
    // Get the type
    char *printType = NULL;

    // Get the type
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

// Helper function to get the function signature from an SteFun
char *getFunctionSignatureFromSte(node_st *steFun) {
    // Check if the steFun is not NULL
    if (STEFUN_NAME(steFun) != NULL) {
        // Escape the " with a backslash
        char *functionSignatureString = STRcat("", "\"");
        // Append the function name
        functionSignatureString = STRcat(functionSignatureString, STEFUN_NAME(steFun));
        // Append the " by escaping it again, add a space at the end for the return type
        functionSignatureString = STRcat(functionSignatureString, "\" ");
        // Append the return type
        functionSignatureString = STRcat(functionSignatureString, getTypeForSignature(STEFUN_TYPE(steFun)));
        // Append all the parameter types if it has any parameter
        if (STEFUN_PARAMS(steFun) != NULL) {
            // Get the first param from the SteFun node
            node_st *paramIterator = STEFUN_PARAMS(steFun);
            do {
                // Append the type of the param into the function signature, also append a space per type
                functionSignatureString = STRcat(
                    functionSignatureString,
                    STRcat(" ", getTypeForSignature(PARAM_TYPE(paramIterator)))
                );

                // Update parameter
                paramIterator = PARAM_NEXT(paramIterator);
            } while (paramIterator != NULL);
        }

        // Return the build function signature string
        return functionSignatureString;

    }

    // No function signature created, return NULL
    return NULL;
}

// Helper function to get the number of variables in a FunDef SteVar chain
int getLocalVariablesCount(node_st *firstSteVarNode) {
    if (firstSteVarNode != NULL) {
        // Get the number of SteVar in the FunDef node
        int localVariablesCount = 0;
        // Set the first SteVar node
        node_st *steVarIterator = firstSteVarNode;
        do {
            // Increment count
            localVariablesCount++;

            // Update the iterator
            steVarIterator = STEVAR_NEXT(steVarIterator);
        } while (steVarIterator != NULL);

        // Return the number of local variables
        return localVariablesCount;
    }

    // If the first SteVar node is NULL, then the number of local variables is 0
    return 0;
}

// Helper function to get the number of arguments for a funcall node 
int getArgumentCountFuncall(node_st *firstArgsNodeFuncall) {
    if (firstArgsNodeFuncall != NULL) {
        // Get the count, start at 0
        int argsCountFuncallNode = 0;
        // Set the first SteVar node
        node_st *argsIterator = firstArgsNodeFuncall;
        do {
            // Increment count
            argsCountFuncallNode++;

            // Update the iterator
            argsIterator = STEVAR_NEXT(argsIterator);
        } while (argsIterator != NULL);

        // Return the count variable
        return argsCountFuncallNode;
    }

    // If the args node is NULL, then the number of arguments is 0
    return 0;
}

/**
 * @fn ACGprogram
 */
node_st *ACGprogram(node_st *node)
{
    // Traverse to the children
    TRAVdecls(node);

    // Print the pseudo instructions at the end of the file if they are not NULL
    struct data_acg *data = DATA_ACG_GET();
    if (pseudoInstructionsString != NULL) {
        // First print the constants pseudo instructions
        fprintf(data->assembly_output_file, "%s\n", pseudoInstructionsString);
    }

    return node;
}

/**
 * @fn ACGdecls
 */
node_st *ACGdecls(node_st *node)
{
    // Traverse to the children
    TRAVdecl(node);
    TRAVnext(node);

    return node;
}

/*
***********************************************************************************************************************************************
These nodes are Decl nodes
*/

/**
 * @fn ACGglobdecl
 */
node_st *ACGglobdecl(node_st *node)
{
    // Create the pseudo instruction for the global and append it to already present instructions
    char *globdeclNameForPseudo = STRcat("\"", STRcat(GLOBDECL_NAME(node), "\" "));
    pseudoInstructionsString = STRcat(
        STRcat(
            STRcat(
                STRcat(
                    pseudoInstructionsString,
                    ".importvar "
                ), globdeclNameForPseudo
            ), getTypeForSignature(GLOBDECL_TYPE(node))
        ), "\n"
    );

    // Set extern to true to use the correct assembly instruction in the var and VarLet later
    STEVAR_IS_EXTERNAL(GLOBDECL_SYMBOL_TABLE(node)) = true;
    // Get the SteVar of this global decl and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(GLOBDECL_SYMBOL_TABLE(node)) = importTableIndex;
    // Increment the global vars index for the next global vardecl
    importTableIndex++;

    return node;
}

/**
 * @fn ACGglobdef
 */
node_st *ACGglobdef(node_st *node)
{   
    // Check if the variable is exported, if so add to the export table
    if (GLOBDEF_EXPORT(node)) {
        // Create the pseudo instruction for the global and append it to already present instructions
        char *globdefNameForPseudo = STRcat("\"", STRcat(GLOBDEF_NAME(node), "\" "));
        pseudoInstructionsString = STRcat(
            STRcat(
                STRcat(
                    STRcat(
                        pseudoInstructionsString,
                        ".exportvar "
                    ), globdefNameForPseudo
                ), STRitoa(globalVarDeclIndex)
            ), "\n"
        );
    }
    // Then append the .global pseudo instruction of this globdecl
    pseudoInstructionsString = STRcat(
        STRcat(
            STRcat(
                pseudoInstructionsString,
                ".global "
            ), getTypeForSignature(GLOBDEF_TYPE(node))
        ), "\n"
    );

    // Get the SteVar of this global decl and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(GLOBDEF_SYMBOL_TABLE(node)) = globalVarDeclIndex;
    // Increment the global vars index for the next global vardecl at the end
    globalVarDeclIndex++;

    // Traverse to the init Expr, probably nothing here because it is separated with RegularAssignments
    TRAVinit(node);
    
    return node;
}

/**
 * @fn ACGfundef
 */
node_st *ACGfundef(node_st *node)
{
    // First check if the FunDef is a FunDec node (funbody is NULL and extern, handled in parser already)
    // If it is, it needs to be imported
    if (FUNDEF_IS_FUNDECL(node)) {
        // Append the function import to the pseudo instructions string
        char *functionSignature = getFunctionSignatureFromSte(FUNDEF_SYMBOL_TABLE(node));
        pseudoInstructionsString = STRcat(
            STRcat(
                pseudoInstructionsString,
                STRcat(".importfun ", functionSignature)
            ), "\n"
        );

        // Get the SteFun of this FunDef and update it with the assembly index to use later
        STEFUN_ASSEMBLY_INDEX(FUNDEF_SYMBOL_TABLE(node)) = externFunsIndex;
        // Increment the globalFunsIndex for the next FunDef
        externFunsIndex++;
        // Set extern to true to use in FunCall node
        STEFUN_IS_EXTERNAL(FUNDEF_SYMBOL_TABLE(node)) = true;
    } else {
        /*
        Append the function signature to the pseudo instructions string if it is exported
        Or the function is "__init" because this needs to be guarenteed exported
        An exported function also ends with the function label name at the end with a space in front
        */
        if (FUNDEF_EXPORT(node) || strcmp(FUNDEF_NAME(node), "__init") == 0) {
            char *functionSignature = getFunctionSignatureFromSte(FUNDEF_SYMBOL_TABLE(node));
            pseudoInstructionsString = STRcat(
                STRcat(
                    STRcat(pseudoInstructionsString, STRcat(".exportfun ", functionSignature)),
                    STRcat(" " ,FUNDEF_NAME(node))
                ), "\n"
            );
        }

        // Reset global counter for localParamVarDeclsIndex for every fundef (constantsIndex and others not necessary)
        localParamVarDeclsIndex = 0;

        // Set the current FunDef SteFun link to use for traversing the children of this fundef
        currentSteFunFunDef = FUNDEF_SYMBOL_TABLE(node); 

        // Start the FunDef node with its label (the name of the FunDef)
        struct data_acg *data = DATA_ACG_GET();
        fprintf(data->assembly_output_file, "%s:\n", FUNDEF_NAME(node));

        // Then create the 'esr' instruction with the number of local variables
        // Get the number of local variables to use in the 'esr' instruction
        int localVariablesCount = getLocalVariablesCount(FUNDEF_FIRST_STE_VARIABLES(node));
        // Only load the esr instruction if the variable count is greater than 0
        if (localVariablesCount > 0) {
            fprintf(data->assembly_output_file, "esr %d\n", localVariablesCount);
        }
        
        // First traverse the params (the first local variables are the params)
        TRAVparams(node);
        // Then traverse the body
        TRAVbody(node);

        // Check if the function is a void function, if so, add a 'return' instruction
        if (FUNDEF_TYPE(node) == CT_void) {
            fprintf(data->assembly_output_file, "return\n");
        }

        // Print a new line at the end of every FunDef
        fprintf(data->assembly_output_file, "\n");
    }

    return node;
}

/*
***********************************************************************************************************************************************
These nodes are children of the FunDef node
*/

/**
 * @fn ACGfunbody
 */
node_st *ACGfunbody(node_st *node)
{
    // Traverse into the children
    TRAVdecls(node);
    TRAVstmts(node);

    return node;
}

/**
 * @fn ACGparam
 */
node_st *ACGparam(node_st *node)
{
    // TODO: what to do here?? Probably nothing right

    // Get the SteVar of this Param and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(PARAM_SYMBOL_TABLE(node)) = localParamVarDeclsIndex;
    // Increment the vardecls index for the next VarDecl
    localParamVarDeclsIndex++;

    // Traverse the next param
    TRAVnext(node);

    return node;
}

/*
***********************************************************************************************************************************************
These nodes are children of the FunBody node
*/

/**
 * @fn ACGvardecl
 */
node_st *ACGvardecl(node_st *node)
{
    // Get the SteVar of this VarDecl and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(VARDECL_SYMBOL_TABLE(node)) = localParamVarDeclsIndex;
    // Increment the vardecls index for the next VarDecl
    localParamVarDeclsIndex++;

    // Traverse into the children
    TRAVinit(node);
    TRAVnext(node);

    return node;
}

/**
 * @fn ACGstmts
 */
node_st *ACGstmts(node_st *node)
{
    // TODO: remove after creating it
    // In the slides it said traverse down to the last statement, but it meant the last statement in the line, so
    // basically the last expression
    // TODO:
    // But in this traversal it can probably be easier because you are writing the file from top to bottom, so 
    // the order is already correct, so you can just write the program into assembly in the file from top to 
    // bottom most of the time as well!

    // TODO: this is probably finished, so the above can be removed

    // Traverse the Stmt
    TRAVstmt(node);

    // Traverse the next Stmts
    TRAVnext(node);

    return node;
}

/*
***********************************************************************************************************************************************
These are the statement nodes (Stmt)
*/

/**
 * @fn ACGassign
 */
node_st *ACGassign(node_st *node)
{    
    // First traverse the Expr
    TRAVexpr(node);

    // Then traverse the VarLet to store the expression result in the VarLet
    TRAVlet(node);

    return node;
}

/**
 * @fn ACGexprstmt
 */
node_st *ACGexprstmt(node_st *node)
{
    // Traverse the Expr
    TRAVexpr(node);

    return node;
}

/**
 * @fn ACGifelse
 */
node_st *ACGifelse(node_st *node)
{
    // First traverse the condition Expr
    TRAVcond(node);

    struct data_acg *data = DATA_ACG_GET();
    // Jump to else if the condition is false by adding the following instruction
    int currentLabelIndexElse = labelIndex;
    fprintf(data->assembly_output_file, "branch_f %d_else\n", currentLabelIndexElse);
    // Increment the label after creating a label
    labelIndex++;

    // If the condition is true, then the above will be skipped and the then block should be executed
    TRAVthen(node);
    // Append a jump to the end of the ifelse at the end of the then block to skip the else instructions
    int currentLabelIndexEnd = labelIndex;
    fprintf(data->assembly_output_file, "jump %d_end\n", currentLabelIndexEnd);
    // Increment the label after creating a label
    labelIndex++;

    // Create the else label and the instructions for the else block
    fprintf(data->assembly_output_file, "%d_else:\n", currentLabelIndexElse);
    // Traverse the else block to create the assembly instructions
    TRAVelse_block(node);

    // Create the end label at the end of the ifelse node, everything after will be in here
    fprintf(data->assembly_output_file, "%d_end:\n", currentLabelIndexEnd);


    // TODO: does something need to be done when there is no else or??? Test that if it still works!
    return node;
}

/**
 * @fn ACGwhile
 */
node_st *ACGwhile(node_st *node)
{
    // TODO: condition should only be evaluated once in the assembly instructions, this is done before. 
    // See how the reference compiler does this. This is what is causing the issue from 
    // ./civicc ../test/basic_added_tests/functional/cast.cvc -o test
    // TODO: it is with the for loop evaluation, so therefore it is only with that part, so fix it, the final test!
    // TODO: this is probably not the same for the do-while, but first fix it with the while, because it is probably
    // with the for loop conversion, can be done in assembly.
    // TODO: then finally look at the do-while to see if that is going correctly, compare with reference compiler.

    // // Then first traverse the condition Expr for a while loop
    // TRAVcond(node);

    // // First create a label for the while loop
    // struct data_acg *data = DATA_ACG_GET();
    // int currentLabelIndexWhile = labelIndex;
    // fprintf(data->assembly_output_file, "%d_while:\n", currentLabelIndexWhile);
    // // Increment the label after creating a label
    // labelIndex++;
    
    // // Then create a conditional jump to the end of the while loop if the condition is false
    // int currentLabelIndexEnd = labelIndex;
    // fprintf(data->assembly_output_file, "branch_f %d_end\n", currentLabelIndexEnd);
    // // Increment the label after creating a label
    // labelIndex++;

    // // Then traverse the block
    // TRAVblock(node);
    // // Append a jump to the start of the while loop again at the end of the block
    // fprintf(data->assembly_output_file, "jump %d_while\n", currentLabelIndexWhile);

    // // Create the end label at the end of the while loop, everything after will be in here
    // fprintf(data->assembly_output_file, "%d_end:\n", currentLabelIndexEnd);

    // TODO: old implementation revert to this one if it does not

    // First create a label for the while loop
    struct data_acg *data = DATA_ACG_GET();
    int currentLabelIndexWhile = labelIndex;
    fprintf(data->assembly_output_file, "%d_while:\n", currentLabelIndexWhile);
    // Increment the label after creating a label
    labelIndex++;

    // Then first traverse the condition Expr for a while loop
    TRAVcond(node);
    
    // Then create a conditional jump to the end of the while loop if the condition is false
    int currentLabelIndexEnd = labelIndex;
    fprintf(data->assembly_output_file, "branch_f %d_end\n", currentLabelIndexEnd);
    // Increment the label after creating a label
    labelIndex++;

    // Then traverse the block
    TRAVblock(node);
    // Append a jump to the start of the while loop again at the end of the block
    fprintf(data->assembly_output_file, "jump %d_while\n", currentLabelIndexWhile);

    // Create the end label at the end of the while loop, everything after will be in here
    fprintf(data->assembly_output_file, "%d_end:\n", currentLabelIndexEnd);

    return node;
}

/**
 * @fn ACGdowhile
 */
node_st *ACGdowhile(node_st *node)
{    
    // First create a label for the do-while loop
    struct data_acg *data = DATA_ACG_GET();
    int currentLabelIndex = labelIndex;
    fprintf(data->assembly_output_file, "%d_doWhile:\n", currentLabelIndex);
    // Increment the label after creating a label
    labelIndex++;

    // Then first traverse the block for a do-while loop
    TRAVblock(node);

    // Then traverse the condition Expr
    TRAVcond(node);

    // Then create a conditional jump back to the do-while loop if the condition is true
    fprintf(data->assembly_output_file, "branch_t %d_doWhile\n", currentLabelIndex);

    return node;
}

/**
 * @fn ACGfor
 */
node_st *ACGfor(node_st *node)
{
    // For loops have been converted to While nodes, so nothing needs to be done here
    // because there are no For nodes left when this traversal is performed

    // TODO: remove after testing and creation, this prints if there is a For node!
    printf("For node found in ACG, this is not what you want!!!!\n");

    return node;
}

/**
 * @fn ACGreturn
 */
node_st *ACGreturn(node_st *node)
{
    // First, traverse the return Expr
    TRAVexpr(node);

    // Then save the return assembly instruction after traversing the return Expr
    struct data_acg *data = DATA_ACG_GET();

    // Check if the function is a void function, if not, print the instruction
    // the 'return' instruction for a void function is handled in the fundef traversal
    if (STEFUN_TYPE(currentSteFunFunDef) != CT_void) {
        // Get the return type of the current fundef
        char *assemblyTypeString = getOperandTypeAssembly(STEFUN_TYPE(currentSteFunFunDef));
        // Append the type infront of the return instruction (void type will automatically become 'return')
        fprintf(data->assembly_output_file, STRcat(assemblyTypeString, "return\n"));
    }

    return node;
}

/*
***********************************************************************************************************************************************
These are the operator nodes (also part of Expr, Operations)
*/

/**
 * @fn ACGbinop
 *
 */
node_st *ACGbinop(node_st *node)
{
    // First traverse into the left operand
    TRAVleft(node);

    // Then traverse into the right operand
    TRAVright(node);

    // Allocate memory for a string of up to 99 characters
    char *binopInstructionSymbol = MEMmalloc(100 * sizeof(char)); 
    // Initialize with empty string to avoid weird memory address value being used at the start
    strcpy(binopInstructionSymbol, "");

    // Get the type signature and push the correct instruction symbol
    // Add the correct type in front of the build up string
    if (BINOP_OPERATOR_TYPE_SIGNATURE(node) != CT_NULL) {
        char *assemblyTypeString = getOperandTypeAssembly(BINOP_OPERATOR_TYPE_SIGNATURE(node));
        // Logical operators have the type of their operand, so also get that type
        char *leftOperandTypeBinop = getOperandTypeAssembly(BINOP_LEFT_OPERAND_TYPE(node));
        if (assemblyTypeString != NULL && leftOperandTypeBinop != NULL) {
            // Then append the the type with the type of the operator assembly instruction
            // AND (&&) and OR (||) operators are omitted because they are transformed into TernaryOp nodes!
            switch (BINOP_OP(node)) {
                case BO_add:
                    // Append the type first. Arightmetic operators have
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, assemblyTypeString), "add");
                    break;
                case BO_sub:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, assemblyTypeString), "sub");
                    break;
                case BO_mul:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, assemblyTypeString), "mul");
                    break;
                case BO_div:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, assemblyTypeString), "div");
                    break;
                case BO_mod:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, assemblyTypeString), "rem");
                    break;
                case BO_lt:
                    // Relational operators have the type of the operands
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "lt");
                    break;
                case BO_le:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "le");
                    break;
                case BO_gt:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "gt");
                    break;
                case BO_ge:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "ge");
                    break;
                case BO_eq:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "eq");
                    break;
                case BO_ne:
                    binopInstructionSymbol = STRcat(STRcat(binopInstructionSymbol, leftOperandTypeBinop), "ne");
                    break;
                case BO_NULL:
                    DBUG_ASSERT(false, "unknown binop detected!");
            }

            // Save the assembly instruction in the output file
            struct data_acg *data = DATA_ACG_GET();
            // Append a new line at the end of the instruction symbol string
            binopInstructionSymbol = STRcat(binopInstructionSymbol, "\n");
            fprintf(data->assembly_output_file, binopInstructionSymbol);

            // TODO: remove after debugging
            printf("printed binop instruction: %s\n", binopInstructionSymbol);
        }
    }

    return node;
}

/**
 * @fn ACGmonop
 *
 * Push instruction symbol
 * Traverse into operand
 */
node_st *ACGmonop(node_st *node)
{
    // First traverse into the operand
    TRAVoperand(node);

    // Allocate memory for a string of up to 99 characters
    char *monopInstructionSymbol = MEMmalloc(100 * sizeof(char)); 
    // Initialize with empty string to avoid weird memory address value being used at the start
    strcpy(monopInstructionSymbol, "");

    if (MONOP_OPERATOR_TYPE_SIGNATURE(node) != CT_NULL) {
        char *assemblyTypeString = getOperandTypeAssembly(MONOP_OPERATOR_TYPE_SIGNATURE(node));
        if (assemblyTypeString != NULL) {
            // Add the type in front of the string, such as i, then at the end it will be iadd
            monopInstructionSymbol = STRcat(monopInstructionSymbol, assemblyTypeString);
        }

        // Type of the operator
        switch (MONOP_OP(node)) {
            case MO_not:
                monopInstructionSymbol = STRcat(monopInstructionSymbol, "not");
                break;
            case MO_neg:
                monopInstructionSymbol = STRcat(monopInstructionSymbol, "neg");
                break;
            case MO_NULL:
                DBUG_ASSERT(false, "unknown monop detected!");
        }

        // Save the assembly instruction in the output file
        struct data_acg *data = DATA_ACG_GET();
        // Append a new line at the end of the instruction symbol string
        monopInstructionSymbol = STRcat(monopInstructionSymbol, "\n");
        fprintf(data->assembly_output_file, monopInstructionSymbol);
    }

    return node;
}

/**
 * @fn ACGternaryop
 */
node_st *ACGternaryop(node_st *node)
{    
    // The AND (&&) and OR (||) operators are handled here
    struct data_acg *data = DATA_ACG_GET();

    // First traverse the predicate
    TRAVpredicate(node);
    
    // Evaluate the predicate expression by adding a conditional jump to a label x_elseExpr
    // this will also skip the evaluation of the then_expr because it jumps over that part if necessary
    int currentLabelIndex = labelIndex;
    fprintf(data->assembly_output_file, "branch_f %d_elseExpr\n", currentLabelIndex);
    // Increment the label after creating a label
    labelIndex++;

    // Then create the assembly for the then_expr
    TRAVthen_expr(node);
    // Append a jump to the end of the TernaryOp to skip the elseExpr if the condition is true
    int currentLabelIndexEnd = labelIndex;
    fprintf(data->assembly_output_file, "jump %d_end\n", currentLabelIndexEnd);
    // Increment the label after creating a label
    labelIndex++;

    // Then create a label for the else expression (labelformat: "token :"")
    fprintf(data->assembly_output_file, "%d_elseExpr:\n", currentLabelIndex);
    // Then traverse the else_expr
    TRAVelse_expr(node);

    // Create the end label at the end of the ternary op, everything after this node will be in here
    fprintf(data->assembly_output_file, "%d_end:\n", currentLabelIndexEnd);

    return node;
}

/*
***********************************************************************************************************************************************
These are the nodes that have an Ste link, Var, VarLet and FunCall (has Exprs node as args child)
(also part of Expr, except VarLet is not part of Expr but belongs to Assign)
*/

/**
 * @fn ACGvarlet
 */
node_st *ACGvarlet(node_st *node)
{
    // Get the index from the SteVar link (saved in VarDecl or GlobDecl earlier)
    int varletIndex = STEVAR_ASSEMBLY_INDEX(VARLET_STE_LINK(node));

    // Save the VarLet into the assembly file. . First get the type
    char *assemblyTypeString = getOperandTypeAssembly(STEVAR_TYPE(VARLET_STE_LINK(node)));
    // Check if it is not NULL
    if (assemblyTypeString != NULL) {
        // Append the store assembly instruction to the type
        assemblyTypeString = STRcat(assemblyTypeString, "store");

        // Check if the variable is a global or a local variable
        if (STEVAR_NESTING_LEVEL(VARLET_STE_LINK(node)) > 0) {
            // If the nesting level is greater than zero, it is a local variable
            // Save the instruction in the assembly output file as a local variable (<type>store C)
            struct data_acg *data = DATA_ACG_GET();
            fprintf(data->assembly_output_file, "%s %d\n", assemblyTypeString, varletIndex);
        } else {
            // Otherwise, it is a global variable, so so the assembly instruction for loading a global (or external)
            // Check if the function is external
            if (STEVAR_IS_EXTERNAL(VAR_STE_LINK(node))) {
                // append a "e" to the instruction, external global variable
                assemblyTypeString = STRcat(assemblyTypeString, "e");
            } else {
                // append a "g" to the instruction, global variable
                assemblyTypeString = STRcat(assemblyTypeString, "g");
            }
            // Print the instruction to the assembly code file
            struct data_acg *data = DATA_ACG_GET();
            fprintf(data->assembly_output_file, "%s %d\n", assemblyTypeString, varletIndex);
        }
    }

    return node;
}

/**
 * @fn ACGcast
 */
node_st *ACGcast(node_st *node)
{
    // First traverse the expression
    TRAVexpr(node);

    // Check if the Cast expression is useless, if so, skip creation the conversion
    if (!CAST_USELESS(node)) {
        // Then check what type it is and perform the cast instruction
        struct data_acg *data = DATA_ACG_GET();
        if (CAST_TYPE(node) == CT_int) {
            printf("getting here\n");
            fprintf(data->assembly_output_file, "f2i\n");
        } else if (CAST_TYPE(node) == CT_float) {
            printf("getting here\n");
            fprintf(data->assembly_output_file, "i2f\n");
        }
    }

    return node;
}

/**
 * @fn ACGfuncall
 */
node_st *ACGfuncall(node_st *node)
{
    struct data_acg *data = DATA_ACG_GET();
    // Check if the function is external
    if (STEFUN_IS_EXTERNAL(FUNCALL_STE_LINK(node))) {
        // Initiate the global subroutine with the instruction 'isrg'
        fprintf(data->assembly_output_file, "isrg\n");
        // Then traverse the arguments
        TRAVargs(node);
        // Then jump to the external subroutine with the index of the external function
        int externalFunIndexFunCall = STEFUN_ASSEMBLY_INDEX(FUNCALL_STE_LINK(node));
        fprintf(data->assembly_output_file, "jsre %d\n", externalFunIndexFunCall);
    } else {
        // Initiate the global subroutine with the instruction 'isrg'
        fprintf(data->assembly_output_file, "isrg\n");
        // Then traverse the arguments
        TRAVargs(node);
        // Then jump to the subroutine with the number of arguments and the name of the FunDef label
        int currentFuncallArgsCount = getArgumentCountFuncall(FUNCALL_ARGS(node));
        fprintf(data->assembly_output_file, "jsr %d %s\n", currentFuncallArgsCount, STEFUN_NAME(FUNCALL_STE_LINK(node)));
    }

    return node;
}

/**
 * @fn ACGexprs
 */
node_st *ACGexprs(node_st *node)
{
    // Traverse the children to create the assembly instructions
    TRAVexpr(node);
    TRAVnext(node);

    return node;
}

/**
 * @fn ACGvar
 *
 * Local variable: push load instruction with index from symbol table
 */
node_st *ACGvar(node_st *node)
{
    // Get the index from the SteVar link (saved in VarDecl or GlobDecl earlier)
    int varIndex = STEVAR_ASSEMBLY_INDEX(VAR_STE_LINK(node));

    // Save the Var into the assembly file. First get the type
    char *assemblyTypeString = getOperandTypeAssembly(STEVAR_TYPE(VAR_STE_LINK(node)));
    // Check if it is not NULL
    if (assemblyTypeString != NULL) {
        // Append the load assembly instruction to the type
        assemblyTypeString = STRcat(assemblyTypeString, "load");

        // Check if the variable is a global or a local variable
        if (STEVAR_NESTING_LEVEL(VAR_STE_LINK(node)) > 0) {
            // If the nesting level is greater than zero, it is a local variable
            // Save the instruction in the assembly output file as a local variable (<type>load C)
            struct data_acg *data = DATA_ACG_GET();
            fprintf(data->assembly_output_file, "%s %d\n", assemblyTypeString, varIndex);
        } else {
            // Otherwise, it is a global variable, so so the assembly instruction for loading a global (or external)
            // Check if the function is external
            if (STEVAR_IS_EXTERNAL(VAR_STE_LINK(node))) {
                // append a "e" to the instruction, external global variable
                assemblyTypeString = STRcat(assemblyTypeString, "e");
            } else {
                // append a "g" to the instruction, global variable
                assemblyTypeString = STRcat(assemblyTypeString, "g");
            }
            // Print the instruction to the assembly code file
            struct data_acg *data = DATA_ACG_GET();
            fprintf(data->assembly_output_file, "%s %d\n", assemblyTypeString, varIndex);
        }
    }

    return node;
}

/*
***********************************************************************************************************************************************
These are the constant nodes: Num, Float, Bool (also part of Expr, Constants)
*/

/**
 * @fn ACGnum
 *
 * Constant: push 'loadc' instruction with index from constant table
 */
node_st *ACGnum(node_st *node)
{
    // Create the assembly instructions
    struct data_acg *data = DATA_ACG_GET();
    // Use less Bytes if possible for standard values
    if (NUM_VAL(node) == 0) {
        // Load an int constant 0, no need to update the 
        // constants index or a pseudo instruction now
        fprintf(data->assembly_output_file, "iloadc_0\n");
    } else if (NUM_VAL(node) == 1) {
        // Loda the int constant value 1
        fprintf(data->assembly_output_file, "iloadc_1\n");
    } else {
        // Otherwise create a pseudo instruction and update the constants index
        // Load the constant with the current constants index
        fprintf(data->assembly_output_file, "iloadc %d\n", constantIndex);

        // Create the pseudo instruction for the constant and append it to already present instructions
        pseudoInstructionsString = STRcat(pseudoInstructionsString, ".const int ");
        // Then concatenate the int value to it with a new line
        pseudoInstructionsString = STRcat(
            STRcat(
                pseudoInstructionsString,
                STRitoa(NUM_VAL(node))
            ), "\n"
        );

        // Increment the constantsIndex for the next constant
        constantIndex++;
    }

    return node;
}

/**
 * @fn ACGfloat
 *
 * Constant: push 'loadc' instruction with index from constant table
 */
node_st *ACGfloat(node_st *node)
{
    // Create the assembly instruction
    struct data_acg *data = DATA_ACG_GET();

    // Use less Bytes if possible for standard values
    if (FLOAT_VAL(node) == 0.0) {
        // Load a float constant 0.0, no need to update the 
        // constants index or a pseudo instruction now
        fprintf(data->assembly_output_file, "floadc_0\n");
    } else if (FLOAT_VAL(node) == 1.0) {
        // Loda the float constant value 1.0
        fprintf(data->assembly_output_file, "floadc_1\n");
    } else {
        // Otherwise create a pseudo instruction and update the constants index
        // Load the constant with the current constants index
        fprintf(data->assembly_output_file, "floadc %d\n", constantIndex);

        // Create the pseudo instruction for the constant and append it to already present instructions
        pseudoInstructionsString = STRcat(pseudoInstructionsString, ".const float ");
        // Then append the value to it. Allocate memory for a string of up to 99 characters.
        char *floatValString = MEMmalloc(100 * sizeof(char));
        // Initialize with empty string to avoid weird memory address value being used at the start
        strcpy(floatValString, ""); 
        sprintf(floatValString, "%f\n", FLOAT_VAL(node));
        // Append the float value string to the current pseudo instruction
        pseudoInstructionsString = STRcat(pseudoInstructionsString, floatValString);

        // Increment the constantsIndex for the next constant
        constantIndex++;
    }

    return node;
}

/**
 * @fn ACGbool
 *
 * Constant: push 'loadc' instruction with index from constant table
 */
node_st *ACGbool(node_st *node)
{
    struct data_acg *data = DATA_ACG_GET();

    // Check the boolean value, a constant boolean is always true or false
    if (BOOL_VAL(node)) {
        // Load a boolean constant true, no need to update the 
        // constants index or a pseudo instruction now
        fprintf(data->assembly_output_file, "bloadc_t\n");
    } else {
        // Otherwise load the boolean constant false
        fprintf(data->assembly_output_file, "bloadc_f\n");
    }

    return node;
}

/*
***********************************************************************************************************************************************
These are the symbol table entry nodes for variables and functions
*/

/**
 * @fn ACGstevar
 */
node_st *ACGstevar(node_st *node)
{
    return node;
}

/**
 * @fn ACGstefun
 */
node_st *ACGstefun(node_st *node)
{
    return node;
}


/*
***********************************************************************************************************************************************
These nodes are unused for basic, only for extensions
*/

/**
 * @fn ACGfundefs
 */
node_st *ACGfundefs(node_st *node)
{
    // NOT USED FOR BASIC, ONLY EXTENSIONS
    return node;
}


/**
 * @fn ACGarrexpr
 */
node_st *ACGarrexpr(node_st *node)
{
    // NOT USED FOR BASIC, ONLY EXTENSIONS
    return node;
}

/**
 * @fn ACGids
 */
node_st *ACGids(node_st *node)
{
    // NOT USED FOR BASIC, ONLY EXTENSIONS
    return node;
}