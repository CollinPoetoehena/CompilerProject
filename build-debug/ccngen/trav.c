#include <stdbool.h>
#include "palm/dbug.h"
#include "ccn/ccn.h"
#include "ccngen/ast.h"
node_st *TRAVstmts(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNBODY:
            FUNBODY_STMTS(node) = TRAVopt(FUNBODY_STMTS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child stmts");
            break;
    }

    return node;
}

node_st *TRAVstep(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FOR:
            FOR_STEP(node) = TRAVopt(FOR_STEP(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child step");
            break;
    }

    return node;
}

node_st *TRAVright(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_BINOP:
            BINOP_RIGHT(node) = TRAVopt(BINOP_RIGHT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child right");
            break;
    }

    return node;
}

node_st *TRAVnext(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_DECLS:
            DECLS_NEXT(node) = TRAVopt(DECLS_NEXT(node));
            break;
            break;
        case NT_PARAM:
            PARAM_NEXT(node) = TRAVopt(PARAM_NEXT(node));
            break;
            break;
        case NT_VARDECL:
            VARDECL_NEXT(node) = TRAVopt(VARDECL_NEXT(node));
            break;
            break;
        case NT_STMTS:
            STMTS_NEXT(node) = TRAVopt(STMTS_NEXT(node));
            break;
            break;
        case NT_EXPRS:
            EXPRS_NEXT(node) = TRAVopt(EXPRS_NEXT(node));
            break;
            break;
        case NT_STEVAR:
            STEVAR_NEXT(node) = TRAVopt(STEVAR_NEXT(node));
            break;
            break;
        case NT_STEFUN:
            STEFUN_NEXT(node) = TRAVopt(STEFUN_NEXT(node));
            break;
            break;
        case NT_FUNDEFS:
            FUNDEFS_NEXT(node) = TRAVopt(FUNDEFS_NEXT(node));
            break;
            break;
        case NT_IDS:
            IDS_NEXT(node) = TRAVopt(IDS_NEXT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child next");
            break;
    }

    return node;
}

node_st *TRAVindices(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_VARLET:
            VARLET_INDICES(node) = TRAVopt(VARLET_INDICES(node));
            break;
            break;
        case NT_VAR:
            VAR_INDICES(node) = TRAVopt(VAR_INDICES(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child indices");
            break;
    }

    return node;
}

node_st *TRAVexpr(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_ASSIGN:
            ASSIGN_EXPR(node) = TRAVopt(ASSIGN_EXPR(node));
            break;
            break;
        case NT_EXPRSTMT:
            EXPRSTMT_EXPR(node) = TRAVopt(EXPRSTMT_EXPR(node));
            break;
            break;
        case NT_RETURN:
            RETURN_EXPR(node) = TRAVopt(RETURN_EXPR(node));
            break;
            break;
        case NT_CAST:
            CAST_EXPR(node) = TRAVopt(CAST_EXPR(node));
            break;
            break;
        case NT_EXPRS:
            EXPRS_EXPR(node) = TRAVopt(EXPRS_EXPR(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child expr");
            break;
    }

    return node;
}

node_st *TRAVcond(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_IFELSE:
            IFELSE_COND(node) = TRAVopt(IFELSE_COND(node));
            break;
            break;
        case NT_WHILE:
            WHILE_COND(node) = TRAVopt(WHILE_COND(node));
            break;
            break;
        case NT_DOWHILE:
            DOWHILE_COND(node) = TRAVopt(DOWHILE_COND(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child cond");
            break;
    }

    return node;
}

node_st *TRAVparams(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNDEF:
            FUNDEF_PARAMS(node) = TRAVopt(FUNDEF_PARAMS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child params");
            break;
    }

    return node;
}

node_st *TRAVlet(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_ASSIGN:
            ASSIGN_LET(node) = TRAVopt(ASSIGN_LET(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child let");
            break;
    }

    return node;
}

node_st *TRAVstop(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FOR:
            FOR_STOP(node) = TRAVopt(FOR_STOP(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child stop");
            break;
    }

    return node;
}

node_st *TRAVelse_expr(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_TERNARYOP:
            TERNARYOP_ELSE_EXPR(node) = TRAVopt(TERNARYOP_ELSE_EXPR(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child else_expr");
            break;
    }

    return node;
}

node_st *TRAVstmt(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_STMTS:
            STMTS_STMT(node) = TRAVopt(STMTS_STMT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child stmt");
            break;
    }

    return node;
}

node_st *TRAVoperand(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_MONOP:
            MONOP_OPERAND(node) = TRAVopt(MONOP_OPERAND(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child operand");
            break;
    }

    return node;
}

node_st *TRAVparent(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_STEVAR:
            STEVAR_PARENT(node) = TRAVopt(STEVAR_PARENT(node));
            break;
            break;
        case NT_STEFUN:
            STEFUN_PARENT(node) = TRAVopt(STEFUN_PARENT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child parent");
            break;
    }

    return node;
}

node_st *TRAVleft(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_BINOP:
            BINOP_LEFT(node) = TRAVopt(BINOP_LEFT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child left");
            break;
    }

    return node;
}

node_st *TRAVblock(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_WHILE:
            WHILE_BLOCK(node) = TRAVopt(WHILE_BLOCK(node));
            break;
            break;
        case NT_DOWHILE:
            DOWHILE_BLOCK(node) = TRAVopt(DOWHILE_BLOCK(node));
            break;
            break;
        case NT_FOR:
            FOR_BLOCK(node) = TRAVopt(FOR_BLOCK(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child block");
            break;
    }

    return node;
}

node_st *TRAVdecls(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_PROGRAM:
            PROGRAM_DECLS(node) = TRAVopt(PROGRAM_DECLS(node));
            break;
            break;
        case NT_FUNBODY:
            FUNBODY_DECLS(node) = TRAVopt(FUNBODY_DECLS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child decls");
            break;
    }

    return node;
}

node_st *TRAVstart_expr(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FOR:
            FOR_START_EXPR(node) = TRAVopt(FOR_START_EXPR(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child start_expr");
            break;
    }

    return node;
}

node_st *TRAVargs(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNCALL:
            FUNCALL_ARGS(node) = TRAVopt(FUNCALL_ARGS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child args");
            break;
    }

    return node;
}

node_st *TRAVthen_expr(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_TERNARYOP:
            TERNARYOP_THEN_EXPR(node) = TRAVopt(TERNARYOP_THEN_EXPR(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child then_expr");
            break;
    }

    return node;
}

node_st *TRAVdims(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_GLOBDECL:
            GLOBDECL_DIMS(node) = TRAVopt(GLOBDECL_DIMS(node));
            break;
            break;
        case NT_GLOBDEF:
            GLOBDEF_DIMS(node) = TRAVopt(GLOBDEF_DIMS(node));
            break;
            break;
        case NT_PARAM:
            PARAM_DIMS(node) = TRAVopt(PARAM_DIMS(node));
            break;
            break;
        case NT_VARDECL:
            VARDECL_DIMS(node) = TRAVopt(VARDECL_DIMS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child dims");
            break;
    }

    return node;
}

node_st *TRAVbody(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNDEF:
            FUNDEF_BODY(node) = TRAVopt(FUNDEF_BODY(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child body");
            break;
    }

    return node;
}

node_st *TRAVthen(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_IFELSE:
            IFELSE_THEN(node) = TRAVopt(IFELSE_THEN(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child then");
            break;
    }

    return node;
}

node_st *TRAVpredicate(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_TERNARYOP:
            TERNARYOP_PREDICATE(node) = TRAVopt(TERNARYOP_PREDICATE(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child predicate");
            break;
    }

    return node;
}

node_st *TRAVexprs(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_ARREXPR:
            ARREXPR_EXPRS(node) = TRAVopt(ARREXPR_EXPRS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child exprs");
            break;
    }

    return node;
}

node_st *TRAVelse_block(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_IFELSE:
            IFELSE_ELSE_BLOCK(node) = TRAVopt(IFELSE_ELSE_BLOCK(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child else_block");
            break;
    }

    return node;
}

node_st *TRAVinit(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_GLOBDEF:
            GLOBDEF_INIT(node) = TRAVopt(GLOBDEF_INIT(node));
            break;
            break;
        case NT_VARDECL:
            VARDECL_INIT(node) = TRAVopt(VARDECL_INIT(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child init");
            break;
    }

    return node;
}

node_st *TRAVlocal_fundefs(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNBODY:
            FUNBODY_LOCAL_FUNDEFS(node) = TRAVopt(FUNBODY_LOCAL_FUNDEFS(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child local_fundefs");
            break;
    }

    return node;
}

node_st *TRAVfundef(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_FUNDEFS:
            FUNDEFS_FUNDEF(node) = TRAVopt(FUNDEFS_FUNDEF(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child fundef");
            break;
    }

    return node;
}

node_st *TRAVdecl(node_st *node) {
    switch (NODE_TYPE(node)) {
        case NT_DECLS:
            DECLS_DECL(node) = TRAVopt(DECLS_DECL(node));
            break;
            break;
        default:
            DBUG_ASSERT(false, "Current target has no child decl");
            break;
    }

    return node;
}

