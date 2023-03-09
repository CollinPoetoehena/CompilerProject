/**
 * @file
 *
 * Traversal: CreateVariableSymbolTableEntries
 * UID      : CVS
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums and types, for the Type
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

// Two scopes for basic: Program and FunBody
int currentScopeVar = 0; // Start at global scope

// firstSymbolTableVar is used to fill the Program symbol table for Variables
node_st *firstSymbolTableVar = NULL;
// lastSteVarGlobal is used to keep track of the last global Ste to use for appending to the LinkedList
node_st *lastSteVarGlobal = NULL;

// firstSteVarCurrent is used to keep track of the first current Ste that is not in the globalscope
node_st *firstSteVarCurrent = NULL;
// lastSteVarCurrent is used to keep track of the last current Ste that is not in the globalscope
node_st *lastSteVarCurrent = NULL;

// Helper variable to keep track of when to open a new chain
bool newSteVarChain = false;


// Update the global symbol tables used for iterating over the Ste's
void updateGlobSymbolTables(node_st *newSte) {
    if (newSte != NULL) {
        if (currentScopeVar == 0) {
            // Use global SteVar's helper variables memory addresses
            if (firstSymbolTableVar == NULL) {
                firstSymbolTableVar = newSte;
                lastSteVarGlobal = newSte;
            } else {
                // Update next of previous symbol table
                STEVAR_NEXT(lastSteVarGlobal) = newSte;
                lastSteVarGlobal = newSte;
            }
        } else {
            // // If a new chain needs to be created, then set the chain helper variables to NULL
            if (newSteVarChain) {
                // These pointers point to the helper variables for the correct chain now and will update them
                firstSteVarCurrent = newSte;
                lastSteVarCurrent = newSte;
                // Then close the chain to use this chain from now on, until updated
                newSteVarChain = false;
            } else {
                // Use non global SteVar's helper variables memory addresses
                if (firstSteVarCurrent == NULL) {
                    firstSteVarCurrent = newSte;
                    lastSteVarCurrent = newSte;
                } else {
                    // Update next of previous symbol table
                    STEVAR_NEXT(lastSteVarCurrent) = newSte;
                    lastSteVarCurrent = newSte;
                }
            }
        }
    }
}

// Check if a symbol is unique
bool isSymbolUnique(char *name) {
    // If a new chain needs to be opened, then it is guarenteed to be a unique symbol in that scope
    if (newSteVarChain) {
        // If this code is not here, it will search in the previous chain and that can create bugs!
        return true;
    } else {
        // Check if the name is not already present in the symbol table entries (use linear search)
        node_st *symtbolTableChain = NULL;
        if (currentScopeVar == 0) {
            // Avoid segmentation fault
            if (firstSymbolTableVar != NULL) {
                // Go through the global chain
                symtbolTableChain = firstSymbolTableVar;
            }
        } else {
            if (firstSteVarCurrent != NULL) {
                // Go through the current (non global) chain
                symtbolTableChain = firstSteVarCurrent;
            }
        }

        // Go through the current chain to check if it contains the symbol already
        if (symtbolTableChain != NULL) {
            // TODO: remove after debugging
            // printf("\n\n\n\n\n\n\nPRINTING STE CHAIN IT IS SERACHING IN********************\n");
            // printSteVarChain(symtbolTableChain);
            do {
                // Symbol already present, return not unique/false. Use string comparison 
                // to check for equality, 0 means equal. == only checks if memory references are equal
                if (strcmp(STEVAR_NAME(symtbolTableChain), name) == 0) {
                    printf("**********************Link found for %s\n", name);
                    printf("First stevar that occured is: %s\n", STEVAR_NAME(symtbolTableChain));
                    return false;
                }

                // Update symbolTable
                symtbolTableChain = STEVAR_NEXT(symtbolTableChain);
            } while (symtbolTableChain != NULL);
        }
    }
    
    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

// Create a symbol table entry node, declared after helper functions, because otherwise it gives an error!
bool createSymbolTableEntry(char *name, enum Type type) {
    // First check if the name is already present, if so, save it in errors
    if (isSymbolUnique(name)) {
        node_st *newSte = NULL;
        // NULL check for firstSymbolTableVar in the condition avoid Segmentation fault
        if (firstSymbolTableVar != NULL &&
            currentScopeVar == 1 && STEVAR_NESTING_LEVEL(firstSymbolTableVar) == 0) {
            // Global Ste is the parent if the firstSymbolTableVar is at nesting_level 0 (global), otherwise NULL
            newSte = ASTstevar(firstSymbolTableVar, NULL, name, type, currentScopeVar);
        } else {
            newSte = ASTstevar(NULL, NULL, name, type, currentScopeVar);
        }

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        // TODO: binops and bool_op from basic check_success do not work!
        // Creation of the Ste's is correctly done, but the chains are not linked well
        // they are all separate entries and not linked
        // New var chain is also working, the problem is with the params. If there are no params, then 
        // it does not work, if there are params, it does work, so the problem is with the params that it links something

        // TODO: remove after debugging
        //printSteVar(newSte);

        // Ste creation succeeded
        return true;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "multiple matching declarations/definitions found for %s", name);
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    // Creation failed
    return false;
}

/**
 * @fn CVSprogram
 */
