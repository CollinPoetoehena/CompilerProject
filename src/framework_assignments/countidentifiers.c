/**
 * @file
 *
 * Traversal: CountIdentifiers
 * UID      : CI
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "palm/hash_table.h"
#include "palm/memory.h"
#include <stdio.h>

void CIinit() { 
    // initialize hash table, makes sure there is a hash table
    htable_st *hash_table = HTnew_String(100);

    struct data_ci *data = DATA_CI_GET();
    data->id_table = hash_table;

    return; 
}
void CIfini() { return; }

/**
 * @fn CIvar
 */
node_st *CIvar(node_st *node)
{
    // Get the hash table from the travdata of the CI traversal
    struct data_ci *data = DATA_CI_GET();

    // Get the value from the identifier from the hash table
    int *value = (int *) HTlookup(data->id_table, VAR_NAME(node));

    if (value == NULL) {
        // Allocate new memory for an int in C to create a new memory block
        int *newValue = MEMmalloc(sizeof(int));
        
        // Dereference newValue and make it equal to 1
        *newValue = 1;
        
        // Insert newValue (= type int *)
        // Cast to void * because the parameter of the HTinsert is of type void *
        HTinsert(data->id_table, VAR_NAME(node), (void *) newValue);
    } else {
        // Dereference value and increment it by 1. No need to insert a new value 
        // because you can directly access that value in the hash table with the pointer
        *value = *value + 1;
    }

    return node;
}

/**
 * @fn CIvarlet
 */
node_st *CIvarlet(node_st *node)
{
    // Get the hash table from the travdata of the CI traversal
    struct data_ci *data = DATA_CI_GET();

    // Get the value from the identifier from the hash table
    int *value = (int *) HTlookup(data->id_table, VARLET_NAME(node));

    if (value == NULL) {
        // Allocate new memory for an int in C to create a new memory block
        int *newValue = MEMmalloc(sizeof(int));
        
        // Dereference newValue and make it equal to 1
        *newValue = 1;
        
        // Insert newValue (= type int *)
        // Cast to void * because the parameter of the HTinsert is of type void *
        HTinsert(data->id_table, VARLET_NAME(node), (void *) newValue);
    } else {
        // Dereference value and increment it by 1. No need to insert a new value 
        // because you can directly access that value in the hash table with the pointer
        *value = *value + 1;
    }


    return node;
}

void * printElement(void * key, void * item) {
    // Dereference int with * operator, char * == type string
    printf("Identifier: %s, occurrences: %d\n", (char *) key, *(int *) item);
}

/**
 * @fn CImodule
 */
node_st *CImodule(node_st *node)
{
    // Go through the whole tree and come back to this function
    TRAVchildren(node);

    // Get travdata from CI traversal
    struct data_ci *data = DATA_CI_GET();

    // Print hash table
    HTmapWithKey(data->id_table, printElement);

    return node;
}