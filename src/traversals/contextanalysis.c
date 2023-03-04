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

// Global variable for the first symbol table
// Used to loop through from start to end via next
node_st *firstSymbolTable = NULL;
node_st *previousSymbolTable = NULL;
int currentScope = 0; // Start at global scope

void updateCurrentScopeWithStatement() {
    // Simply increment the current scope by one to create a new scope for Stmts
    // There are no symnbol table entries that need to be created here
    currentScope++;

    // Return nothing to avoid warning
    return 0;
}

node_st *findSteLink(char *name) {
    printf("Trying to find Ste for: %s\n", name);

    // return the Symbol table entry that is linked to this node (with name)
    // Use linear search to find the entry, stop when next is NULL
    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Match found, return Ste node
            if (STE_NAME(symbolTable) == name) {
                printf("**********************Link found for %s\n", name);
                return symbolTable;
            }
        } while (STE_NEXT(symbolTable) != NULL);
    }

    // No existing symbol found, return NULL
    return NULL;
}

bool isSymbolUnique(char *name) {
    // Check if the name is not already present in the symbol table entries (use linear search)

    if (firstSymbolTable != NULL) {
        node_st *symbolTable = firstSymbolTable;
        do {
            // Symbol already present, return not unique/false 
            if (STE_NAME(symbolTable) == name) {
                printf("**********************Link found for %s\n", name);
                return false;
            }
        } while (STE_NEXT(symbolTable) != NULL);
    }

    // If the first symbol table is NULL or no match found, then the Ste is guarenteed unique
    return true;
}

/**
 * @fn CAprogram
 */
node_st *CAprogram(node_st *node)
{
    // Create a new symbol table with a new scope (program == global scope)
    // node_st *new = ASTste();
    // Update the current symbol table to use in the other traversals

    //TODO: implement functions above and further implement this.
    // TODO: why do they not come to the traversal of the node!???

    // TODO: remove after testing
    printf("current scope program: %d\n", currentScope);

    // Go to the decls traversal
    TRAVdecls(node);

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

    //TODO: Decls is probably global level and Stmts on above, is that correct, ask Simon????
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
    printf("decl version globdecl\n");

    // First check if the name is already present, if so, save it in errors
    if (isSymbolUnique(GLOBDECL_NAME(node))) {
        // Create a symbol table entry (link it later in the Var, Varlet and Funcall)
        node_st *newSte = ASTste(NULL, GLOBDECL_NAME(node), GLOBDECL_TYPE(node), currentScope, STT_var);

        // Update first symbol table if it is NULL 
        if (firstSymbolTable == NULL) {
            firstSymbolTable = newSte;
            previousSymbolTable = newSte;
        } else {
            // Update next of previous symbol table
            STE_NEXT(previousSymbolTable) = newSte;
            previousSymbolTable = newSte;
        }
    } else {
        // Save in errors, symbol already present
        // TODO
    }

    
    // if (firstSymbolTable != NULL) {
    //     // Update previous symbol table next
    //     STE_NEXT(firstSymbolTable) = newSte;
    // }   

    // // Update symbol table, if previous is NULL it would not have updated the next!
    // firstSymbolTable = newSte;

    return node;
}

/**
 * @fn CAglobdef
 */
node_st *CAglobdef(node_st *node)
{
    printf("decl version glob def\n");

    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)

    return node;
}

/**
 * @fn CAfundef
 */
node_st *CAfundef(node_st *node)
{
    printf("decl version fundef\n");
    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)

    // Go to the traversal function of the paramaters
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

    return node;
}

/**
 * @fn CAfunbody
 */
node_st *CAfunbody(node_st *node)
{
    // Create a new symbol table with a new scope (funbody == one scope under global)
    //TODO: is the currentScope variable correct???

    //TODO: it only gets to the first node: Program, but the parser comes into the funbody from the print

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

    // TODO: remove after testing
    printf("current scope funbody: %d\n", currentScope);

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
    // Create a symbol table entry (link it later in the Var, Varlet and Funcall)

    return node;
}

/**
 * @fn CAstmts
 */
node_st *CAstmts(node_st *node)
{
    printf("decls\n");
    // To perfom the traversal functions of the children use TRAVchildx(node)
    TRAVstmt(node);
    TRAVstmt(node);

    return node;
}

/**
 * @fn CAdowhile
 */
node_st *CAdowhile(node_st *node)
{
    updateCurrentScopeWithStatement();
    return node;
}

/**
 * @fn CAfor
 */
node_st *CAfor(node_st *node)
{
    updateCurrentScopeWithStatement();

    //TODO: how to put for declaration in start in upper nesting level???

    return node;
}

/**
 * @fn CAifelse
 */
node_st *CAifelse(node_st *node)
{
    updateCurrentScopeWithStatement();
    return node;
}

/**
 * @fn CAwhile
 */
node_st *CAwhile(node_st *node)
{
    updateCurrentScopeWithStatement();
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
 * @fn CAfuncall
 */
node_st *CAfuncall(node_st *node)
{
    // Update this link from var to the Ste with the given name 
    //FUNCALL_STE_LINK(node) = newSte;     

    printf("*************************symbol table link\n");

    // TODO: is scope 1?? And what about statements (such as inside a funbody and inside a while statement????)

    // TODO: remove after testing
    printf("current scope funcall: %d\n", currentScope);

    // No changes made to the node directly, so no need to return a new node here
    return node;
}

/**
 * @fn CAvar
 */
node_st *CAvar(node_st *node)
{
    //TODO: how do i get to this part because the traversal function is not getting here

    // Update this link from var to the Ste with the given name 
    // VAR_STE_LINK(node) = newSte;

    printf("*************************symbol table link\n");

    // TODO: remove after testing
    printf("current scope var: %d\n", currentScope);

    return node;
}

/**
 * @fn CAvarlet
 */
node_st *CAvarlet(node_st *node)
{
    // Update this link from varlet to the Ste with the given name 
    // VARLET_STE_LINK(node) = newSte;

    // TODO: remove after testing
    printf("current scope varlet: %d\n", currentScope);

    printf("*************************symbol table link\n");

    return node;
}

/*
******************************************************* END LINKING PART *******************************************************
*/