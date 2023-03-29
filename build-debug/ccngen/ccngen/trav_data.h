#pragma once
#include"ccngen/ccn_defs.h"
#include "ccn/ccn_types.h"
#ifdef CCN_USES_UNSAFE
#include "user_types.h"
#endif
#include "ccngen/ast.h"
struct data_acg {
    file_ptr assembly_output_file;
};

struct data_tmaf {
    htable_ptr funcalls_funcallIndex_paramIndex;
    htable_ptr funcalls_funcallIndex_node;
};

struct data_rfi {
    htable_ptr for_stmts_nodes_table;
    htable_ptr for_identifiers_table;
};

union TRAV_DATA {
    struct data_acg *assemblycodegeneration;
    struct data_tmaf *typematchingassignmentsfuncalls;
    struct data_rfi *renameforidentifiers;
};

#define DATA_ACG_GET() (TRAVgetCurrent()->trav_data.assemblycodegeneration)
#define DATA_TMAF_GET() (TRAVgetCurrent()->trav_data.typematchingassignmentsfuncalls)
#define DATA_RFI_GET() (TRAVgetCurrent()->trav_data.renameforidentifiers)
void TRAVdataInitAssemblyCodeGeneration(struct ccn_trav *trav);
void TRAVdataFreeAssemblyCodeGeneration(struct ccn_trav *trav);
void TRAVdataInitTypeMatchingAssignmentsFunCalls(struct ccn_trav *trav);
void TRAVdataFreeTypeMatchingAssignmentsFunCalls(struct ccn_trav *trav);
void TRAVdataInitRenameForIdentifiers(struct ccn_trav *trav);
void TRAVdataFreeRenameForIdentifiers(struct ccn_trav *trav);