node_st *CVSprogram(node_st *node)
{
    // printf("program\n");

    // Print the start of the context analysis variables
    printf("\n\n\n****************************************************************************************************************************************************************************** \
    \t\tStart of context analysis variables\n");

    // Go to the traversal functions of the children
    TRAVchildren(node);

    // Update Ste first occurrence to put into the Program node
    if (firstSymbolTableVar != NULL) {
        PROGRAM_FIRST_STE_VARIABLES(node) = firstSymbolTableVar;
    } else {
        printf("NO STES CREATED IN TRAVERSAL!!\n");
    }
    // If the firstSymbolTableVar is NULL, then no symbol tables are created, so nothing to update

    printf("\n\n\n\t\tEnd of context analysis variables\n****************************************************************************************************************************************************************************** \
    \n");

    return node;
}

/**
 * @fn CVSglobdecl
 */
node_st *CVSglobdecl(node_st *node)
{
    // printf("globdecl\n");

    // Current scope is guarenteed to be global scope
    currentScopeVar = 0;

    // Create a symbol table entry
    createSymbolTableEntry(GLOBDECL_NAME(node), GLOBDECL_TYPE(node));

    return node;
}

/**
 * @fn CVSglobdef
 */
node_st *CVSglobdef(node_st *node)
{
    // printf("globdef\n");

    // Current scope is guarenteed to be global scope
    currentScopeVar = 0;

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(GLOBDEF_NAME(node), GLOBDEF_TYPE(node));

    return node;
}

/**
 * @fn CVSfundef
 */
node_st *CVSfundef(node_st *node)
{
    printf("fundef\n");

    // Open a new Ste chain 
    newSteVarChain = true;

    // No need to create a ste for the fundef here, that is done in the symbol tables for the functions
    // So, only create a pointer to the first SteVar in this functions scope

    // Save the oldScope
    int oldScope = currentScopeVar;
    // Increment the current scope inside a function body for every function body 
    // (basic has global, funbody and statements (if, while, etc) scope)
    currentScopeVar++;

    // First traverse the params, because they come first in the symbol tables implementation
    TRAVparams(node);
    // Then traverse the funbody
    TRAVbody(node);

    // Create a pointer to the first steVar using the global temp symbol table variable
    // Do this linking after the traversal functions of the params AND body because otherwise
    // the SteVar chain can be empty still if there are no params!
    if (firstSteVarCurrent != NULL) {
        // This SteVar should contain the first param of first vardecl if the params are empty
        FUNDEF_FIRST_STE_VARIABLES(node) = firstSteVarCurrent;
    }
    // If the firstSteVarCurrent is NULL, then no symbol tables are created, so nothing to update

    // Update the scope to the old scope after the statements when you get back to this fundef
    currentScopeVar = oldScope;

    return node;
}

/**
 * @fn CVSparam
 */
