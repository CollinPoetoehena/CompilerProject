#include "ccngen/ast.h"
#include "ccn/dynamic_core.h"
#include "palm/memory.h"
struct ccn_node *DELids(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_ids->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_ids);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELarrexpr(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_arrexpr);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfundefs(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_fundefs);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELstefun(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_stefun->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_stefun);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELstevar(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_stevar->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_stevar);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELbool(struct ccn_node *arg_node) {
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_bool);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfloat(struct ccn_node *arg_node) {
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_float);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELnum(struct ccn_node *arg_node) {
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_num);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELvar(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_var->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_var);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELexprs(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_exprs);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfuncall(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_funcall->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_funcall);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELcast(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_cast);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELvarlet(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_varlet->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_varlet);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELternaryop(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_ternaryop);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELmonop(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_monop);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELbinop(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_binop);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELreturn(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_return);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfor(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_for->var);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_for);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELdowhile(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_dowhile);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELwhile(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_while);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELifelse(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_ifelse);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELexprstmt(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_exprstmt);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELassign(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_assign);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELstmts(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_stmts);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELvardecl(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_vardecl->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_vardecl);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELparam(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_param->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_param);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfunbody(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_funbody);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELfundef(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_fundef->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_fundef);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELglobdef(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_globdef->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_globdef);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELglobdecl(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(arg_node->data.N_globdecl->name);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_globdecl);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELdecls(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_decls);
    MEMfree(arg_node);
    return NULL;
}

struct ccn_node *DELprogram(struct ccn_node *arg_node) {
    TRAVchildren(arg_node);
    MEMfree(NODE_FILENAME(arg_node));
    MEMfree(arg_node->data.N_program);
    MEMfree(arg_node);
    return NULL;
}

