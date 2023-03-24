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
int constandIndex = 0;
// Save the index of the VarDecls in a global variable to use for creation assembly
int vardeclsIndex = 0;
// Save the index of the global VarDecls in a global variable to use for creation assembly
int globalVarDeclIndex = 0;
// Global helper variable to save the label index of the current label (starts at 1)
int labelIndex = 1;

// Save the current fundef first SteVar to use for return instruction
node_st *currentSteFunFunDef = NULL;

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

/*
TODO: this is how you generate a file:
./civicc ../test/basic/functional/for_to_while.cvc -o <fileName>
The file will be made in the current directory, so you run this in the build-debug,
so the file can then be found in that directory!

You can run this command in the build-debug to see more information about civicc
./civicc

This is how you can then perform the output for a file using civas and civvm
(You need to have the civas and civvm in your bin folder for this to work):
    1. First go to the build-debug directory, then do:
    2. ./civicc ../test/<testFilePath> -o <fileName>
        This creates the assembly instructions for the test file provided
    3. ../bin/civas <fileName> -o <fileName2>.as
        This creates the output file with the CiviC assembler
    4. ../bin/civvm <fileName2>.as
*/

// Helper function to get the string type of the enum Type
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

/**
 * @fn ACGprogram
 */
node_st *ACGprogram(node_st *node)
{
    // Traverse to the children
    TRAVdecls(node);

    // TODO: at the end of the program, print the functionSignatures pseudo instructions??? (See CiviC_VM last pages!)

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
    TODO: this is how you handle external functions that are build in:
        - check if the fundef is exported and if the funbody is NULL, then it is a FunDec
        - No need to check for a name of the built in functions, extern functions are always this way, so just follow this:
        - Then create the assembly instruction for the external built in function. This needs to be printed 
        only when you get to the end of the program, maybe save it in a char * with function signatures?? (See Civic VM last pages!):
            .importfun "funName" <retType> <args>
        - Then update this fundef ste link node with its index in the assembly instructions (global variable)
            STEFUN_ASSEMBLY_INDEX(FUNDEF_SYMBOL_TABLE(node));
            = globalVariable
        - Then when you get the funcall node of this fundef (can be found with the stefun link)
            get the index, check if STEFUN_ASSEMBLY_INDEX(FUNCALL)_STE_LINK(node)) != NULL, then:
            then you add the following assembly instruction:
            jsre <indexFromSteLink>
            This is: jump to external subroutine (which is the external function that is done for you already!)

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


    // Reset global counter for vardeclsIndex for every fundef (constantsIndex and others not necessary)
    // TODO: is it correct that only the vardeclsIndex needs to be reset
    vardeclsIndex = 0;

    // Set the current FunDef SteFun link
    currentSteFunFunDef = FUNDEF_SYMBOL_TABLE(node);
    
    // Traverse the children
    TRAVbody(node);
    TRAVparams(node);

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
    // TODO

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

    // TODO:

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
    // TODO, makkelijkst om eerst de conditie te doen, dan 
    // branch_f 1_else
    // dit gaat naar else als de conditie false is en dan hieronder de if code en daaronder de else code
    // TODO: maar voer een file uit in de reference compiler en zie hoe die structuur is (optimized, dus expressies hoeven niet hetzelfde!)

    // Traverse the condition Expr
    TRAVcond(node);

    // Traverse the then Stmts
    TRAVthen(node);

    // TODO: if the condition is true, what to do with the else block???

    // Traverse the else_block
    TRAVelse_block(node);
    return node;
}

/**
 * @fn ACGwhile
 */
node_st *ACGwhile(node_st *node)
{
        // TODO
        // see VM manual example for how to do it!

    // Traverse the condition Expr
    TRAVcond(node);

    // Traverse the block Stmts
    TRAVblock(node);

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
    fprintf(data->assembly_output_file, "%d_doWhile\n", currentLabelIndex);
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
    // Get the return type of the current fundef
    char *assemblyTypeString = getOperandTypeAssembly(STEFUN_TYPE(currentSteFunFunDef));
    // Append the type infront of the return instruction (void type will automatically become 'return')
    fprintf(data->assembly_output_file, STRcat(assemblyTypeString, "return"));

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

    // Then create a label for the else expression (labelformat: "token :"")
    fprintf(data->assembly_output_file, "%d_elseExpr:\n", currentLabelIndex);
    // Then traverse the else_expr
    TRAVelse_expr(node);

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

    return node;
}

/**
 * @fn ACGexprs
 */
node_st *ACGexprs(node_st *node)
{
    // TODO: later with funcalls, do this, probably fairly simple, just traverse expr and then after that next or the other way around
    // with doing some assembly instructions in between maybe!

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
    // Load the constant with the current constants index
    struct data_acg *data = DATA_ACG_GET();
    fprintf(data->assembly_output_file, "iloadc %d\n", constandIndex);

    // Increment the constantsIndex for the next constant
    constandIndex++;

    return node;
}

/**
 * @fn ACGfloat
 *
 * Constant: push 'loadc' instruction with index from constant table
 */
node_st *ACGfloat(node_st *node)
{
    // Load the constant with the current constants index
    struct data_acg *data = DATA_ACG_GET();
    fprintf(data->assembly_output_file, "floadc %d\n", constandIndex);

    // Increment the constantsIndex for the next constant
    constandIndex++;

    return node;
}

/**
 * @fn ACGbool
 *
 * Constant: push 'loadc' instruction with index from constant table
 */
node_st *ACGbool(node_st *node)
{
    // Load the constant with the current constants index
    struct data_acg *data = DATA_ACG_GET();
    fprintf(data->assembly_output_file, "bloadc %d\n", constandIndex);

    // Increment the constantsIndex for the next constant
    constandIndex++;

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