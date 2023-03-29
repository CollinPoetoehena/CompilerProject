#pragma once
enum nodesettype {
    NS_NULL,
    NS_LINK,
    NS_STMT,
    NS_EXPR,
    NS_VARS,
    NS_DECL,
    NS_OPERATIONS,
    NS_CONSTANTS,
    _NS_SIZE,
};

enum ccn_nodetype {
    NT_NULL,
    NT_IDS,
    NT_ARREXPR,
    NT_FUNDEFS,
    NT_STEFUN,
    NT_STEVAR,
    NT_BOOL,
    NT_FLOAT,
    NT_NUM,
    NT_VAR,
    NT_EXPRS,
    NT_FUNCALL,
    NT_CAST,
    NT_VARLET,
    NT_TERNARYOP,
    NT_MONOP,
    NT_BINOP,
    NT_RETURN,
    NT_FOR,
    NT_DOWHILE,
    NT_WHILE,
    NT_IFELSE,
    NT_EXPRSTMT,
    NT_ASSIGN,
    NT_STMTS,
    NT_VARDECL,
    NT_PARAM,
    NT_FUNBODY,
    NT_FUNDEF,
    NT_GLOBDEF,
    NT_GLOBDECL,
    NT_DECLS,
    NT_PROGRAM,
    _NT_SIZE,
};

enum ccn_traversal_type {
    TRAV_NULL,
    TRAV_ACG,
    TRAV_CBCE,
    TRAV_CBDC,
    TRAV_AUCE,
    TRAV_TMAF,
    TRAV_CFTW,
    TRAV_RA,
    TRAV_LFTSF,
    TRAV_CFS,
    TRAV_CVS,
    TRAV_RFI,
    TRAV_PRT,
    TRAV_free,
    TRAV_check,
    TRAV_cpy,
    _TRAV_SIZE,
};

enum ccn_pass_type {
    PASS_NULL,
    PASS_SPDOSCANPARSE,
    _PASS_SIZE,
};

enum BinOpEnum {
    BO_NULL,
    BO_add,
    BO_sub,
    BO_mul,
    BO_div,
    BO_mod,
    BO_lt,
    BO_le,
    BO_gt,
    BO_ge,
    BO_eq,
    BO_ne,
    BO_and,
    BO_or,
};

enum MonOpEnum {
    MO_NULL,
    MO_not,
    MO_neg,
};

enum Type {
    CT_NULL,
    CT_int,
    CT_float,
    CT_bool,
    CT_void,
};

