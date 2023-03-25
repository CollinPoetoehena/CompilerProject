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
// Save the index of the VarDecls in a global variable to use for creation assembly
int vardeclsIndex = 0;
// Save the index of the global VarDecls in a global variable to use for creation assembly
int globalVarDeclIndex = 0;
// Global helper variable to save the label index of the current label (starts at 1)
int labelIndex = 1;

// This global variable is used for the number of extern functions (to use in FunCall later)
// Counter variable for functions in this program not necessary, jump to them with the label funName!
int externFunsIndex = 0;

// This helper variable is used to keep track of the number of args for the funcall
int tempFunCallArgsCount = 0;

// Save the current fundef first SteVar to use for return instruction
node_st *currentSteFunFunDef = NULL;

// This string is used to store all the pseudo instructions for functions in
char *pseudoInstructionsFuns = NULL;
// This string is used to store all the pseudo instructions for functions in
char *pseudoInstructionsConstants = NULL;

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

        // Write to a file with 'fprintf'.
        //fprintf(data->assembly_output_file, "Hello World 2\n");

        // TODO: veel dingen kan je al direct schrijven, verzin een logica dat de juiste assembly ouput
        // tabs hoeven niet in de file, zolang de assembly maar de goede instructions heeft, maar
        // het is goed om te debuggen misschien
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

// Get the number of variables in a FunDef SteVar chain
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

/**
 * @fn ACGprogram
 */
