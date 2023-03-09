/**
 * @file
 *
 * Traversal: ContextAnalysis
 * UID      : CA
 *
 * TODO: this is an old file, can be removed if it has no use for copying code anymore!
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
// Include enums, for the Type and SymbolTableType
#include "ccngen/enum.h"
#include "ccn/ccn_types.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Include error functionality
#include "palm/ctinfo.h"

// Global variable for the first symbol table
// Used to loop through from start to end via next
node_st *firstSymbolTable = NULL;
node_st *previousSymbolTable = NULL;
// Two scopes for basic: Program and FunBody
int currentScope = 0; // Start at global scope
char *errors;

// Update the global symbol tables used for iterating over the Ste's
void updateGlobSymbolTables(node_st *newSte) {
    // Update first symbol table if it is NULL 
    if (firstSymbolTable == NULL) {
        firstSymbolTable = newSte;
        previousSymbolTable = newSte;
    } else {
        // Update next of previous symbol table
        STE_NEXT(previousSymbolTable) = newSte;
        previousSymbolTable = newSte;
    }
}

// Find an Ste node that has the specified name
node_st *findSteLink(char *name) {
    printf("Trying to find Ste for: %s\n", name);

    // return the Symbol table entry that is linked to this node (with name)
    // Use linear search to find the entry, stop when next is NULL
    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Match found, return Ste node. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STE_NAME(symbolTable), name) == 0) {
                printf("**********************Link found for: %s\n", name);
                return symbolTable;
            }

            // Update symbolTable
            symbolTable = STE_NEXT(symbolTable);
        } while (symbolTable != NULL);
    }

    printf("No link found for linking an Ste to a Var, VarLet or FunCall!\n");
    // No existing symbol found, return NULL
    return NULL;
}

// Check if a symbol is unique
bool isSymbolUnique(char *name) {
    // Check if the name is not already present in the symbol table entries (use linear search)

    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Symbol already present, return not unique/false. Use string comparison 
            // to check for equality, 0 means equal. == only checks if memory references are equal
            if (strcmp(STE_NAME(symbolTable), name) == 0) {
                printf("**********************Link found for %s\n", name);
                return false;
            }

            // Update symbolTable
            symbolTable = STE_NEXT(symbolTable);
        } while (symbolTable != NULL);
    }

    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

// Create a symbol table entry node
bool createSymbolTableEntry(char *name, enum Type type, enum SymbolTableType steType, node_st *params) {
    // First check if the name is already present, if so, save it in errors
    if (isSymbolUnique(name)) {
        // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
        node_st *newSte = ASTste(NULL, name, type, currentScope, steType, params);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        // Ste creation succeeded
        return true;
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("multiple matching declarations/definitions found\n");
    }

    // Creation failed
    return false;
}

// Check for argument numbers matching parameter numbers
bool compareFunCallArgumentsLength(node_st *funcallNode, node_st *steLink) {
    // Get the parameter count
    int parameterCount = 0;
    // Get the first param from the Ste
    node_st *paramIterator = STE_PARAMS(steLink);
    do {
        // Increment parameter count
        parameterCount++;

        // Update parameter
        paramIterator = PARAM_NEXT(paramIterator);
    } while (paramIterator != NULL);

    // Get the count of the arguments in the funcall node
    int argumentsCount = 0;
    if (FUNCALL_ARGS(funcallNode) != NULL) {
        // Get the first param from the Ste
        node_st *funcallArgsIterator = FUNCALL_ARGS(funcallNode);
        do {
            // Increment parameter count
            argumentsCount++;

            // Update parameter
            funcallArgsIterator = EXPRS_NEXT(funcallArgsIterator);
        } while (funcallArgsIterator != NULL);
    }

    if (parameterCount == argumentsCount) {
        // Equal arguments and parameter numbers
        return true;
    } else {
        // Not equal arguments and parameter numbers
        return false;
    }
}

/**
 * @fn CAprogram
 */
