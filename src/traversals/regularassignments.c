/**
 * @file
 *
 * Traversal: RegularAssignments
 * UID      : RA
 * 
 * This traversal should separate the declaration from the initilizations.
 * This will be handy with code generation.
 *
 * Example:
 * int a = 5 * 6;
 * int b = 3;
 * a = 6;
 * Should become (still with the equivalent code):
 * int a; int b; a = 5 * 6; b = 3; a = 6;
 * 
 * So, you should first only have declarations and then the statements.
 *
 * For local variable declarations the new assignment statements can simply prefix
 * the original sequence of statements. But for global variables it is a-priori unclear where such 
 * initialisation assignments could be stored. Therefore, the compiler shall create one top-level function 
 * named __init in every compilation unit. In this function the compiler collects all initialisation assignments 
 * for global variables in the order of their syntactic appearance in the original code. This __init
 * function will later also be used by the CiviC-VM.
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
// Palm library for easy working with strings
#include "palm/str.h"

// This global variable for Decls is used to put the __init function at the top
bool firstDeclsNode = true;
node_st *initFunDefNode = NULL;

// node_st * global variables are used for building and updating the new nodes
node_st *firstGlobdefStmts = NULL;
node_st *currentGlobdefStmts = NULL;

// vardecls in een lijst
// __init maak je aan met ASTfundef, alle initializaties, worden stmts, alleen voor globdef hoeft dit
// export int a = 3; 
// init func heeft dan a = 3;

// funbody travdecls
// daarna travstmts initalizaties normale stmts maken en prependen aan de bestaande stmts

// Helper function to update the global globdef Stmts nodes helper variables
void updateGlobDefStmts(node_st *newStmts) {
    if (newStmts != NULL) {
        if (firstGlobdefStmts != NULL) {
            // Save the next and update current globdef stmts
            STMTS_NEXT(currentGlobdefStmts) = newStmts;
            currentGlobdefStmts = newStmts;
        } else {
            // Save it as the first Stmts
            firstGlobdefStmts = newStmts;
            currentGlobdefStmts = newStmts;
        }
    }
}

// TODO: convert. Aparently you cannot create a Decl as a FunDef and save it in a Decls node as Decl
// node_st *createInitFunDefWithStmts(node_st *stmtsNode) {
//     return ASTfundef(NULL, NULL, CT_void, "__init", false);
// }


/**
 * @fn RAprogram
 */
node_st *RAprogram(node_st *node)
{
    TRAVdecls(node);

    return node;
}

/**
 * @fn RAdecls
 */
node_st *RAdecls(node_st *node)
{
    // TODO: make sure that the __init function is the top-level function, use boolean global value

    // Go to the traversal function of the decl
    TRAVdecl(node);

    // If there are no next decls anymore, create the FunDef __init at the top
    // Last Decls node, so create and print the __init function
    // TODO: save it at the top, how to do that????? First focus on the creation and make that work, etc, later link it to the top!
    if (DECLS_NEXT(node) == NULL) {

    } else {
        // Go to the next decls
        TRAVnext(node);
    }

    return node;
}

/**
 * @fn RAglobdef
 */
node_st *RAglobdef(node_st *node)
{
    printf("getting to globdef in RA*************\n");
    // If the globdef has an initialization, convert it
    if (GLOBDEF_INIT(node) != NULL) {
        // First convert it to a Varlet node and an Assign node
        //TODO: what to do with the Link attribute, probably this traversal should be before the CA right?!
        // Create copies to avoid pointing to the same reference twice
        char *copiedGlobDefName = STRcpy(GLOBDEF_NAME(node));
        node_st *newVarletNode = ASTvarlet(copiedGlobDefName);
        node_st *copiedGlobDefExpr = CCNcopy(GLOBDEF_INIT(node));
        node_st *newAssignNode = ASTassign(newVarletNode, copiedGlobDefExpr);

        // Add the new AssignNode to the global Stmts helper variable
        updateGlobDefStmts(newAssignNode);

        // Then update this GlobDef node by setting the initialization to NULL
        GLOBDEF_INIT(node) = NULL;
    }

    return node;
}

/**
 * @fn RAfunbody
 */
node_st *RAfunbody(node_st *node)
{
    // First traverse the VarDecls to convert the initializations
    TRAVdecls(node);

    // Then traverse the Stmts and prepend the new Stmts nodes collected from the VarDecls
    TRAVstmts(node);

    return node;
}

/**
 * @fn RAvardecl
 */
node_st *RAvardecl(node_st *node)
{
    // if init then it has an initialization: "= Expr"
    // if (VARDECL_INIT(node) != NULL) {
    //   //TODO: HOW TO CREATE THE __init function for the compiler
      
    //   // Create a copy of the nodes and then free this node to create separate nodes
    //   //TODO: is this correct????
    //   // Important: only use Copy when you want to have it at two different locations
    //   // No need to Copy here because it is re-used here because it is set to NULL afterwards
    //   node_st *init = VARDECL_INIT(node);
    //   // Set init to NULL, to only keep declaration (such as int a;)
    //   VARDECL_INIT(node) = NULL;
    // }
    
    return node;
}

/**
 * @fn RAstmts
 */
node_st *RAstmts(node_st *node)
{
    // Update statements by prepending new Stmts node to the first one occurring

    // Reset first Stmts boolean to only prepend to the first one

    return node;
}

/**
 * @fn RAfor
 */
node_st *RAfor(node_st *node)
{
    // TODO: milestone 6, what to do with for, if anything, no need to do anything right???
    return node;
}

