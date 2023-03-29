#include <stdlib.h>
#include "ccngen/trav_data.h"
#include "ccn/dynamic_core.h"
#include "palm/memory.h"
extern void ACGinit();
extern void ACGfini();
void TRAVdataInitAssemblyCodeGeneration(ccn_trav_st *trav) {
    trav->trav_data.assemblycodegeneration = MEMmalloc(sizeof(struct data_acg));
    struct data_acg *data = trav->trav_data.assemblycodegeneration;
    data->assembly_output_file = 0;
    ACGinit();
}

void TRAVdataFreeAssemblyCodeGeneration(ccn_trav_st *trav) {
    ACGfini();
    MEMfree(trav->trav_data.assemblycodegeneration);
}

extern void TMAFinit();
extern void TMAFfini();
void TRAVdataInitTypeMatchingAssignmentsFunCalls(ccn_trav_st *trav) {
    trav->trav_data.typematchingassignmentsfuncalls = MEMmalloc(sizeof(struct data_tmaf));
    struct data_tmaf *data = trav->trav_data.typematchingassignmentsfuncalls;
    data->funcalls_funcallIndex_paramIndex = 0;
    data->funcalls_funcallIndex_node = 0;
    TMAFinit();
}

void TRAVdataFreeTypeMatchingAssignmentsFunCalls(ccn_trav_st *trav) {
    TMAFfini();
    MEMfree(trav->trav_data.typematchingassignmentsfuncalls);
}

extern void RFIinit();
extern void RFIfini();
void TRAVdataInitRenameForIdentifiers(ccn_trav_st *trav) {
    trav->trav_data.renameforidentifiers = MEMmalloc(sizeof(struct data_rfi));
    struct data_rfi *data = trav->trav_data.renameforidentifiers;
    data->for_stmts_nodes_table = 0;
    data->for_identifiers_table = 0;
    RFIinit();
}

void TRAVdataFreeRenameForIdentifiers(ccn_trav_st *trav) {
    RFIfini();
    MEMfree(trav->trav_data.renameforidentifiers);
}