node_st *ACGprogram(node_st *node)
{
    // **************************************************************************************************************************************
    // TODO: maybe the make check fails because of the global variables not being in travdata??
    // or you can try to reset all the global variables to 0 in the fini????
    // index is failing so maybe that is the problem???



    // TODO: remove
    // // Set the first global SteFun node to use for traversing the children
    // firstGlobalSteFunAssembly = PROGRAM_FIRST_STE_FUNCTIONS(node);

    // Traverse to the children
    TRAVdecls(node);

    // TODO: at the end of the program, print the functionSignatures pseudo instructions??? (See CiviC_VM last pages!)

    // Print the pseudo instructions at the end of the file if they are not NULL
    struct data_acg *data = DATA_ACG_GET();
    if (pseudoInstructionsConstants != NULL) {
        // First print the constants pseudo instructions
        fprintf(data->assembly_output_file, "%s\n", pseudoInstructionsConstants);
    }
    if (pseudoInstructionsFuns != NULL) {
        // Then print the function pseudo instructions
        fprintf(data->assembly_output_file, "%s\n", pseudoInstructionsFuns);
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
    // No children for basic here

    // Get the SteVar of this global decl and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(GLOBDECL_SYMBOL_TABLE(node)) = globalVarDeclIndex;
    // Increment the global vars index for the next global vardecl
    globalVarDeclIndex++;

    // TODO

    return node;
}

/**
 * @fn ACGglobdef
 */
node_st *ACGglobdef(node_st *node)
{

    // TODO:
    // Save index of global variable in the ste link

    // Get the SteVar of this global decl and update it with the assembly index to use later
    STEVAR_ASSEMBLY_INDEX(GLOBDEF_SYMBOL_TABLE(node)) = globalVarDeclIndex;
    // Increment the global vars index for the next global vardecl
    globalVarDeclIndex++;

    // Traverse to the init Expr, probably nothing here because it is separated with RegularAssignments
    TRAVinit(node);

    // TODO: perform assembly generation when global is occurred
    // <type>loadg
    // loads a global variable
    // But look at the manual for all the instructions!
    
    return node;
}

/**
 * @fn ACGfundef
 */
node_st *ACGfundef(node_st *node)
{
    /*
        - When you get the funcall node of this fundef (can be found with the stefun link)
            get the index, check if STEFUN_ASSEMBLY_INDEX(FUNCALL)_STE_LINK(node)) != NULL, then:
            then you add the following assembly instruction:
            jsre <indexFromSteLink>
            This is: jump to external subroutine (which is the external function that is done for you already!)
            Or use the name for a not external function, no index necessary, use the label name!

    */

    // Very helpful slides in the last lecture: 70-72, 97-108
    // FunDef:
    // Create a label with the FunDef name from the SteFun link, this can then be used to jump
    // to the FunDef label with the SteFun link name to easily go there, so use fundef name!

    // label is een unieke naam die je in de assembly neerzet, gebruik het overal waar je moet jumpen
    // dit gebruik je eigenlijk als de offset, dat gebruik je in de 'jsr'
    // alle labels moeten uniek zijn, dat moet je bijhouden, bijv. met een counter voor labels, bijv 1_while

    // je kan ook jumpen naar een subroutine als iets true is, zoals met
    // branch_t O
    // Dit jumpt alleen als iets true is, met offset O
    // Maar bekijk de CiviC VM manual gewoon en lees alles dan zie je wat alles doet en hoe het werkt, etc!
    // werk weer in kleine stapjes!



    // TODO: every FunDef starts with an 'esr' instruction, which means enter subroutine!
    // esr L -> with L elements, thus reserving space for L local variables (can be calculated
    // by going through the chain of SteVars of this FunDef, this way you can easily count that number!)
    // TODO: is that the correct way to do it, ask a TA and test it!???


    // TODO: see the output of the reference compiler for how to do the functions, etc!
    //     ./civcc ../test/assemblyGenerationTests/operators/logical.cvc -o test
    // But keep in mind, it has a lot of optimizations, so the assembly of yours is different, but the 
    // output should be the same, and the function structure with labels and esr, etc is probably the same as well!

    // First check if the FunDef is a FunDec node (funbody is NULL and exported)
    // If it is, it needs to be imported
    if (FUNDEF_BODY(node) == NULL && FUNDEF_EXPORT(node)) {
        // Append the function import to the pseudo instructions string
        char *functionSignature = getFunctionSignatureFromSte(FUNDEF_SYMBOL_TABLE(node));
        pseudoInstructionsFuns = STRcat(
            STRcat(
                pseudoInstructionsFuns,
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
        // Append the function signature to the pseudo instructions string if it is exported
        // An exported function also ends with the function label name at the end with a space in front
        if (FUNDEF_EXPORT(node)) {
            char *functionSignature = getFunctionSignatureFromSte(FUNDEF_SYMBOL_TABLE(node));
            pseudoInstructionsFuns = STRcat(
                STRcat(
                    STRcat(pseudoInstructionsFuns, STRcat(".exportfun ", functionSignature)),
                    STRcat(" " ,FUNDEF_NAME(node))
                ), "\n"
            );
        }

        // Reset global counter for vardeclsIndex for every fundef (constantsIndex and others not necessary)
        vardeclsIndex = 0;

        // Set the current FunDef SteFun link to use for traversing the children of this fundef
        currentSteFunFunDef = FUNDEF_SYMBOL_TABLE(node); 

        // Start the FunDef node with its label (the name of the FunDef)
        struct data_acg *data = DATA_ACG_GET();
        fprintf(data->assembly_output_file, "%s:\n", FUNDEF_NAME(node));

        // Then create the 'esr' instruction with the number of local variables
        // Get the number of local variables to use in the 'esr' instruction
        int localVariablesCount = getLocalVariablesCount(FUNDEF_FIRST_STE_VARIABLES(node));
        fprintf(data->assembly_output_file, "esr %d\n", localVariablesCount);
        
        // Traverse the children
        TRAVbody(node);
        TRAVparams(node);
        // Check if the function is a void function, if so, add a 'return' instruction
        if (FUNDEF_TYPE(node) == CT_void) {
            fprintf(data->assembly_output_file, "return\n");
        }

        // Print a new line at the end of every FunDef
        fprintf(data->assembly_output_file, "\n");
    }

    // TODO: void function needs the instruction 'return' at the end, even if there is no return

    return node;
}
 // TODO: this gives an error but not used anyway, because you jump to a function in here with its name!!
    // So remove the below part and save it somewhere that you know it does not work, but not necessary because in
    // the FunCall you can jump to a function in the program with the name!

        // STEFUN_ASSEMBLY_INDEX(FUNDEF_SYMBOL_TABLE(node)) = globalFunsIndex;
        // printf("stefun assembly index is NULL not extern %d\n",STEFUN_ASSEMBLY_INDEX(FUNDEF_SYMBOL_TABLE(node)));
        // printf("stefun link is NULL not extern %s\n",FUNDEF_SYMBOL_TABLE(node) == NULL ? "true" : "false");
        // // Increment the globalFunsIndex for the next FunDef
        // globalFunsIndex++;

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
    STEVAR_ASSEMBLY_INDEX(VARDECL_SYMBOL_TABLE(node)) = vardeclsIndex;
    // Increment the vardecls index for the next VarDecl
    vardeclsIndex++;

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

        // TODO: remove after debugging
        printf("printed monop instruction: %s\n", monopInstructionSymbol);
    }

    return node;
}

/**
 * @fn ACGternaryop
 */
node_st *ACGternaryop(node_st *node)
{
    // TODO: found problem, it needs to be another binop with 5 > 0, not just the number!
    
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
            // Otherwise, it is a global variable, so so the assembly instruction for storing a global
            // in the global table by appending "g" at the end of the instruction
            assemblyTypeString = STRcat(assemblyTypeString, "g");
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
    // TODO: this needs to be done as well for the first assembly milestone

    // First traverse the expression
    TRAVexpr(node);

    // Then check what type it is and perform the cast instruction
    struct data_acg *data = DATA_ACG_GET();
    if (CAST_TYPE(node) == CT_int) {
        fprintf(data->assembly_output_file, "f2i\n");
    } else if (CAST_TYPE(node) == CT_int) {
        fprintf(data->assembly_output_file, "i2f\n");
    }

    return node;
}

/**
 * @fn ACGfuncall
 */
node_st *ACGfuncall(node_st *node)
{
    // TODO:
    // FunCall:
    // isr -> initiates a subroutine, probably 'isrg' to initiate a call to global (basic only one scope!)
    // <type>load -> then load all the variables needed for the parameters of the funcall (can also be an expression, see ass 6)
    // jsr A O -> jumps to subroutine with A number of arguments and O offset, O can also be a Label, that is easier, such as jsr 2 factorial
    // Of: jsre L -> this is for external functions. Index L can be picked from the SteFun link!
    // Than the function call assembly is finished. Or if you want to go to an external function (function with exported true as link)
    // (maybe that needs to be added to the SteFun as well???)
    // Then it is jsre I -> with I as the index in the import table (see index of the FunDef from the SteFun! You can then directly save if
    // it is exported as well in the FunDef traversal of this traversal!)

    // TODO: remove after testing, this was how the TA explained it:
    // FunCall:
    // isr 
    // start a new subroutine, eigenlijk wanneer je een functie called, voorbereiden op uitvoer functie
    // sub routine is eigenlijk een functie in assembly
    // isr and its scopes can probably be done easily with basic, just two scopes, global and in funbody
    // onder isr alle argumenten loaden met 'load'

    // TODO: check if extern from link, if it is extern, get the assembly index, otherwise use the label funName, no index necessary!
    // Get the index from the SteFun link (saved in FunDef earlier)
    //int funIndex = STEFUN_ASSEMBLY_INDEX(FUNCALL_STE_LINK(node));

    // Reset the number of arguments for every FunCall node
    tempFunCallArgsCount = 0;

    struct data_acg *data = DATA_ACG_GET();
    // Check if the function is external
    if (STEFUN_IS_EXTERNAL(FUNCALL_STE_LINK(node))) {
        // Initiate the global subroutine with the instruction 'isrg'
        fprintf(data->assembly_output_file, "isrg\n");
        // Then traverse the arguments
        if (FUNCALL_ARGS(node) != NULL) {
            TRAVargs(node);
        }
        // Then jump to the external subroutine with the index of the external function
        int externalFunIndexFunCall = STEFUN_ASSEMBLY_INDEX(FUNCALL_STE_LINK(node));
        fprintf(data->assembly_output_file, "jsre %d\n", externalFunIndexFunCall);
    } else {
        // TODO: change to isrg with comments

        // Initiate the subroutine with the instruction 'isr' if the function is not external
        fprintf(data->assembly_output_file, "isrg\n");
        // Then traverse the arguments if they are not NULL (checked to calculate the correct args count)
        if (FUNCALL_ARGS(node) != NULL) {
            TRAVargs(node);
        }
        // Then jump to the subroutine with the number of arguments and the name of the FunDef label
        fprintf(data->assembly_output_file, "jsr %d %s\n", tempFunCallArgsCount, STEFUN_NAME(FUNCALL_STE_LINK(node)));
    }

    return node;
}

/**
 * @fn ACGexprs
 */
node_st *ACGexprs(node_st *node)
{
    // TODO: later with funcalls, do this, probably fairly simple, just traverse expr and then after that next or the other way around
    // with doing some assembly instructions in between maybe!

    // Increment the arguments count for every argument in the FunCall node
    // If the args is NULL then it will not get here, so therefore this counter will be valid
    tempFunCallArgsCount++;

    // Then traverse the children
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
            // Otherwise, it is a global variable, so so the assembly instruction for loading a global
            // in the global table by appending "g" at the end of the instruction
            assemblyTypeString = STRcat(assemblyTypeString, "g");
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
        // TODO: check integer out of range

        // TODO: fix format a bit with the new lines, think of 

    struct data_acg *data = DATA_ACG_GET();

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
        //pseudoInstructionsConstants = STRcat(pseudoInstructionsConstants, ".const int %d\n", NUM_VAL(node));
        pseudoInstructionsConstants = STRcat(pseudoInstructionsConstants, "\n.const int ");
        // Then concatenate the int value to it
        pseudoInstructionsConstants = STRcat(pseudoInstructionsConstants, STRitoa(NUM_VAL(node)));

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
    // TODO: check float out of range


    struct data_acg *data = DATA_ACG_GET();

    if (FLOAT_VAL(node) == 0.0) {
        // Load a float constant 0.0, no need to update the 
        // constants index or a pseudo instruction now
        fprintf(data->assembly_output_file, "floadc_1\n");
    } else if (FLOAT_VAL(node) == 1.0) {
        // Loda the float constant value 1.0
        fprintf(data->assembly_output_file, "floadc_1\n");
    } else {
        // Otherwise create a pseudo instruction and update the constants index
        // Load the constant with the current constants index
        fprintf(data->assembly_output_file, "floadc %d\n", constantIndex);

        // Create the pseudo instruction for the constant and append it to already present instructions
        // Start the new instruction with a new line (avoids having a line between constants and funs pseudo ins)
        pseudoInstructionsConstants = STRcat(pseudoInstructionsConstants, "\n.const float ");
        // Then append the value to it. Allocate memory for a string of up to 99 characters.
        char *floatValString = MEMmalloc(100 * sizeof(char));
        // Initialize with empty string to avoid weird memory address value being used at the start
        strcpy(floatValString, ""); 
        sprintf(floatValString, "%f", FLOAT_VAL(node));
        // Append the float value string to the current pseudo instruction
        pseudoInstructionsConstants = STRcat(pseudoInstructionsConstants, floatValString);

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