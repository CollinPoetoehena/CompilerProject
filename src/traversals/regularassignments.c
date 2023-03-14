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
// Palm library for easily using memory in C
#include "palm/memory.h"

// node_st * global variables are used for building and updating the new nodes
node_st *firstGlobdefStmts = NULL;
node_st *currentGlobdefStmts = NULL;

// This variable is used to determine the last Decls node with a GlobDef node to append the __init function to
node_st *tempDeclsNode = NULL;
node_st *lastGlobDefDeclsNode = NULL;

// node_st * global variables are used for building and updating the new nodes
node_st *firstVardeclStmts = NULL;
node_st *currentVardeclStmts = NULL;

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

// Helper function to update the global vardecl Stmts nodes helper variables
void updateVarDeclStmts(node_st *newStmts) {
    if (newStmts != NULL) {
        if (firstVardeclStmts != NULL) {
            // Save the next and update current globdef stmts
            STMTS_NEXT(currentVardeclStmts) = newStmts;
            currentVardeclStmts = newStmts;
        } else {
            // Save it as the first Stmts
            firstVardeclStmts = newStmts;
            currentVardeclStmts = newStmts;
        }
    }
}

/**
 * @fn RAprogram
 */
node_st *RAprogram(node_st *node)
{
    // First traverse the GlobDefs to convert the initializations
    TRAVdecls(node);

    /*
    Update the Stmts of the funbody.
    If lastGlobDefDeclsNode is NULL, then there were no GlobDef occurrences. And if firstGlobdefStmts 
    or currentGlobdefStmts is NULL, that means that there were no GlobDef initializations, so no
    need to create the __init function then.
    Otherwise, create the __init function and append it to the last globdef node in the program.
    */ 
    if (lastGlobDefDeclsNode != NULL && firstGlobdefStmts != NULL && currentGlobdefStmts != NULL) {
        // Init function will be put after the last GlobDef node 
        // (not the GlobDecls because GlobDecls) do not have an initialization
        printf("DECLS next before new assign is at address: %p\n", (void*)&DECLS_NEXT(lastGlobDefDeclsNode));

        // Allocate new memory to add the new FunDef node
        //node_st *newDeclsNode = MEMmalloc(1000);
        node_st *newDeclsNode = ASTdecls(ASTfundef(ASTfunbody(NULL, firstGlobdefStmts), 
            NULL, CT_void, "__init", false), DECLS_NEXT(lastGlobDefDeclsNode));
        DECLS_NEXT(lastGlobDefDeclsNode) = newDeclsNode;
        
        printf("newDeclsNode is at address: %p\n", (void*)&newDeclsNode);
        printf("DECLS next after new assign is at address: %p\n", (void*)&DECLS_NEXT(lastGlobDefDeclsNode));
        // TODO: why does this return an invalid pointer??? or a Segmentation fault??**************************************************************
    }

    return node;
}

/**
 * @fn RAdecls
 */
node_st *RAdecls(node_st *node)
{
    char *bool_str = NODE_TYPE(DECLS_DECL(node)) == NT_GLOBDEF ? "true" : "false";
    printf("%s\n", bool_str);
    // Check if the type is NT_GLOBDEF
    if (NODE_TYPE(DECLS_DECL(node)) == NT_GLOBDEF) {
        // Update last globdef node, this node will be used to append the __init FunDef to
        lastGlobDefDeclsNode = node;
    }

    // Go to the traversal function of the decl
    TRAVdecl(node);

    // Go to the next Decls
    TRAVnext(node);

    return node;
}

/**
 * @fn RAglobdef
 */
node_st *RAglobdef(node_st *node)
{
    // If the globdef has an initialization, convert it
    if (GLOBDEF_INIT(node) != NULL) {
        // Create copies to avoid pointing to the same reference twice
        char *copiedGlobDefName = STRcpy(GLOBDEF_NAME(node));

        // Create new VarLet, Assign and Stmts node, use the current INIT Expr node
        // TODO: is this correct, no copies required or????
        // TODO: what to do with the Link attribute, probably this traversal should be before the CA right?!
        node_st *newStmtsNodeGlobDef = ASTstmts(ASTassign(ASTvarlet(copiedGlobDefName), GLOBDEF_INIT(node)), NULL);

        // Add the new AssignNode to the global Stmts helper variable
        updateGlobDefStmts(newStmtsNodeGlobDef);

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

    // Update the Stmts of the funbody
    if (firstVardeclStmts != NULL && currentVardeclStmts != NULL) {
        // First update the last Stmts node of the VarDecls initializations with the current stmts
        STMTS_NEXT(currentVardeclStmts) = FUNBODY_STMTS(node);
        // Then update the funbody's stmts with the new first Stmts (which also contains the old stmts chain)
        FUNBODY_STMTS(node) = firstVardeclStmts;
    }

    // Then traverse the Stmts and prepend the new Stmts nodes collected from the VarDecls
    TRAVstmts(node);

    // Reset the temp helper variables after every funbody traversal
    firstVardeclStmts = NULL;
    currentVardeclStmts = NULL;

    return node;
}

/**
 * @fn RAvardecl
 */
node_st *RAvardecl(node_st *node)
{
    // If the vardecl has an initialization, convert it
    if (VARDECL_INIT(node) != NULL) {        
        // Create copies to avoid pointing to the same reference twice
        char *copiedVarDeclName = STRcpy(VARDECL_NAME(node));

        // Create new VarLet, Assign and Stmts node, use the current INIT Expr node
        // TODO: is this correct, no copies required or????
        // TODO: what to do with the Link attribute, probably this traversal should be before the CA right?!
        node_st *newStmtsNodeVarDecl = ASTstmts(ASTassign(ASTvarlet(copiedVarDeclName), VARDECL_INIT(node)), NULL);

        // Add the new AssignNode to the global Stmts helper variables
        updateVarDeclStmts(newStmtsNodeVarDecl);

        // Then update this VarDecl node by setting the initialization to NULL
        VARDECL_INIT(node) = NULL;
    }

    // Go to the next VarDecls to traverse that ndoe
    TRAVnext(node);
    
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

