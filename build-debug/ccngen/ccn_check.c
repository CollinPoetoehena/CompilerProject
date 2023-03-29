#include <stdbool.h>
#include "ccn/dynamic_core.h"
#include "ccn/phase_driver.h"
#include "ccngen/ast.h"
#include "palm/ctinfo.h"
char *nodetypeToName(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_IDS:
            return "Ids";
            break;
        case NT_ARREXPR:
            return "ArrExpr";
            break;
        case NT_FUNDEFS:
            return "FunDefs";
            break;
        case NT_STEFUN:
            return "SteFun";
            break;
        case NT_STEVAR:
            return "SteVar";
            break;
        case NT_BOOL:
            return "Bool";
            break;
        case NT_FLOAT:
            return "Float";
            break;
        case NT_NUM:
            return "Num";
            break;
        case NT_VAR:
            return "Var";
            break;
        case NT_EXPRS:
            return "Exprs";
            break;
        case NT_FUNCALL:
            return "FunCall";
            break;
        case NT_CAST:
            return "Cast";
            break;
        case NT_VARLET:
            return "VarLet";
            break;
        case NT_TERNARYOP:
            return "TernaryOp";
            break;
        case NT_MONOP:
            return "Monop";
            break;
        case NT_BINOP:
            return "Binop";
            break;
        case NT_RETURN:
            return "Return";
            break;
        case NT_FOR:
            return "For";
            break;
        case NT_DOWHILE:
            return "DoWhile";
            break;
        case NT_WHILE:
            return "While";
            break;
        case NT_IFELSE:
            return "IfElse";
            break;
        case NT_EXPRSTMT:
            return "ExprStmt";
            break;
        case NT_ASSIGN:
            return "Assign";
            break;
        case NT_STMTS:
            return "Stmts";
            break;
        case NT_VARDECL:
            return "VarDecl";
            break;
        case NT_PARAM:
            return "Param";
            break;
        case NT_FUNBODY:
            return "FunBody";
            break;
        case NT_FUNDEF:
            return "FunDef";
            break;
        case NT_GLOBDEF:
            return "GlobDef";
            break;
        case NT_GLOBDECL:
            return "GlobDecl";
            break;
        case NT_DECLS:
            return "Decls";
            break;
        case NT_PROGRAM:
            return "Program";
            break;
        default:
            return "Unknown";
                }

}

static bool TypeIslink(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_STEVAR || node_type == NT_STEFUN    );
}

static bool TypeIsstmt(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_ASSIGN || node_type == NT_EXPRSTMT || node_type == NT_DOWHILE || node_type == NT_IFELSE || node_type == NT_FOR || node_type == NT_WHILE || node_type == NT_RETURN    );
}

static bool TypeIsexpr(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_CAST || node_type == NT_ARREXPR || node_type == NT_BOOL || node_type == NT_BINOP || node_type == NT_FUNCALL || node_type == NT_FLOAT || node_type == NT_VAR || node_type == NT_NUM || node_type == NT_MONOP || node_type == NT_TERNARYOP    );
}

static bool TypeIsvars(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_VARDECL || node_type == NT_VAR || node_type == NT_VARLET    );
}

static bool TypeIsdecl(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_GLOBDEF || node_type == NT_GLOBDECL || node_type == NT_FUNDEF    );
}

static bool TypeIsoperations(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_BINOP || node_type == NT_MONOP || node_type == NT_TERNARYOP    );
}

static bool TypeIsconstants(node_st *arg_node) {
    enum ccn_nodetype node_type = NODE_TYPE(arg_node);
    return (false || node_type == NT_FLOAT || node_type == NT_BOOL || node_type == NT_NUM    );
}

