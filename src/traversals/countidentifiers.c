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

void CIinit() { 
    // initialize hash table, makes sure there is a hash table
    htable_st *hash_table = HTnew_String(100);

    struct data_ci *data = DATA_CI_GET();
    data->id_table = hash_table;

    return; 
}
void CIfini() { return; }

// struct identifierCounter {
//     int counter;
// };

/**
 * @fn CIvar
 */
node_st *CIvar(node_st *node)
{
    // Get the hash table from the travdata of the CI traversal
    struct data_ci *data = DATA_CI_GET();

    // Get the value from the identifier from the hash table
    void *value = HTlookup(data->id_table, VAR_NAME(node));

    if (value == NULL) {
        // Cast to void * because the parameter is of type void *
        HTinsert(data->id_table, VAR_NAME(node), (void *) 1); // correct way

        // Save the variable in global memory (TODO: change without global variable, not permitted)
        // struct identifierCounter *id = MEMmalloc(sizeof(struct identifierCounter));
        
        // // With pointers you do not use . to access variables but ->
        // id->counter = 1;
    } else {
        // Remove the HT entry and re-add it
        HTremove(data->id_table, VAR_NAME(node));

        HTinsert(data->id_table, VAR_NAME(node), (void *) ((int *)value)+1);

        // cast void * back to actual type
        // struct identifierCounter *id = (struct identifierCounter *) value;
        // id->counter

        // Add the hash table to the travdata
        // data->id_table = hash_table;
    }

        MODULE_ID_TABLE(node) = data->id_table;

    return node;
}

/**
 * @fn CIvarlet
 */
node_st *CIvarlet(node_st *node)
{
    // Get travdata from CI traversal
    struct data_ci *data = DATA_CI_GET();

    // TODO: update the hash table

    return node;
}

