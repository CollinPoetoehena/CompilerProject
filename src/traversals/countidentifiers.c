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

void CIinit() { return; }
void CIfini() { return; }

/**
 * @fn CIvar
 */
node_st *CIvar(node_st *node)
{
    // TODO: are these the correct identifiers or are they other nodes????

    // Get travdata from CI traversal
    struct data_ci *data = DATA_CI_GET();

    // TODO: update the hash table
    // if (data != NULL) {
    //     // Insert or update entry
    //     // HTinsert();
    // } else {
    //     // Create new hash table
    //     htable_st *hash_table = HTnew();
    //     // Waardes is met HTLookup();
    //     data->id_table = hash_table;
    // }

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