struct ccn_node *CHKids(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (IDS_NEXT(arg_node)) {
        if (NODE_TYPE(IDS_NEXT(arg_node)) != NT_IDS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(Ids) has disallowed type(%s) ", nodetypeToName(IDS_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKarrexpr(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (ARREXPR_EXPRS(arg_node)) {
        if (NODE_TYPE(ARREXPR_EXPRS(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(exprs) of node(ArrExpr) has disallowed type(%s) ", nodetypeToName(ARREXPR_EXPRS(arg_node)));
        }

    }

    if (ARREXPR_EXPRS(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(exprs) in node(ArrExpr) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKfundefs(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (FUNDEFS_FUNDEF(arg_node)) {
        if (NODE_TYPE(FUNDEFS_FUNDEF(arg_node)) != NT_FUNDEF) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(fundef) of node(FunDefs) has disallowed type(%s) ", nodetypeToName(FUNDEFS_FUNDEF(arg_node)));
        }

    }

    if (FUNDEFS_FUNDEF(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(fundef) in node(FunDefs) is missing, but specified as mandatory.\n");;
    }

    if (FUNDEFS_NEXT(arg_node)) {
        if (NODE_TYPE(FUNDEFS_NEXT(arg_node)) != NT_FUNDEFS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(FunDefs) has disallowed type(%s) ", nodetypeToName(FUNDEFS_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKstefun(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (STEFUN_PARENT(arg_node)) {
        if (NODE_TYPE(STEFUN_PARENT(arg_node)) != NT_STEFUN) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(parent) of node(SteFun) has disallowed type(%s) ", nodetypeToName(STEFUN_PARENT(arg_node)));
        }

    }

    if (STEFUN_NEXT(arg_node)) {
        if (NODE_TYPE(STEFUN_NEXT(arg_node)) != NT_STEFUN) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(SteFun) has disallowed type(%s) ", nodetypeToName(STEFUN_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKstevar(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (STEVAR_PARENT(arg_node)) {
        if (NODE_TYPE(STEVAR_PARENT(arg_node)) != NT_STEVAR) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(parent) of node(SteVar) has disallowed type(%s) ", nodetypeToName(STEVAR_PARENT(arg_node)));
        }

    }

    if (STEVAR_NEXT(arg_node)) {
        if (NODE_TYPE(STEVAR_NEXT(arg_node)) != NT_STEVAR) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(SteVar) has disallowed type(%s) ", nodetypeToName(STEVAR_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKbool(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    return arg_node;
}

struct ccn_node *CHKfloat(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    return arg_node;
}

struct ccn_node *CHKnum(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    return arg_node;
}

struct ccn_node *CHKvar(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (VAR_INDICES(arg_node)) {
        if (NODE_TYPE(VAR_INDICES(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(indices) of node(Var) has disallowed type(%s) ", nodetypeToName(VAR_INDICES(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKexprs(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (EXPRS_EXPR(arg_node)) {
        if (!TypeIsexpr(EXPRS_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(expr) of node(Exprs) has disallowed type(%s) ", nodetypeToName(EXPRS_EXPR(arg_node)));
        }

    }

    if (EXPRS_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(expr) in node(Exprs) is missing, but specified as mandatory.\n");;
    }

    if (EXPRS_NEXT(arg_node)) {
        if (NODE_TYPE(EXPRS_NEXT(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(Exprs) has disallowed type(%s) ", nodetypeToName(EXPRS_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKfuncall(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (FUNCALL_ARGS(arg_node)) {
        if (NODE_TYPE(FUNCALL_ARGS(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(args) of node(FunCall) has disallowed type(%s) ", nodetypeToName(FUNCALL_ARGS(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKcast(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (CAST_EXPR(arg_node)) {
        if (!TypeIsexpr(CAST_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(expr) of node(Cast) has disallowed type(%s) ", nodetypeToName(CAST_EXPR(arg_node)));
        }

    }

    if (CAST_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(expr) in node(Cast) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKvarlet(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (VARLET_INDICES(arg_node)) {
        if (NODE_TYPE(VARLET_INDICES(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(indices) of node(VarLet) has disallowed type(%s) ", nodetypeToName(VARLET_INDICES(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKternaryop(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (TERNARYOP_PREDICATE(arg_node)) {
        if (!TypeIsexpr(TERNARYOP_PREDICATE(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(predicate) of node(TernaryOp) has disallowed type(%s) ", nodetypeToName(TERNARYOP_PREDICATE(arg_node)));
        }

    }

    if (TERNARYOP_PREDICATE(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(predicate) in node(TernaryOp) is missing, but specified as mandatory.\n");;
    }

    if (TERNARYOP_THEN_EXPR(arg_node)) {
        if (!TypeIsexpr(TERNARYOP_THEN_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(then_expr) of node(TernaryOp) has disallowed type(%s) ", nodetypeToName(TERNARYOP_THEN_EXPR(arg_node)));
        }

    }

    if (TERNARYOP_THEN_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(then_expr) in node(TernaryOp) is missing, but specified as mandatory.\n");;
    }

    if (TERNARYOP_ELSE_EXPR(arg_node)) {
        if (!TypeIsexpr(TERNARYOP_ELSE_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(else_expr) of node(TernaryOp) has disallowed type(%s) ", nodetypeToName(TERNARYOP_ELSE_EXPR(arg_node)));
        }

    }

    if (TERNARYOP_ELSE_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(else_expr) in node(TernaryOp) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKmonop(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (MONOP_OPERAND(arg_node)) {
        if (!TypeIsexpr(MONOP_OPERAND(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(operand) of node(Monop) has disallowed type(%s) ", nodetypeToName(MONOP_OPERAND(arg_node)));
        }

    }

    if (MONOP_OPERAND(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(operand) in node(Monop) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKbinop(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (BINOP_LEFT(arg_node)) {
        if (!TypeIsexpr(BINOP_LEFT(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(left) of node(Binop) has disallowed type(%s) ", nodetypeToName(BINOP_LEFT(arg_node)));
        }

    }

    if (BINOP_LEFT(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(left) in node(Binop) is missing, but specified as mandatory.\n");;
    }

    if (BINOP_RIGHT(arg_node)) {
        if (!TypeIsexpr(BINOP_RIGHT(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(right) of node(Binop) has disallowed type(%s) ", nodetypeToName(BINOP_RIGHT(arg_node)));
        }

    }

    if (BINOP_RIGHT(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(right) in node(Binop) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKreturn(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (RETURN_EXPR(arg_node)) {
        if (!TypeIsexpr(RETURN_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(expr) of node(Return) has disallowed type(%s) ", nodetypeToName(RETURN_EXPR(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKfor(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (FOR_START_EXPR(arg_node)) {
        if (!TypeIsexpr(FOR_START_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(start_expr) of node(For) has disallowed type(%s) ", nodetypeToName(FOR_START_EXPR(arg_node)));
        }

    }

    if (FOR_START_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(start_expr) in node(For) is missing, but specified as mandatory.\n");;
    }

    if (FOR_STOP(arg_node)) {
        if (!TypeIsexpr(FOR_STOP(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(stop) of node(For) has disallowed type(%s) ", nodetypeToName(FOR_STOP(arg_node)));
        }

    }

    if (FOR_STOP(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(stop) in node(For) is missing, but specified as mandatory.\n");;
    }

    if (FOR_STEP(arg_node)) {
        if (!TypeIsexpr(FOR_STEP(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(step) of node(For) has disallowed type(%s) ", nodetypeToName(FOR_STEP(arg_node)));
        }

    }

    if (FOR_BLOCK(arg_node)) {
        if (NODE_TYPE(FOR_BLOCK(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(block) of node(For) has disallowed type(%s) ", nodetypeToName(FOR_BLOCK(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKdowhile(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (DOWHILE_COND(arg_node)) {
        if (!TypeIsexpr(DOWHILE_COND(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(cond) of node(DoWhile) has disallowed type(%s) ", nodetypeToName(DOWHILE_COND(arg_node)));
        }

    }

    if (DOWHILE_COND(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(cond) in node(DoWhile) is missing, but specified as mandatory.\n");;
    }

    if (DOWHILE_BLOCK(arg_node)) {
        if (NODE_TYPE(DOWHILE_BLOCK(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(block) of node(DoWhile) has disallowed type(%s) ", nodetypeToName(DOWHILE_BLOCK(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKwhile(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (WHILE_COND(arg_node)) {
        if (!TypeIsexpr(WHILE_COND(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(cond) of node(While) has disallowed type(%s) ", nodetypeToName(WHILE_COND(arg_node)));
        }

    }

    if (WHILE_COND(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(cond) in node(While) is missing, but specified as mandatory.\n");;
    }

    if (WHILE_BLOCK(arg_node)) {
        if (NODE_TYPE(WHILE_BLOCK(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(block) of node(While) has disallowed type(%s) ", nodetypeToName(WHILE_BLOCK(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKifelse(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (IFELSE_COND(arg_node)) {
        if (!TypeIsexpr(IFELSE_COND(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(cond) of node(IfElse) has disallowed type(%s) ", nodetypeToName(IFELSE_COND(arg_node)));
        }

    }

    if (IFELSE_COND(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(cond) in node(IfElse) is missing, but specified as mandatory.\n");;
    }

    if (IFELSE_THEN(arg_node)) {
        if (NODE_TYPE(IFELSE_THEN(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(then) of node(IfElse) has disallowed type(%s) ", nodetypeToName(IFELSE_THEN(arg_node)));
        }

    }

    if (IFELSE_ELSE_BLOCK(arg_node)) {
        if (NODE_TYPE(IFELSE_ELSE_BLOCK(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(else_block) of node(IfElse) has disallowed type(%s) ", nodetypeToName(IFELSE_ELSE_BLOCK(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKexprstmt(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (EXPRSTMT_EXPR(arg_node)) {
        if (!TypeIsexpr(EXPRSTMT_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(expr) of node(ExprStmt) has disallowed type(%s) ", nodetypeToName(EXPRSTMT_EXPR(arg_node)));
        }

    }

    if (EXPRSTMT_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(expr) in node(ExprStmt) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKassign(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (ASSIGN_LET(arg_node)) {
        if (NODE_TYPE(ASSIGN_LET(arg_node)) != NT_VARLET) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(let) of node(Assign) has disallowed type(%s) ", nodetypeToName(ASSIGN_LET(arg_node)));
        }

    }

    if (ASSIGN_EXPR(arg_node)) {
        if (!TypeIsexpr(ASSIGN_EXPR(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(expr) of node(Assign) has disallowed type(%s) ", nodetypeToName(ASSIGN_EXPR(arg_node)));
        }

    }

    if (ASSIGN_EXPR(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(expr) in node(Assign) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKstmts(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (STMTS_STMT(arg_node)) {
        if (!TypeIsstmt(STMTS_STMT(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(stmt) of node(Stmts) has disallowed type(%s) ", nodetypeToName(STMTS_STMT(arg_node)));
        }

    }

    if (STMTS_STMT(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(stmt) in node(Stmts) is missing, but specified as mandatory.\n");;
    }

    if (STMTS_NEXT(arg_node)) {
        if (NODE_TYPE(STMTS_NEXT(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(Stmts) has disallowed type(%s) ", nodetypeToName(STMTS_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKvardecl(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (VARDECL_DIMS(arg_node)) {
        if (NODE_TYPE(VARDECL_DIMS(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(dims) of node(VarDecl) has disallowed type(%s) ", nodetypeToName(VARDECL_DIMS(arg_node)));
        }

    }

    if (VARDECL_INIT(arg_node)) {
        if (!TypeIsexpr(VARDECL_INIT(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(init) of node(VarDecl) has disallowed type(%s) ", nodetypeToName(VARDECL_INIT(arg_node)));
        }

    }

    if (VARDECL_NEXT(arg_node)) {
        if (NODE_TYPE(VARDECL_NEXT(arg_node)) != NT_VARDECL) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(VarDecl) has disallowed type(%s) ", nodetypeToName(VARDECL_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKparam(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (PARAM_DIMS(arg_node)) {
        if (NODE_TYPE(PARAM_DIMS(arg_node)) != NT_IDS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(dims) of node(Param) has disallowed type(%s) ", nodetypeToName(PARAM_DIMS(arg_node)));
        }

    }

    if (PARAM_NEXT(arg_node)) {
        if (NODE_TYPE(PARAM_NEXT(arg_node)) != NT_PARAM) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(Param) has disallowed type(%s) ", nodetypeToName(PARAM_NEXT(arg_node)));
        }

    }

    if (PARAM_NAME(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Attribute(name) in node(Param) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKfunbody(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (FUNBODY_DECLS(arg_node)) {
        if (NODE_TYPE(FUNBODY_DECLS(arg_node)) != NT_VARDECL) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(decls) of node(FunBody) has disallowed type(%s) ", nodetypeToName(FUNBODY_DECLS(arg_node)));
        }

    }

    if (FUNBODY_LOCAL_FUNDEFS(arg_node)) {
        if (NODE_TYPE(FUNBODY_LOCAL_FUNDEFS(arg_node)) != NT_FUNDEFS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(local_fundefs) of node(FunBody) has disallowed type(%s) ", nodetypeToName(FUNBODY_LOCAL_FUNDEFS(arg_node)));
        }

    }

    if (FUNBODY_STMTS(arg_node)) {
        if (NODE_TYPE(FUNBODY_STMTS(arg_node)) != NT_STMTS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(stmts) of node(FunBody) has disallowed type(%s) ", nodetypeToName(FUNBODY_STMTS(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKfundef(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (FUNDEF_BODY(arg_node)) {
        if (NODE_TYPE(FUNDEF_BODY(arg_node)) != NT_FUNBODY) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(body) of node(FunDef) has disallowed type(%s) ", nodetypeToName(FUNDEF_BODY(arg_node)));
        }

    }

    if (FUNDEF_PARAMS(arg_node)) {
        if (NODE_TYPE(FUNDEF_PARAMS(arg_node)) != NT_PARAM) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(params) of node(FunDef) has disallowed type(%s) ", nodetypeToName(FUNDEF_PARAMS(arg_node)));
        }

    }

    if (FUNDEF_NAME(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Attribute(name) in node(FunDef) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKglobdef(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (GLOBDEF_DIMS(arg_node)) {
        if (NODE_TYPE(GLOBDEF_DIMS(arg_node)) != NT_EXPRS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(dims) of node(GlobDef) has disallowed type(%s) ", nodetypeToName(GLOBDEF_DIMS(arg_node)));
        }

    }

    if (GLOBDEF_INIT(arg_node)) {
        if (!TypeIsexpr(GLOBDEF_INIT(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(init) of node(GlobDef) has disallowed type(%s) ", nodetypeToName(GLOBDEF_INIT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKglobdecl(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (GLOBDECL_DIMS(arg_node)) {
        if (NODE_TYPE(GLOBDECL_DIMS(arg_node)) != NT_IDS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(dims) of node(GlobDecl) has disallowed type(%s) ", nodetypeToName(GLOBDECL_DIMS(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKdecls(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (DECLS_DECL(arg_node)) {
        if (!TypeIsdecl(DECLS_DECL(arg_node))) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(decl) of node(Decls) has disallowed type(%s) ", nodetypeToName(DECLS_DECL(arg_node)));
        }

    }

    if (DECLS_NEXT(arg_node)) {
        if (NODE_TYPE(DECLS_NEXT(arg_node)) != NT_DECLS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(next) of node(Decls) has disallowed type(%s) ", nodetypeToName(DECLS_NEXT(arg_node)));
        }

    }

    TRAVchildren(arg_node);
    return arg_node;
}

struct ccn_node *CHKprogram(struct ccn_node *arg_node) {
    size_t action_id = CCNgetCurrentActionId();
    (void)action_id;
    if (PROGRAM_DECLS(arg_node)) {
        if (NODE_TYPE(PROGRAM_DECLS(arg_node)) != NT_DECLS) {
            CTI(CTI_ERROR, true, "Inconsistent node found in AST. Child(decls) of node(Program) has disallowed type(%s) ", nodetypeToName(PROGRAM_DECLS(arg_node)));
        }

    }

    if (PROGRAM_DECLS(arg_node) == NULL) {
        CTI(CTI_ERROR, true, "Child(decls) in node(Program) is missing, but specified as mandatory.\n");;
    }

    TRAVchildren(arg_node);
    return arg_node;
}