node_st *CAprogram(node_st *node)
{
    //TODO: Good idea to save the first empty Ste in the attributes of the Program node
    // to use for iterating over all the Ste's???

    printf("\n\n\n****************************************************************************************************************************************************************************** \
    \t\tStart of context analysis\n");
    // Go to the decls traversal
    TRAVdecls(node);

    // TODO: print errors at the end and stop compilation, how to do that???
    //TODO: remove errors, not necessary, see implementation of error funcall part
    if (errors != NULL) {
        // Stop compilation and print errors
    } else {
        // Print all the symbol tables at the end of the traversal
        printSymbolTables();
    }

    printf("\n\n\n\t\tEnd of context analysis\n****************************************************************************************************************************************************************************** \
        \n");

    // Nothing is changed to the program node, so just return the node again
    return node;
}

/**
 * @fn CAdecls
 */
node_st *CAdecls(node_st *node)
{
    printf("decls\n");

    // To perfom the traversal functions of the children use TRAVchildx(node)
    if (DECLS_DECL(node) != NULL) {
            TRAVdecl(node);
    }
    TRAVnext(node);
    // This will now go to the GlobDef, GlobDecl, FunDef traversals

    return node;
}

/*
******************************************************* START DECLS *******************************************************
First the GlobDef, GlobDecl and FunDef nodes and its children will fill the Symbol table entries.
Then after that the FunDef scope will be used to fill the next level of Symbol table entries.
*/

/**
 * @fn CAglobdecl
 */
node_st *CAglobdecl(node_st *node)
{
    printf("globdecl\n");

    // Create a symbol table entry
    createSymbolTableEntry(GLOBDECL_NAME(node), GLOBDECL_TYPE(node), STT_var, NULL);

    return node;
}

/**
 * @fn CAglobdef
 */
node_st *CAglobdef(node_st *node)
{
    printf("globdef\n");

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(GLOBDEF_NAME(node), GLOBDEF_TYPE(node), STT_var, NULL);

    return node;
}

/**
 * @fn CAfundef
 */
node_st *CAfundef(node_st *node)
{
    printf("fundef\n");

    // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
    // Provide the first param of the FunDef to save as the params
    createSymbolTableEntry(FUNDEF_NAME(node), FUNDEF_TYPE(node), STT_function, FUNDEF_PARAMS(node));

    // Save the oldScope
    int oldScope = currentScope;
    // Increment the current scope inside a function body for every function body 
    // (basic has global, funbody and statements (if, while, etc) scope)
    currentScope++;

    // Then go to the traversal function of the paramaters, use current symbol table to update params
    TRAVparams(node);
    // Then go to the funbody after that to traverse that node
    TRAVbody(node);

    // Update the scope to the old scope after the statements when you get back to this funbody
    currentScope = oldScope;

    return node;
}

/*
******************************************************* END DECLS *******************************************************
*/

/*
******************************************************* START FUNDEF *******************************************************
Here the FunDef part will be used to fill the next level of Symbol table entries.
*/

/**
 * @fn CAparam
 */
node_st *CAparam(node_st *node)
{
    printf("param\n");

    // Use the previousSymbolTable because that is the FunDef which contains the params
    // If it is not null it contains the LinkedList of type Param from the FunDef
    if (STE_PARAMS(previousSymbolTable) != NULL) {
        // Get the first param from the Ste
        node_st *paramIterator = STE_PARAMS(previousSymbolTable);
        do {
            // Create a symbol table entry for param (link it later in the Var, Varlet and Funcall)
            createSymbolTableEntry(PARAM_NAME(paramIterator), PARAM_TYPE(paramIterator), STT_var, NULL);

            // Update symbolTable
            paramIterator = PARAM_NEXT(paramIterator);
        } while (paramIterator != NULL);
    }

    // If this param has a next, do the same for the next param in the function definition
    TRAVnext(node);

    return node;
}

/**
 * @fn CAfunbody
 */
node_st *CAfunbody(node_st *node)
{
    printf("funbody\n");

    // Go to the vardecls and create the symbol table entries
    TRAVdecls(node);

    // Then after that, go to the Stmts, wich are the IfElse, While, DoWhile and For 
    TRAVstmts(node);

    return node;
}

/*
******************************************************* END FUNDEF *******************************************************
*/

/*
******************************************************* START FUNBODY *******************************************************
Here the FunBody part will be used to fill the next level of Symbol table entries.
This part can have VarDecls and/or Stmts.
*/

/**
 * @fn CAvardecl
 */