node_st *CVSparam(node_st *node)
{
    // Create ste for the param
    // printf("param\n");

    // Create a SteVar for the param
    createSymbolTableEntry(PARAM_NAME(node), PARAM_TYPE(node));

    // If this param has a next, do the same for the next param in the function definition
    TRAVnext(node);

    return node;
}

/**
 * @fn CVSfunbody
 */
node_st *CVSfunbody(node_st *node)
{
    // First traverse the VarDecls
    TRAVdecls(node);

    // Then traverse the Stmts
    // Updating scope for Stmts not necessary because there are no VarDecls or FunDefs in Stmts (see language)!
    TRAVstmts(node);

    return node;
}

/**
 * @fn CVSvardecl
 */
node_st *CVSvardecl(node_st *node)
{
    printf("vardecls\n");
    //TODO: all files from basic check_success do not get a Ste, why???

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(VARDECL_NAME(node), VARDECL_TYPE(node));

    // TODO: this is probably not necessary anymore to travinit?? Test this thourougly!
    // Go to the traversal function of the expr to go to the Vars
    // TRAVinit(node);

    // To perfom the traversal functions of the children (next vardecls) use TRAVchildx(node)
    TRAVnext(node);

    return node;
}

/**
 * @fn CVSfor
 */
node_st *CVSfor(node_st *node)
{
    // Updating scope not necessary, no VarDecls or FunDefs in Stmts (see language)!
    // Renaming of for loop identifiers has been done in a separate traversal
    
    // remove the declaration part from for-loop induction variables and create corresponding 
    // local variable declarations on the level of the (innermost) function definition
    // For var declaration always has type int and name is saved in For node
    createSymbolTableEntry(FOR_VAR(node), CT_int);
    printf("For Var node: %s", FOR_VAR(node));

    // Go to stmts traversal functions
    TRAVblock(node);

    // TODO: while, ifelse, etc not necessary??? Test by creating a var, varlet and funcall and see if they get linked in the body!

    return node;
}

// Prints a chain of SteVar's using the LinkedList structure
// TODO: remove at the end of the compiler project, this is handy to print a chain of Ste's for debugging!
void printSteVar(node_st *steParentNode) {
  if (steParentNode != NULL) {
    // Open the new SteVar chain
    printf("\n**************************\n\tNew SteVar chain:\n");

    // Get the first param from the Ste
    node_st *steIterator = steParentNode;
    do {
        // Get the type
        char *type = NULL;

        switch (STEVAR_TYPE(steParentNode)) {
          case CT_int:
          type = "int";
          break;
          case CT_float:
          type = "float";
          break;
          case CT_bool:
          type = "bool";
          break;
          case CT_void:
          type = "void";
          break;
          case CT_NULL:
          DBUG_ASSERT(false, "unknown type detected!");
        }

        // Print var Ste: "name, type"
        printf("SteVar:\n %s : %s\nnesting level: %d\n", 
            STEVAR_NAME(steIterator), type, STEVAR_NESTING_LEVEL(steIterator));

        // Update iterator
        steIterator = STEVAR_NEXT(steIterator);
    } while (steIterator != NULL);

    // End the current SteVar chain
    printf("\n\tEnd of SteVar chain\n**************************\n\n");
  }
}

// Helper function to return the appropriate current Ste
// TODO: if it is not used it can be removed, but maybe this can be a helpful function (not yet tested, so needs to be tested and changed!)!
// node_st *getCurrentSteVar(bool firstSte) {
//     // TODO: convert to use scopes
//     if (currentScopeVar == 0) {
//         // Return an Ste from the global chain of Ste's
//         if (firstSte) {
//             // If the first Ste of the current scope is requested return first
//             return firstSymbolTableVar;
//         }

//         // Otherwise return the last Ste of the current scope is requested return the last 
//         return lastSteVarGlobal;
//     } else {
//         // Return an Ste from a non global chain of Ste's
//         if (firstSte) {
//             // If the first Ste of the current scope is requested return first
//             return firstSteVarCurrent;
//         }

//         // Otherwise return the last Ste of the current scope is requested return the last 
//         return lastSteVarCurrent;
//     }

//     return NULL;
// }