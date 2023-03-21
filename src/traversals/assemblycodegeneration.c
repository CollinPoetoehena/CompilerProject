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

// Get the output file in the init fuction
void ACGinit() {
    // Initialize file pointer, ensures there is a file.
    // Use the global.output_file from globals in CoCoNut to write the assembly to
    FILE *file = fopen(global.output_file, "w");

    if (file != NULL) {
        // Get the file pointer from the travdata of the ACG traversal and update it
        struct data_acg *data = DATA_ACG_GET();
        data->assembly_output_file = file;

        // Write to a file with 'fprintf'.
        fprintf(data->assembly_output_file, "Hello World\n");
    } else {
        // File is NULL, so failed
        // TODO: produce something from an error here or something???
    }
    
    return;
}

void ACGfini() {
    // TODO: close the file here

    // Get the file pointer from the travdata of the ACG traversal and update it
    struct data_acg *data = DATA_ACG_GET();

    // Close the file at the end of the traversal
    fclose(data->assembly_output_file);

    return;
}

/*
TODO: this is how you generate a file:
./civicc ../test/basic/functional/for_to_while.cvc -o <fileName>
The file will be made in the current directory, so you run this in the build-debug,
so the file can then be found in that directory!

You can run this command in the build-debug to see more information about civicc
./civicc
*/

/**
 * @fn ACGprogram
 */
node_st *ACGprogram(node_st *node)
{
    return node;
}

/**
 * @fn ACGdecls
 */
node_st *ACGdecls(node_st *node)
{
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
    return node;
}

/**
 * @fn ACGglobdef
 */
node_st *ACGglobdef(node_st *node)
{
    return node;
}

/**
 * @fn ACGfundef
 */
node_st *ACGfundef(node_st *node)
{
    return node;
}

/*
***********************************************************************************************************************************************
These nodes are children of the FunDef node
*/

/**
 * @fn ACGparam
 */
node_st *ACGparam(node_st *node)
{
    return node;
}

/**
 * @fn ACGfunbody
 */
node_st *ACGfunbody(node_st *node)
{
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
    return node;
}

/**
 * @fn ACGstmts
 */
node_st *ACGstmts(node_st *node)
{
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
    return node;
}

/**
 * @fn ACGexprstmt
 */
node_st *ACGexprstmt(node_st *node)
{
    return node;
}

/**
 * @fn ACGifelse
 */
node_st *ACGifelse(node_st *node)
{
    return node;
}

/**
 * @fn ACGwhile
 */
node_st *ACGwhile(node_st *node)
{
    return node;
}

/**
 * @fn ACGdowhile
 */
node_st *ACGdowhile(node_st *node)
{
    return node;
}

/**
 * @fn ACGfor
 */
node_st *ACGfor(node_st *node)
{
    return node;
}

/**
 * @fn ACGreturn
 */
node_st *ACGreturn(node_st *node)
{
    return node;
}

/*
***********************************************************************************************************************************************
These are the operator nodes (also part of Expr, Operations)
*/

/**
 * @fn ACGbinop
 */
node_st *ACGbinop(node_st *node)
{
    return node;
}

/**
 * @fn ACGmonop
 */
node_st *ACGmonop(node_st *node)
{
    return node;
}

/**
 * @fn ACGternaryop
 */
node_st *ACGternaryop(node_st *node)
{
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
    return node;
}

/**
 * @fn ACGcast
 */
node_st *ACGcast(node_st *node)
{
    return node;
}

/**
 * @fn ACGfuncall
 */
node_st *ACGfuncall(node_st *node)
{
    return node;
}

/**
 * @fn ACGexprs
 */
node_st *ACGexprs(node_st *node)
{
    return node;
}

/**
 * @fn ACGvar
 */
node_st *ACGvar(node_st *node)
{
    return node;
}

/*
***********************************************************************************************************************************************
These are the constant nodes: Num, Float, Bool (also part of Expr, Constants)
*/

/**
 * @fn ACGnum
 */
node_st *ACGnum(node_st *node)
{
    return node;
}

/**
 * @fn ACGfloat
 */
node_st *ACGfloat(node_st *node)
{
    return node;
}

/**
 * @fn ACGbool
 */
node_st *ACGbool(node_st *node)
{
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