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

// This helper VarDecl node is used for checking if a Var is the same as the declaration (then use global ste chain only)
node_st *currentVarDeclNode = NULL;

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
            // If a new chain needs to be created, then set the chain helper variables to NULL
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
            do {
                // Symbol already present, return not unique/false. Use string comparison 
                // to check for equality, 0 means equal. == only checks if memory references are equal
                if (strcmp(STEVAR_NAME(symtbolTableChain), name) == 0) {
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

        // Ste creation succeeded
        return true;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "multiple matching declarations/definitions found for the variable: %s", name);
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
    // Go to the traversal functions of the children
    TRAVchildren(node);

    // Update Ste first occurrence of a global symbolTableEntry to put into the Program node
    if (firstSymbolTableVar != NULL) {
        PROGRAM_FIRST_STE_VARIABLES(node) = firstSymbolTableVar;
    }
    // If the firstSymbolTableVar is NULL, then no global symbol tables are created, fundefs may have a SteVar

    return node;
}

/**
 * @fn CVSglobdecl
 */
node_st *CVSglobdecl(node_st *node)
{
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
    // Current scope is guarenteed to be global scope
    currentScopeVar = 0;

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(GLOBDEF_NAME(node), GLOBDEF_TYPE(node));

    // Traverse the init Expr to find potential links
    TRAVinit(node);

    return node;
}

/**
 * @fn CVSfundef
 */
node_st *CVSfundef(node_st *node)
{
    // No need to create a ste for the fundef here, that is done in the symbol tables for the functions
    // So, only create a pointer to the first SteVar in this functions scope

    // Open a new Ste chain 
    newSteVarChain = true;
    // Update the first and lastCurrent Ste global helper variables to open a new chain
    // This also avoids having a new fundef without Ste's linking to the previous SteVar chain
    firstSteVarCurrent = NULL;
    lastSteVarCurrent = NULL;

    // Save the oldScope
    int oldScope = currentScopeVar;
    // Increment the current scope inside a function body for every function body 
    // (basic has global, funbody and statements (if, while, etc) scope)
    currentScopeVar++;

    // First traverse the params, because they come first in the symbol tables implementation
    TRAVparams(node);
    // Then traverse the funbody
    TRAVbody(node);

    /*
    Create a pointer to the first steVar using the global temp symbol table variable
    Do this linking after the traversal functions of the params AND body because otherwise
    the SteVar chain can be empty still if there are no params!
    */ 
    if (firstSteVarCurrent != NULL) {
        // This SteVar should contain the first param of first vardecl if the params are empty
        FUNDEF_FIRST_STE_VARIABLES(node) = firstSteVarCurrent;
    }
    // If the firstSteVarCurrent is NULL, then no symbol tables are created, so nothing to update

    // Update the scope to the old scope after the statements when you get back to this fundef
    currentScopeVar = oldScope;

    // Also, update the newSteVarChain if no entry is created for this fundef (normally updated in createSymbol())
    newSteVarChain = false;

    return node;
}

/**
 * @fn CVSparam
 */
node_st *CVSparam(node_st *node)
{
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
    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(VARDECL_NAME(node), VARDECL_TYPE(node));

    // Update the current vardecl node before going to the init expression
    currentVarDeclNode = node;

    // Traverse the init Expr to find potential links
    TRAVinit(node);

    // To perfom the traversal functions of the children (next vardecls) use TRAVchildx(node)
    TRAVnext(node);

    // Reset the currentVarDeclNode to NULL at the end to not link it unnecessary later
    currentVarDeclNode = NULL;

    return node;
}

/*
***********************************************************************************************************************************************
                        This part is used to link the Var and/or VarLet nodes with their SteVar link 
*/

// Helper to avoid code duplication. Returns a found Ste node or NULL if no match is found
node_st *findSteVarNodeInSteChain(node_st *firstChainSte, char *name) {
    node_st *steIterator = firstChainSte;
    do {
        // Match found, return Ste node. Use string comparison 
        // to check for equality, 0 means equal. == only checks if memory references are equal
        char *tempSteName = STEVAR_NAME(steIterator);
        // Add NULL check to avoid Segmentation fault
        if (tempSteName != NULL && strcmp(tempSteName, name) == 0) {
            // Return Ste found, automatically stops the execution of this function with the return
            return steIterator;
        }

        // Update steIterator
        steIterator = STEVAR_NEXT(steIterator);
    } while (steIterator != NULL);

    // No link found
    return NULL;
}

// Find an Ste node that has the specified name
node_st *findSteVarLink(char *name) {
    /*
    If the current VarDecl is not equal to NULL and the name of the VarDecl is equal
    equal to 0 (means the name of the ste link and the VarDecl name are equal), 
    then skip the current fundef chain and search in the global chain only!
    If not:
    First search in the fundef chain because you want the closest Ste to be linked.
    If it is not in the current fundef chain, then search in the global chain.
    If it is not in the global chain then give an error that there is no link found!
    */
    if (currentVarDeclNode != NULL && strcmp(VARDECL_NAME(currentVarDeclNode), name) == 0) {
        printf("VarDecl, only global scope!************************\n");
        // Search in the global chain only, skip searching in the current fundef chain
        if (firstSymbolTableVar != NULL) {
            node_st *foundSteNodeInChain = findSteVarNodeInSteChain(firstSymbolTableVar, name);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }
    } else {
        printf("NULL VarDecl, fundef and global scope!************************\n");

        // First search in the current FunDef chain
        if (firstSteVarCurrent != NULL) {
            node_st *foundSteNodeInChain = findSteVarNodeInSteChain(firstSteVarCurrent, name);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }

        // Search in the global chain if fundef chain is NULL or symbol not found there
        // If the return statement of the previous search is not called it will get to this part
        if (firstSymbolTableVar != NULL) {
            node_st *foundSteNodeInChain = findSteVarNodeInSteChain(firstSymbolTableVar, name);
            if (foundSteNodeInChain != NULL) {
                // Return Ste found, automatically stops the execution of this function with the return
                return foundSteNodeInChain;
            }
        }
    }
    

    // No existing symbol found, return NULL
    return NULL;
}

/**
 * @fn CVSvar
 */
node_st *CVSvar(node_st *node)
{
    // TODO

    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteVarLink(VAR_NAME(node));
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VAR_STE_LINK(node) = steNode;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "no matching declaration/definition for var: %s", VAR_NAME(node));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }

    return node;
}

/**
 * @fn CVSvarlet
 */
node_st *CVSvarlet(node_st *node)
{
    // TODO
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteVarLink(VARLET_NAME(node));
    
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VARLET_STE_LINK(node) = steNode;
    } else {
        // Prints the error when it occurs, so in this line
        CTI(CTI_ERROR, true, "no matching declaration/definition for varlet: %s", VARLET_NAME(node));
        // Create error action, will stop the current compilation at the end of this Phase (contextanalysis phase)
        CCNerrorPhase();
    }
    
    return node;
}