node_st *CAvardecl(node_st *node)
{
    printf("vardecls\n");

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    createSymbolTableEntry(VARDECL_NAME(node), VARDECL_TYPE(node), STT_var, NULL);

    // Go to the traversal function of the expr to go to the Vars
    TRAVinit(node);

    // To perfom the traversal functions of the children use TRAVchildx(node)
    TRAVnext(node);

    return node;
}

/**
 * @fn CAstmts
 */
node_st *CAstmts(node_st *node)
{
    printf("statements\n");

    // To perfom the traversal functions of the children use TRAVchildx(node)
    TRAVstmt(node);
    TRAVnext(node);

    return node;
}

/**
 * @fn CAifelse
 */
node_st *CAifelse(node_st *node)
{
    // Updating scope not necessary, no VarDecls or FunDefs in Stmts (see language)!

    // Go to stmts traversal functions
    TRAVthen(node);
    TRAVelse_block(node);
    
    return node;
}

/**
 * @fn CAwhile
 */
node_st *CAwhile(node_st *node)
{
    // Updating scope not necessary, no VarDecls or FunDefs in Stmts (see language)!

    // Go to stmts traversal functions
    TRAVblock(node);

    return node;
}

/**
 * @fn CAdowhile
 */
node_st *CAdowhile(node_st *node)
{
    // Updating scope not necessary, no VarDecls or FunDefs in Stmts (see language)!

    // Go to stmts traversal functions
    TRAVblock(node);

    return node;
}

/**
 * @fn CAfor
 */
node_st *CAfor(node_st *node)
{
    // Updating scope not necessary, no VarDecls or FunDefs in Stmts (see language)!
    
    // remove the declaration part from for-loop induction variables and create corresponding 
    // local variable declarations on the level of the (innermost) function definition
    // For var declaration always has type int and name is saved in For node
    createSymbolTableEntry(FOR_VAR(node), CT_int, STT_var, NULL);

    //TODO: multiple i's in one function scope should return an error right?

    // Go to stmts traversal functions
    TRAVblock(node);

    return node;
}


/*
******************************************************* END FUNBODY *******************************************************
*/


/*
******************************************************* START LINKING PART *******************************************************
These traversals need to link the corresponding funcall, var or varlet with a Ste from the 
LinkedList of Ste's. It then needs to be 'linked' to the Link attribute in those nodes.
*/


/**
 * @fn CAassign
 */
node_st *CAassign(node_st *node)
{
    printf("Got to assign!\n");

    // Go to varlet traversal function
    TRAVlet(node);
    // Go to the expr
    TRAVexpr(node);

    return node;
}

/**
 * @fn CAexprs
 */
node_st *CAexprs(node_st *node)
{
    printf("Got to exprs!\n");

    // Go to the traversal functions of exprs, which are funcall and var
    if (EXPRS_EXPR(node) != NULL) {
        TRAVdecl(node);
    }
    TRAVnext(node);

    return node;
}

/**
 * @fn CAfuncall
 */
node_st *CAfuncall(node_st *node)
{
    // Update this link from var to the Ste with the given name. The link a Var, Varlet or FunCall node
    // Only needs to be updated once they appear again. For example void foo() {int a;} == no link
    // void foo() {int a; a = 5; foo();} == two links needs to be updated
    node_st *steNode = findSteLink(FUNCALL_NAME(node));
    if (steNode != NULL) {
        if (STE_PARAMS(steNode) != NULL) {
            // If the arguments and parameter numbers are not equal, then error
            if (compareFunCallArgumentsLength(node, steNode)) {
                // Save Ste node in link attribute
                FUNCALL_STE_LINK(node) = steNode;
            } else {
                // TODO: save error, argument numbers do not match parameter numbers
                 printf("argument numbers do not match parameter numbers\n");

                 // Prints the error when it occurs, so in this line
                 CTI(CTI_ERROR, true, "argument numbers for function '%s' do not match parameter numbers", FUNCALL_NAME(node));
                // Create error action, will stop the current compilation after this Action (contextanalysis traversal)
                 CCNerrorAction();
            }
        } else {
            // Save Ste node in link attribute
            FUNCALL_STE_LINK(node) = steNode;
        }
    } else {
        // Save in errors, no matching declaration/definition!
        // TODO
        printf("no matching declaration/definition for funcall found\n");
    }

    printf("*************************symbol table link funcall\n");

    // No changes made to the node directly, so no need to return a new node here
    return node;
}

