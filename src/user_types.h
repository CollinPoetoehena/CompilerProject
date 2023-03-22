#pragma once

// Include the hash table from palm
#include "palm/hash_table.h"
// Include FILE * from stdio.h in C to work with files
#include <stdio.h>

// Define the hash table user type to use in travdata
typedef htable_st *htable_ptr;
// Define the FILE * user type to use in travdata
typedef FILE *file_ptr;