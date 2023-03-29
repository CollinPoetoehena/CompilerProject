#include <stddef.h>
#include "ccn/action_types.h"
#include "ccngen/action_handling.h"
#include "ccngen/enum.h"
#include "ccngen/ast.h"
#include "ccngen/gate.h"
#include "ccn/phase_driver.h"
enum ccn_action_id cleanup_ids_table[2] = { CCNAC_ID_free, CCNAC_ID_NULL };
enum ccn_action_id typechecking_ids_table[] = {    CCNAC_ID_TYPEMATCHINGASSIGNMENTSFUNCALLS,     CCNAC_ID_NULL, };

enum ccn_action_id contextanalysis_ids_table[] = {    CCNAC_ID_RENAMEFORIDENTIFIERS,     CCNAC_ID_CREATEVARIABLESYMBOLTABLEENTRIES,     CCNAC_ID_CREATEFUNCTIONSYMBOLTABLEENTRIES,     CCNAC_ID_LINKFUNCALLSTOSTEFUNNODE,     CCNAC_ID_NULL, };

enum ccn_action_id rootphase_ids_table[] = {    CCNAC_ID_SPDOSCANPARSE,     CCNAC_ID_CONTEXTANALYSIS,     CCNAC_ID_REGULARASSIGNMENTS,     CCNAC_ID_CONVERTFORTOWHILE,     CCNAC_ID_TYPECHECKING,     CCNAC_ID_ANNOTATEUSELESSCASTEXPRESSIONS,     CCNAC_ID_COMPILINGBOOLEANDISJUNCTIONANDCONJUNCTION,     CCNAC_ID_COMPILINGBOOLEANCASTEXPRESSIONS,     CCNAC_ID_ASSEMBLYCODEGENERATION,     CCNAC_ID_PRINT,     CCNAC_ID_NULL, };

static struct ccn_action ccn_action_array[] = {
{CCN_ACTION_PHASE, CCNAC_ID_TYPECHECKING, "TypeChecking", .phase = {NULL, NT_PROGRAM, typechecking_ids_table, false, CCNAC_ID_TYPECHECKING,},},
{CCN_ACTION_PHASE, CCNAC_ID_CONTEXTANALYSIS, "ContextAnalysis", .phase = {NULL, NT_PROGRAM, contextanalysis_ids_table, false, CCNAC_ID_CONTEXTANALYSIS,},},
{CCN_ACTION_PHASE, CCNAC_ID_ROOTPHASE, "RootPhase", .phase = {NULL, NT_PROGRAM, rootphase_ids_table, false, CCNAC_ID_ROOTPHASE,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_ASSEMBLYCODEGENERATION, "AssemblyCodeGeneration", .traversal = {TRAV_ACG,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_COMPILINGBOOLEANCASTEXPRESSIONS, "CompilingBooleanCastExpressions", .traversal = {TRAV_CBCE,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_COMPILINGBOOLEANDISJUNCTIONANDCONJUNCTION, "CompilingBooleanDisjunctionAndConjunction", .traversal = {TRAV_CBDC,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_ANNOTATEUSELESSCASTEXPRESSIONS, "AnnotateUselessCastExpressions", .traversal = {TRAV_AUCE,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_TYPEMATCHINGASSIGNMENTSFUNCALLS, "TypeMatchingAssignmentsFunCalls", .traversal = {TRAV_TMAF,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_CONVERTFORTOWHILE, "ConvertForToWhile", .traversal = {TRAV_CFTW,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_REGULARASSIGNMENTS, "RegularAssignments", .traversal = {TRAV_RA,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_LINKFUNCALLSTOSTEFUNNODE, "LinkFunCallsToSteFunNode", .traversal = {TRAV_LFTSF,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_CREATEFUNCTIONSYMBOLTABLEENTRIES, "CreateFunctionSymbolTableEntries", .traversal = {TRAV_CFS,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_CREATEVARIABLESYMBOLTABLEENTRIES, "CreateVariableSymbolTableEntries", .traversal = {TRAV_CVS,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_RENAMEFORIDENTIFIERS, "RenameForIdentifiers", .traversal = {TRAV_RFI,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_PRINT, "Print", .traversal = {TRAV_PRT,},},
{CCN_ACTION_PASS, CCNAC_ID_SPDOSCANPARSE, "SPdoScanParse", .pass = {PASS_SPDOSCANPARSE,},},
{CCN_ACTION_TRAVERSAL, CCNAC_ID_free, "Free", .traversal = {TRAV_free,},},
{CCN_ACTION_PHASE, CCNAC_ID_cleanup, "Cleanup", .phase = {NULL, NT_PROGRAM, cleanup_ids_table, false, CCNAC_ID_cleanup,},},
};

struct ccn_action *CCNgetActionFromID(enum ccn_action_id action_id) {
    return &ccn_action_array[action_id];
}

