/**
 * @file
 *
 * Traversal: ContextAnalysis
 * UID      : CA
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "palm/dbug.h"
#include "ccngen/trav.h"
#include  <string.h>
#include "palm/memory.h"

// Global variable for the first symbol table
// Used to loop through from start to end via next
node_st *firstSymbolTable = NULL;
node_st *previousSymbolTable = NULL;
// Two scopes for basic: Program and FunBody
int currentScope = 0; // Start at global scope
char *errors;

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

/**
 * @fn CAprogram
 */
node_st *CAprogram(node_st *node)
{
    //TODO: Good idea to save the first empty Ste in the attributes of the Program node
    // to use for iterating over all the Ste's???

    printf("\n\n\n****************************************************************************************************************************************************************************** \
        Start of context analysis\n");
    // Go to the decls traversal
    TRAVdecls(node);

    // TODO: print errors at the end and stop compilation, how to do that???
    if (errors != NULL) {
        // Stop compilation and print errors
    } else {
        // Print all the symbol tables at the end of the traversal
        printSymbolTables();
    }

    printf("\n\n\nEnd of context analysis\n****************************************************************************************************************************************************************************** \
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

    // First check if the name is already present, if so, save it in errors
    if (isSymbolUnique(GLOBDECL_NAME(node))) {
        // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
        node_st *newSte = ASTste(NULL, GLOBDECL_NAME(node), GLOBDECL_TYPE(node), currentScope, STT_var);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a globdecl found\n");
    }

    return node;
}

/**
 * @fn CAglobdef
 */
node_st *CAglobdef(node_st *node)
{
    printf("globdef\n");

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    if (isSymbolUnique(GLOBDEF_NAME(node))) {
        // Create a symbol table entry
        node_st *newSte = ASTste(NULL, GLOBDEF_NAME(node), GLOBDEF_TYPE(node), currentScope, STT_var);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        printf("fundef ste made\n");
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a globdef found\n");
    }

    return node;
}

/**
 * @fn CAfundef
 */
node_st *CAfundef(node_st *node)
{
    printf("fundef\n");

    // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
    if (isSymbolUnique(FUNDEF_NAME(node))) {
        // Create a symbol table entry
        node_st *newSte = ASTste(NULL, FUNDEF_NAME(node), FUNDEF_TYPE(node), currentScope, STT_function);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        printf("fundef ste made\n");
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a fundef found\n");
    }

    // Then go to the traversal function of the paramaters, use current symbol table to update params
    TRAVparams(node);

    // Then go to the funbody after that to traverse that node
    TRAVbody(node);

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
    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
    printf("param\n");

    // TODO: use previousSymbolTable to update the params in that symbol table for the fundef that just created the new Ste!

    // TODO: See slides page 38 and 39, param needs to be in inner function
    // Then create a new Ste for the param in the new scope and save name and type (not only type such as in function)
    currentScope++;
    if (isSymbolUnique(PARAM_NAME(node))) {
        // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
        node_st *newSte = ASTste(NULL, PARAM_NAME(node), PARAM_TYPE(node), currentScope, STT_var);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        printf("vardecls ste made\n");
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a param found\n");
    }
    // Decrement scope again to let the funbody traversal apply the correct scope
    currentScope--;

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

    // Increment the current scope inside a function body for every function body 
    // (basic has global, funbody and statements (if, while, etc) scope)
    currentScope++;

    // Go to the vardecls and create the symbol table entries
    TRAVdecls(node);

    // Then after that, go to the Stmts, wich are the IfElse, While, DoWhile and For 
    // and create the symbol table entries there (a scope down in the function body)
    int oldScope = currentScope;
    TRAVstmts(node);
    // Update the scope to the old scope after the statements when you get back to this funbody
    currentScope = oldScope;

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
    if (isSymbolUnique(VARDECL_NAME(node))) {
        // Create a symbol table entry (link it later in the Var, Varlet or Funcall once it appears)
        node_st *newSte = ASTste(NULL, VARDECL_NAME(node), VARDECL_TYPE(node), currentScope, STT_var);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        printf("vardecls ste made\n");
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a vardecl found\n");
    }

    // Go to the traversal function of the expr to go to the Vars
    TRAVinit(node);

    // To perfom the traversal functions of the children use TRAVchildx(node)
    TRAVnext(node);
    // TRAVstmt(node);

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

    //TODO: how to put for variable declaration in start in upper nesting level???
    // For var declaration always has type int and name is saved in For node
    if (isSymbolUnique(FOR_VAR(node))) {
        // Create a symbol table entry
        node_st *newSte = ASTste(NULL, FOR_VAR(node), CT_int, currentScope, STT_var);

        // Update global symbol tables in this traversal
        updateGlobSymbolTables(newSte);

        printf("for var decl ste made\n");
    } else {
        // Save in errors, multiple matching declarations/definitions
        // TODO
        printf("duplicate definition for a for loop vardecl found\n");
    }

    // remove the declaration part from for-loop induction variables and create corresponding 
    // local variable declarations on the level of the (innermost) function definition
    // TRAVstart_expr(node);

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
        // Save Ste node in link attribute
        FUNCALL_STE_LINK(node) = steNode;
    } else {
        // Save in errors, no matching declaration/definition!
        // TODO
        printf("no matching declaration/definition for funcall found\n");
    }

    printf("*************************symbol table link funcall\n");

    // TODO: check if the arguments in the funcall match the paramaters of the called function, otherwise save error!

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
        \nSymbol Tables Entries created:\n");

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
                // TODO: how to get param types in the Ste and print them, ask Simon!!???
                
                // Declare a C string array with space for 5 strings of 20 characters each
                char strArr[5][20] = {"Still", "To", "Do", "Ask", "Simon"}; //TODO: change when implemented Ste new attribute!
                // Get the length of the array
                char *params = MEMmalloc(100 * sizeof(char)); // allocate memory for a string of up to 99 characters
                int len = sizeof(strArr) / sizeof(strArr[0]);
                for (int i = 1; i < len; ++i) {
                    strcat(params, strArr[i]);
                    // Add a comma after every value, except the last one
                    if (i < len - 1) {
                        strcat(params, ", ");
                    }
                }

                // Print the function symbol table
                printf("\nSymbol table entry:\n %s : %s (%s) \nstymbol type: %s, nesting level: %d\n", 
                    STE_NAME(symbolTable), type, params, stType, STE_NESTING_LEVEL(symbolTable));

                // Free the params memory when done because it is not needed anymore
                MEMfree(params);
            } else {
                // Print var Ste: "name, type"
                printf("\nSymbol table entry:\n %s : %s\nstymbol type: %s, nesting level: %d\n", 
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