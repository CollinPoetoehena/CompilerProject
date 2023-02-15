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
    // Get travdata from CI traversal
    struct data_ci *data = DATA_CI_GET();

    // Get the identifier from the hash table
    void *value = HTLookup(data, VAR_NAME(node));

    // Create struct and use global variable with MEMmalloc (#include "palm/memory.h")
    struct identifierCounter *id = MEMmalloc(sizeof(struct identifierCounter));
    // With pointers you do not use . to access variables but ->
    id->counter = 1;
    // Insert into the string hash table
    HTinsert(data, VAR_NAME(node), (void *) id);

    // Cast to void * because the parameter is of type void *
    struct identifierCounter *id = (struct identifierCounter *) value; // Get the value

    if (value == NULL) {
        // Save the variable in global memory (TODO: change without global variable, not permitted)
        
        /

    } else {
        // cast void * back to actual type
        // struct identifierCounter *id = (struct identifierCounter *) value;
        
        id->counter
        // Create new hash table
        htable_st *hash_table = HTnew_String();
        // Waardes is met HTLookup();
        data->id_table = hash_table;
    }

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