/**
 * @fn CAvar
 */
node_st *CAvar(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    node_st *steNode = findSteLink(VAR_NAME(node));
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VAR_STE_LINK(node) = steNode;
    } else {
        // Save in errors, no matching declaration/definition!
        // TODO
        printf("no matching declaration/definition for var found\n");
    }

    printf("*************************symbol table link var\n");

    return node;
}

/**
 * @fn CAvarlet
 */
node_st *CAvarlet(node_st *node)
{
    // Update this link from varlet to the Ste with the given name
    node_st *steNode = findSteLink(VARLET_NAME(node));
    if (steNode != NULL) {
        // Save Ste node in link attribute
        VARLET_STE_LINK(node) = steNode;
    } else {
        // Save in errors, no matching declaration/definition!
        // TODO
        printf("no matching declaration/definition for varlet found\n");
    }

    printf("*************************symbol table link varlet\n");

    return node;
}

/*
******************************************************* END LINKING PART *******************************************************
*/

// Print all symbol table entries using the linked list and firstSymbolTable
void printSymbolTables()
{    
    // Print Ste's
    if (firstSymbolTable != NULL) {
        // Print a couple of new lines before printing the Ste's
        printf("\n\n\n****************************************************************************************************************************************************************************** \
        \t\tSymbol Tables Entries created:\n");

        node_st *symbolTable = firstSymbolTable;
        do {
            // Get the type
            char *type = NULL;

            switch (STE_TYPE(symbolTable)) {
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
            
            // Get the SymbolTableType
            char *stType = NULL;
            switch (STE_SYMBOL_TYPE(symbolTable)) {
                case STT_var:
                stType = "var";
                break;
                case STT_varlet:
                stType = "varlet";
                break;
                case STT_function:
                stType = "function";
                break;
                case STT_NULL:
                DBUG_ASSERT(false, "unknown SymbolTableType detected!");
            }

            // Print the Ste
            if (STE_SYMBOL_TYPE(symbolTable) == STT_function) {
                // Print function Ste: "funName: returnType (param types)"
                // Declare a C string array with space for 5 strings of 20 characters each
                char *params = MEMmalloc(100 * sizeof(char)); // allocate memory for a string of up to 99 characters
                // Initialize with empty string to avoid weird memory address value being used at the start
                strcpy(params, "");
                
                if (STE_PARAMS(symbolTable) != NULL) {
                    // Get the first param from the Ste
                    node_st *paramIterator = STE_PARAMS(symbolTable);
                    do {
                        // Get the type
                        char *tmp = NULL;
                        switch (PARAM_TYPE(paramIterator)) {
                            case CT_int:
                            tmp = "int";
                            break;
                            case CT_float:
                            tmp = "float";
                            break;
                            case CT_bool:
                            tmp = "bool";
                            break;
                            case CT_void:
                            tmp = "void";
                            break;
                            case CT_NULL:
                            DBUG_ASSERT(false, "unknown type detected!");
                        }

                        // Add the param to the params string to print the fundef
                        strcat(params, tmp);
                        // Add a comma after every value, except the last one
                        if (PARAM_NEXT(paramIterator) != NULL) {
                            strcat(params, ", ");
                        }

                        // Update parameter
                        paramIterator = PARAM_NEXT(paramIterator);
                    } while (paramIterator != NULL);
                }

                // Print the function symbol table
                printf("\nSymbol table entry:\n %s : %s (%s) \nsymbol type: %s, nesting level: %d\n", 
                    STE_NAME(symbolTable), type, params, stType, STE_NESTING_LEVEL(symbolTable));

                // Free the params memory when done because it is not needed anymore
                MEMfree(params);
            } else {
                // Print var Ste: "name, type"
                printf("\nSymbol table entry:\n %s : %s\nsymbol type: %s, nesting level: %d\n", 
                    STE_NAME(symbolTable), type, stType, STE_NESTING_LEVEL(symbolTable));
            }

            // Update symbolTable
            symbolTable = STE_NEXT(symbolTable);
        } while (symbolTable != NULL);

        // Print a couple of new lines before printing the Ste's
        printf("\n\n\n****************************************************************************************************************************************************************************** \
        \n");
    } else {
        printf("\nNo symbol tables found\n");
    }
}