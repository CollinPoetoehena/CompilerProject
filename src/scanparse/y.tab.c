/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


/*
The lexer reads input text and generates a sequence of tokens. 
The parser then reads this sequence of tokens and uses it to build an abstract syntax tree (AST) 
representing the structure of the input.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "palm/memory.h"
#include "palm/ctinfo.h"
#include "palm/dbug.h"
#include "palm/str.h"
#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "global/globals.h"

static node_st *parseresult = NULL;
extern int yylex(); /* get next token, no more input returns 0 */
static int yyerror( char *errname); /* prints grammar violation message */
extern FILE *yyin;
void AddLocToNode(node_st *node, void *begin_loc, void *end_loc);

// To define debuuging define these variables and do yydebug = 1 before yyparse() at the end
// #define YYDEBUG 1
// #define parse.trace

#line 101 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BRACKET_L = 258,               /* BRACKET_L  */
    BRACKET_R = 259,               /* BRACKET_R  */
    COMMA = 260,                   /* COMMA  */
    SEMICOLON = 261,               /* SEMICOLON  */
    CURLYBRACE_L = 262,            /* CURLYBRACE_L  */
    CURLYBRACE_R = 263,            /* CURLYBRACE_R  */
    MINUS = 264,                   /* MINUS  */
    PLUS = 265,                    /* PLUS  */
    STAR = 266,                    /* STAR  */
    SLASH = 267,                   /* SLASH  */
    PERCENT = 268,                 /* PERCENT  */
    LE = 269,                      /* LE  */
    LT = 270,                      /* LT  */
    GE = 271,                      /* GE  */
    GT = 272,                      /* GT  */
    EQ = 273,                      /* EQ  */
    NE = 274,                      /* NE  */
    OR = 275,                      /* OR  */
    AND = 276,                     /* AND  */
    EXCLAMATION = 277,             /* EXCLAMATION  */
    TRUEVAL = 278,                 /* TRUEVAL  */
    FALSEVAL = 279,                /* FALSEVAL  */
    LET = 280,                     /* LET  */
    INTTYPE = 281,                 /* INTTYPE  */
    FLOATTYPE = 282,               /* FLOATTYPE  */
    BOOLTYPE = 283,                /* BOOLTYPE  */
    VOIDTYPE = 284,                /* VOIDTYPE  */
    NUM = 285,                     /* NUM  */
    FLOAT = 286,                   /* FLOAT  */
    ID = 287,                      /* ID  */
    IF = 288,                      /* IF  */
    ELSE = 289,                    /* ELSE  */
    WHILE = 290,                   /* WHILE  */
    DO = 291,                      /* DO  */
    FOR = 292,                     /* FOR  */
    RETURN = 293,                  /* RETURN  */
    EXTERN = 294,                  /* EXTERN  */
    EXPORT = 295,                  /* EXPORT  */
    THEN = 296,                    /* THEN  */
    MONOP_MINUS = 297,             /* MONOP_MINUS  */
    TYPECAST = 298,                /* TYPECAST  */
    FUNCTIONCALL = 299             /* FUNCTIONCALL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define BRACKET_L 258
#define BRACKET_R 259
#define COMMA 260
#define SEMICOLON 261
#define CURLYBRACE_L 262
#define CURLYBRACE_R 263
#define MINUS 264
#define PLUS 265
#define STAR 266
#define SLASH 267
#define PERCENT 268
#define LE 269
#define LT 270
#define GE 271
#define GT 272
#define EQ 273
#define NE 274
#define OR 275
#define AND 276
#define EXCLAMATION 277
#define TRUEVAL 278
#define FALSEVAL 279
#define LET 280
#define INTTYPE 281
#define FLOATTYPE 282
#define BOOLTYPE 283
#define VOIDTYPE 284
#define NUM 285
#define FLOAT 286
#define ID 287
#define IF 288
#define ELSE 289
#define WHILE 290
#define DO 291
#define FOR 292
#define RETURN 293
#define EXTERN 294
#define EXPORT 295
#define THEN 296
#define MONOP_MINUS 297
#define TYPECAST 298
#define FUNCTIONCALL 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "parser.y"

 char               *id;
 int                 cint;
 float               cflt;
 enum Type           ctype;
 node_st             *node;

#line 247 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BRACKET_L = 3,                  /* BRACKET_L  */
  YYSYMBOL_BRACKET_R = 4,                  /* BRACKET_R  */
  YYSYMBOL_COMMA = 5,                      /* COMMA  */
  YYSYMBOL_SEMICOLON = 6,                  /* SEMICOLON  */
  YYSYMBOL_CURLYBRACE_L = 7,               /* CURLYBRACE_L  */
  YYSYMBOL_CURLYBRACE_R = 8,               /* CURLYBRACE_R  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_STAR = 11,                      /* STAR  */
  YYSYMBOL_SLASH = 12,                     /* SLASH  */
  YYSYMBOL_PERCENT = 13,                   /* PERCENT  */
  YYSYMBOL_LE = 14,                        /* LE  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_GE = 16,                        /* GE  */
  YYSYMBOL_GT = 17,                        /* GT  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NE = 19,                        /* NE  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_EXCLAMATION = 22,               /* EXCLAMATION  */
  YYSYMBOL_TRUEVAL = 23,                   /* TRUEVAL  */
  YYSYMBOL_FALSEVAL = 24,                  /* FALSEVAL  */
  YYSYMBOL_LET = 25,                       /* LET  */
  YYSYMBOL_INTTYPE = 26,                   /* INTTYPE  */
  YYSYMBOL_FLOATTYPE = 27,                 /* FLOATTYPE  */
  YYSYMBOL_BOOLTYPE = 28,                  /* BOOLTYPE  */
  YYSYMBOL_VOIDTYPE = 29,                  /* VOIDTYPE  */
  YYSYMBOL_NUM = 30,                       /* NUM  */
  YYSYMBOL_FLOAT = 31,                     /* FLOAT  */
  YYSYMBOL_ID = 32,                        /* ID  */
  YYSYMBOL_IF = 33,                        /* IF  */
  YYSYMBOL_ELSE = 34,                      /* ELSE  */
  YYSYMBOL_WHILE = 35,                     /* WHILE  */
  YYSYMBOL_DO = 36,                        /* DO  */
  YYSYMBOL_FOR = 37,                       /* FOR  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_EXTERN = 39,                    /* EXTERN  */
  YYSYMBOL_EXPORT = 40,                    /* EXPORT  */
  YYSYMBOL_THEN = 41,                      /* THEN  */
  YYSYMBOL_MONOP_MINUS = 42,               /* MONOP_MINUS  */
  YYSYMBOL_TYPECAST = 43,                  /* TYPECAST  */
  YYSYMBOL_FUNCTIONCALL = 44,              /* FUNCTIONCALL  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_decls = 47,                     /* decls  */
  YYSYMBOL_decl = 48,                      /* decl  */
  YYSYMBOL_fundef = 49,                    /* fundef  */
  YYSYMBOL_globdecl = 50,                  /* globdecl  */
  YYSYMBOL_globdef = 51,                   /* globdef  */
  YYSYMBOL_param = 52,                     /* param  */
  YYSYMBOL_funbody = 53,                   /* funbody  */
  YYSYMBOL_vardecl = 54,                   /* vardecl  */
  YYSYMBOL_stmts = 55,                     /* stmts  */
  YYSYMBOL_stmt = 56,                      /* stmt  */
  YYSYMBOL_ifelse = 57,                    /* ifelse  */
  YYSYMBOL_while = 58,                     /* while  */
  YYSYMBOL_dowhile = 59,                   /* dowhile  */
  YYSYMBOL_for = 60,                       /* for  */
  YYSYMBOL_return = 61,                    /* return  */
  YYSYMBOL_block = 62,                     /* block  */
  YYSYMBOL_funcall = 63,                   /* funcall  */
  YYSYMBOL_expr = 64,                      /* expr  */
  YYSYMBOL_exprs = 65,                     /* exprs  */
  YYSYMBOL_assign = 66,                    /* assign  */
  YYSYMBOL_type = 67,                      /* type  */
  YYSYMBOL_varlet = 68,                    /* varlet  */
  YYSYMBOL_var = 69,                       /* var  */
  YYSYMBOL_constant = 70,                  /* constant  */
  YYSYMBOL_floatval = 71,                  /* floatval  */
  YYSYMBOL_intval = 72,                    /* intval  */
  YYSYMBOL_boolval = 73                    /* boolval  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   504

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  212

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   121,   121,   127,   132,   139,   143,   147,   156,   160,
     165,   169,   174,   180,   187,   191,   196,   200,   205,   211,
     219,   226,   230,   234,   238,   244,   248,   254,   258,   262,
     267,   272,   277,   281,   285,   291,   295,   301,   305,   309,
     313,   317,   322,   326,   338,   342,   347,   352,   357,   361,
     367,   371,   378,   382,   388,   393,   400,   405,   410,   415,
     420,   425,   430,   435,   440,   445,   450,   455,   460,   465,
     470,   477,   483,   488,   493,   497,   504,   508,   514,   523,
     524,   525,   529,   537,   544,   549,   553,   559,   565,   571,
     575
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BRACKET_L",
  "BRACKET_R", "COMMA", "SEMICOLON", "CURLYBRACE_L", "CURLYBRACE_R",
  "MINUS", "PLUS", "STAR", "SLASH", "PERCENT", "LE", "LT", "GE", "GT",
  "EQ", "NE", "OR", "AND", "EXCLAMATION", "TRUEVAL", "FALSEVAL", "LET",
  "INTTYPE", "FLOATTYPE", "BOOLTYPE", "VOIDTYPE", "NUM", "FLOAT", "ID",
  "IF", "ELSE", "WHILE", "DO", "FOR", "RETURN", "EXTERN", "EXPORT", "THEN",
  "MONOP_MINUS", "TYPECAST", "FUNCTIONCALL", "$accept", "program", "decls",
  "decl", "fundef", "globdecl", "globdef", "param", "funbody", "vardecl",
  "stmts", "stmt", "ifelse", "while", "dowhile", "for", "return", "block",
  "funcall", "expr", "exprs", "assign", "type", "varlet", "var",
  "constant", "floatval", "intval", "boolval", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-154)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-83)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     427,  -154,  -154,  -154,   -15,   225,   243,    18,  -154,   427,
    -154,  -154,  -154,   -11,    59,    33,    44,    49,    50,  -154,
    -154,    74,     7,    90,    20,   101,   171,    15,  -154,   204,
     115,   119,    93,    57,   103,  -154,   142,   172,  -154,   204,
     120,   124,   188,   204,   204,  -154,  -154,  -154,  -154,   129,
    -154,   351,  -154,  -154,  -154,  -154,  -154,   157,   126,   133,
     145,   154,   150,   155,   164,   168,   166,   178,   367,   157,
     179,   246,   197,  -154,  -154,   112,  -154,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
      13,   200,   201,    65,   203,   199,   209,   117,  -154,   117,
    -154,  -154,  -154,  -154,  -154,   383,  -154,   177,   262,   157,
      43,  -154,   218,  -154,   219,   157,   281,   157,   283,  -154,
     297,   157,  -154,   204,  -154,   459,     2,    97,    97,  -154,
    -154,  -154,   152,   152,   152,   152,   448,   448,   472,   485,
     204,   204,   117,  -154,   254,   280,  -154,   399,  -154,  -154,
    -154,  -154,    -1,   204,   299,  -154,  -154,  -154,   315,   157,
     316,   157,  -154,   317,  -154,  -154,   204,   264,   282,   333,
     305,   294,  -154,    43,   204,   415,  -154,  -154,   334,  -154,
     350,  -154,   459,    65,    65,  -154,   204,   349,  -154,   431,
    -154,  -154,  -154,   309,  -154,   300,   204,    43,    65,   353,
     335,  -154,  -154,  -154,   204,   228,    65,   204,  -154,   318,
      65,  -154
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    81,    80,    79,     0,     0,     0,     0,     2,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     1,
       3,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    23,     0,
       0,     0,     0,     0,     0,    89,    90,    88,    87,    83,
      73,     0,    74,    75,    84,    85,    86,    30,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,    70,    71,     0,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,    28,    29,    36,
      38,    39,    40,    41,    42,     0,    37,     0,     0,    30,
       0,    19,     0,    13,     0,    30,     0,    30,     0,    21,
       0,    30,    56,     0,    54,    76,     0,    58,    57,    60,
      59,    61,    62,    63,    64,    65,    66,    69,    67,    68,
       0,     0,     0,    53,     0,     0,    50,     0,    17,    27,
      35,    43,     0,     0,     0,    25,    18,    12,     0,    30,
       0,    30,    11,     0,    72,    55,     0,     0,     0,     0,
       0,     0,    51,    31,     0,     0,    16,    15,     0,     9,
       0,    10,    77,     0,     0,    52,     0,     0,    33,     0,
      78,    14,     8,    44,    46,     0,     0,    32,     0,     0,
       0,    34,    45,    47,     0,     0,     0,     0,    49,     0,
       0,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,   366,  -154,  -154,  -154,  -154,    -5,   -42,  -153,
     -95,   -92,  -154,  -154,  -154,  -154,  -154,  -120,  -154,   -29,
    -154,  -154,     3,  -154,  -154,  -154,  -154,  -154,  -154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    31,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   144,    50,   105,
     126,   106,   107,   108,    52,    53,    54,    55,    56
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   143,   149,    13,   150,   173,   165,   166,    16,    18,
      68,    30,    13,    71,    73,    74,    75,    14,    19,    40,
     188,    21,    41,    34,   174,    32,    35,   120,    61,    63,
      32,    65,    67,     1,     2,     3,    32,    32,   -82,    32,
      32,     1,     2,     3,   201,    72,   125,   169,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,    60,    22,   193,   194,    23,   147,   154,    42,     1,
       2,     3,   142,   158,    43,   160,    24,    27,   202,   163,
      28,    25,    26,     1,     2,     3,   208,    44,    45,    46,
     211,   143,   143,    33,   164,    47,    48,    90,    91,    29,
      92,    93,    94,    95,    36,   155,   143,    62,    79,    80,
      81,   167,   168,    32,   143,    42,   124,   178,   143,   180,
      42,    43,    57,    58,   175,    59,    43,    69,    70,     1,
       2,     3,    75,   109,    44,    45,    46,   182,   110,    44,
      45,    46,    47,    48,    49,   189,    64,    47,    48,    90,
      91,   111,    92,    93,    94,    95,   113,   195,   112,   114,
      42,    77,    78,    79,    80,    81,    43,   200,     1,     2,
       3,   115,   116,   117,    37,   205,    66,    38,   209,    44,
      45,    46,   118,     1,     2,     3,   121,    47,    48,    90,
      91,    42,    92,    93,    94,    95,    39,    43,     1,     2,
       3,   123,    42,   140,   141,   146,   145,    42,    43,   152,
      44,    45,    46,    43,     1,     2,     3,   148,    47,    48,
      49,    44,    45,    46,   156,   157,    44,    45,    46,    47,
      48,    49,   206,   207,    47,    48,    49,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     122,     1,     2,     3,    15,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,   183,     1,
       2,     3,    17,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   184,   153,   159,   170,
     161,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   199,   162,   171,   176,   186,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   210,   177,   179,   181,   187,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     204,   185,   191,   198,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    76,   192,   203,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   119,   196,    20,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   151,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   172,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   190,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   197,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     1,     2,     3,     4,    77,    78,    79,
      80,    81,    82,    83,    84,    85,     5,     6,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,    89,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
      29,    93,    97,     0,    99,     6,     4,     5,     5,     6,
      39,     4,     9,    42,    43,    44,     3,    32,     0,     4,
     173,    32,    27,     3,    25,    22,     6,    69,    33,    34,
      27,    36,    37,    26,    27,    28,    33,    34,    25,    36,
      37,    26,    27,    28,   197,    42,    75,   142,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     4,     3,   183,   184,    32,    95,   109,     3,    26,
      27,    28,     7,   115,     9,   117,    32,     3,   198,   121,
       6,    32,    32,    26,    27,    28,   206,    22,    23,    24,
     210,   183,   184,     3,   123,    30,    31,    32,    33,    25,
      35,    36,    37,    38,     3,   110,   198,     4,    11,    12,
      13,   140,   141,   110,   206,     3,     4,   159,   210,   161,
       3,     9,     7,     4,   153,    32,     9,     7,     4,    26,
      27,    28,     3,     7,    22,    23,    24,   166,     5,    22,
      23,    24,    30,    31,    32,   174,     4,    30,    31,    32,
      33,     6,    35,    36,    37,    38,     6,   186,     4,     4,
       3,     9,    10,    11,    12,    13,     9,   196,    26,    27,
      28,     7,     4,     7,     3,   204,     4,     6,   207,    22,
      23,    24,     4,    26,    27,    28,     7,    30,    31,    32,
      33,     3,    35,    36,    37,    38,    25,     9,    26,    27,
      28,     4,     3,     3,     3,     6,     3,     3,     9,    32,
      22,    23,    24,     9,    26,    27,    28,     8,    30,    31,
      32,    22,    23,    24,     6,     6,    22,    23,    24,    30,
      31,    32,     4,     5,    30,    31,    32,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       4,    26,    27,    28,    29,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     4,    26,
      27,    28,    29,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     4,    25,     7,    35,
       7,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     4,     8,    26,     8,     3,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     4,     8,     8,     8,    32,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       5,     8,     8,    34,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     6,     8,     6,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     6,    25,     9,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     6,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     6,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     6,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    26,    27,    28,    29,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    39,    40,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    29,    39,    40,    46,    47,    48,
      49,    50,    51,    67,    32,    29,    67,    29,    67,     0,
      47,    32,     3,    32,    32,    32,    32,     3,     6,    25,
       4,    52,    67,     3,     3,     6,     3,     3,     6,    25,
       4,    52,     3,     9,    22,    23,    24,    30,    31,    32,
      63,    64,    69,    70,    71,    72,    73,     7,     4,    32,
       4,    52,     4,    52,     4,    52,     4,    52,    64,     7,
       4,    64,    67,    64,    64,     3,     6,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      32,    33,    35,    36,    37,    38,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    64,    66,    67,    68,     7,
       5,     6,     4,     6,     4,     7,     4,     7,     4,     6,
      53,     7,     4,     4,     4,    64,    65,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
       3,     3,     7,    56,    62,     3,     6,    64,     8,    55,
      55,     6,    32,    25,    53,    52,     6,     6,    53,     7,
      53,     7,     8,    53,    64,     4,     5,    64,    64,    55,
      35,    26,     6,     6,    25,    64,     8,     8,    53,     8,
      53,     8,    64,     4,     4,     8,     3,    32,    54,    64,
       6,     8,     8,    62,    62,    64,    25,     6,    34,     4,
      64,    54,    62,     6,     5,    64,     4,     5,    62,    64,
       4,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      50,    51,    51,    51,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    58,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    67,
      67,    67,    68,    69,    70,    70,    70,    71,    72,    73,
      73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     9,     8,
       8,     7,     7,     6,     9,     8,     8,     7,     7,     6,
       4,     6,     5,     4,     3,     4,     2,     2,     1,     1,
       0,     3,     5,     4,     6,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     5,     7,    12,    10,
       2,     3,     3,     1,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     1,     1,     1,     1,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: decls  */
#line 122 "parser.y"
         {
           parseresult = ASTprogram((yyvsp[0].node));
         }
#line 1624 "y.tab.c"
    break;

  case 3: /* decls: decl decls  */
#line 128 "parser.y"
        {
          // $$ = means what you return to coconut
          (yyval.node) = ASTdecls((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1633 "y.tab.c"
    break;

  case 4: /* decls: decl  */
#line 133 "parser.y"
        {
          // Next is NULL
          (yyval.node) = ASTdecls((yyvsp[0].node), NULL);
        }
#line 1642 "y.tab.c"
    break;

  case 5: /* decl: fundef  */
#line 140 "parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1650 "y.tab.c"
    break;

  case 6: /* decl: globdecl  */
#line 144 "parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1658 "y.tab.c"
    break;

  case 7: /* decl: globdef  */
#line 148 "parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1666 "y.tab.c"
    break;

  case 8: /* fundef: EXPORT type ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 157 "parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-7].ctype), (yyvsp[-6].id), true);
        }
#line 1674 "y.tab.c"
    break;

  case 9: /* fundef: EXPORT type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 161 "parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), true);
        }
#line 1683 "y.tab.c"
    break;

  case 10: /* fundef: type ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 166 "parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-7].ctype), (yyvsp[-6].id), false);
        }
#line 1691 "y.tab.c"
    break;

  case 11: /* fundef: type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 170 "parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), false);
        }
#line 1700 "y.tab.c"
    break;

  case 12: /* fundef: EXTERN type ID BRACKET_L param BRACKET_R SEMICOLON  */
#line 175 "parser.y"
        {
          // Empty funbody. FunDec always starts with extern and ends with a ;
          // No need to do anything with EXTERN for the FunDec because they are always external!
          (yyval.node) = ASTfundef(NULL, (yyvsp[-2].node), (yyvsp[-5].ctype), (yyvsp[-4].id), true);
        }
#line 1710 "y.tab.c"
    break;

  case 13: /* fundef: EXTERN type ID BRACKET_L BRACKET_R SEMICOLON  */
#line 181 "parser.y"
        {
          // Empty param and empty funbody. FunDec always starts with extern and ends with a ;
          // No need to do anything with EXTERN for the FunDec because they are always external!
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), true);
        }
#line 1720 "y.tab.c"
    break;

  case 14: /* fundef: EXPORT VOIDTYPE ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 188 "parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), CT_void, (yyvsp[-6].id), true);
        }
#line 1728 "y.tab.c"
    break;

  case 15: /* fundef: EXPORT VOIDTYPE ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 192 "parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, CT_void, (yyvsp[-5].id), true);
        }
#line 1737 "y.tab.c"
    break;

  case 16: /* fundef: VOIDTYPE ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 197 "parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), CT_void, (yyvsp[-6].id), false);
        }
#line 1745 "y.tab.c"
    break;

  case 17: /* fundef: VOIDTYPE ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 201 "parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, CT_void, (yyvsp[-5].id), false);
        }
#line 1754 "y.tab.c"
    break;

  case 18: /* fundef: EXTERN VOIDTYPE ID BRACKET_L param BRACKET_R SEMICOLON  */
#line 206 "parser.y"
        {
          // Empty funbody. FunDec always starts with extern and ends with a ;
          // No need to do anything with EXTERN for the FunDec because they are always external!
          (yyval.node) = ASTfundef(NULL, (yyvsp[-2].node), CT_void, (yyvsp[-4].id), true);
        }
#line 1764 "y.tab.c"
    break;

  case 19: /* fundef: EXTERN VOIDTYPE ID BRACKET_L BRACKET_R SEMICOLON  */
#line 212 "parser.y"
        {
          // Empty param and empty funbody. FunDec always starts with extern and ends with a ;
          // No need to do anything with EXTERN for the FunDec because they are always external!
          (yyval.node) = ASTfundef(NULL, NULL, CT_void, (yyvsp[-3].id), true);
        }
#line 1774 "y.tab.c"
    break;

  case 20: /* globdecl: EXTERN type ID SEMICOLON  */
#line 220 "parser.y"
         {
          // ID has the value that the lexer put into it with STRCopy(yytext)
           (yyval.node) = ASTglobdecl((yyvsp[-2].ctype), (yyvsp[-1].id));
         }
#line 1783 "y.tab.c"
    break;

  case 21: /* globdef: EXPORT type ID LET expr SEMICOLON  */
#line 227 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), true);
        }
#line 1791 "y.tab.c"
    break;

  case 22: /* globdef: type ID LET expr SEMICOLON  */
#line 231 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), false);
        }
#line 1799 "y.tab.c"
    break;

  case 23: /* globdef: EXPORT type ID SEMICOLON  */
#line 235 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), true);
        }
#line 1807 "y.tab.c"
    break;

  case 24: /* globdef: type ID SEMICOLON  */
#line 239 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), false);
        }
#line 1815 "y.tab.c"
    break;

  case 25: /* param: type ID COMMA param  */
#line 245 "parser.y"
      {
        (yyval.node) = ASTparam(NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
      }
#line 1823 "y.tab.c"
    break;

  case 26: /* param: type ID  */
#line 249 "parser.y"
      {
        (yyval.node) = ASTparam(NULL, NULL, (yyvsp[0].id), (yyvsp[-1].ctype));
      }
#line 1831 "y.tab.c"
    break;

  case 27: /* funbody: vardecl stmts  */
#line 255 "parser.y"
        {
          (yyval.node) = ASTfunbody((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1839 "y.tab.c"
    break;

  case 28: /* funbody: vardecl  */
#line 259 "parser.y"
        {
          (yyval.node) = ASTfunbody((yyvsp[0].node), NULL);
        }
#line 1847 "y.tab.c"
    break;

  case 29: /* funbody: stmts  */
#line 263 "parser.y"
        {
          (yyval.node) = ASTfunbody(NULL, (yyvsp[0].node));
        }
#line 1855 "y.tab.c"
    break;

  case 30: /* funbody: %empty  */
#line 267 "parser.y"
        {
          (yyval.node) = ASTfunbody(NULL, NULL);
        }
#line 1863 "y.tab.c"
    break;

  case 31: /* vardecl: type ID SEMICOLON  */
#line 273 "parser.y"
        {
          // dims expr is NULL, initial expr is NULL, next is NULL, name is ID, type is type
          (yyval.node) = ASTvardecl(NULL, NULL, NULL, (yyvsp[-1].id), (yyvsp[-2].ctype));
        }
#line 1872 "y.tab.c"
    break;

  case 32: /* vardecl: type ID LET expr SEMICOLON  */
#line 278 "parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, (yyvsp[-1].node), NULL, (yyvsp[-3].id), (yyvsp[-4].ctype));
        }
#line 1880 "y.tab.c"
    break;

  case 33: /* vardecl: type ID SEMICOLON vardecl  */
#line 282 "parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
        }
#line 1888 "y.tab.c"
    break;

  case 34: /* vardecl: type ID LET expr SEMICOLON vardecl  */
#line 286 "parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-4].id), (yyvsp[-5].ctype));
        }
#line 1896 "y.tab.c"
    break;

  case 35: /* stmts: stmt stmts  */
#line 292 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1904 "y.tab.c"
    break;

  case 36: /* stmts: stmt  */
#line 296 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
        }
#line 1912 "y.tab.c"
    break;

  case 37: /* stmt: assign  */
#line 302 "parser.y"
      {
         (yyval.node) = (yyvsp[0].node);
      }
#line 1920 "y.tab.c"
    break;

  case 38: /* stmt: ifelse  */
#line 306 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1928 "y.tab.c"
    break;

  case 39: /* stmt: while  */
#line 310 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1936 "y.tab.c"
    break;

  case 40: /* stmt: dowhile  */
#line 314 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1944 "y.tab.c"
    break;

  case 41: /* stmt: for  */
#line 318 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1952 "y.tab.c"
    break;

  case 42: /* stmt: return  */
#line 323 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1960 "y.tab.c"
    break;

  case 43: /* stmt: expr SEMICOLON  */
#line 327 "parser.y"
      {
        // This is an expression in a statement, therefore the name Expr Statement
        (yyval.node) = ASTexprstmt((yyvsp[-1].node));
      }
#line 1969 "y.tab.c"
    break;

  case 44: /* ifelse: IF BRACKET_L expr BRACKET_R block  */
#line 339 "parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-2].node), (yyvsp[0].node), NULL);
        }
#line 1977 "y.tab.c"
    break;

  case 45: /* ifelse: IF BRACKET_L expr BRACKET_R block ELSE block  */
#line 343 "parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 1985 "y.tab.c"
    break;

  case 46: /* while: WHILE BRACKET_L expr BRACKET_R block  */
#line 348 "parser.y"
       {
        (yyval.node) = ASTwhile((yyvsp[-2].node), (yyvsp[0].node));
       }
#line 1993 "y.tab.c"
    break;

  case 47: /* dowhile: DO block WHILE BRACKET_L expr BRACKET_R SEMICOLON  */
#line 353 "parser.y"
          {
           (yyval.node) = ASTdowhile((yyvsp[-2].node), (yyvsp[-5].node));
          }
#line 2001 "y.tab.c"
    break;

  case 48: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr COMMA expr BRACKET_R block  */
#line 358 "parser.y"
     {
      (yyval.node) = ASTfor((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-8].id));
     }
#line 2009 "y.tab.c"
    break;

  case 49: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr BRACKET_R block  */
#line 362 "parser.y"
     {
      // No step means NULL, which will be used as + 1, this is coded somewhere else
      (yyval.node) = ASTfor((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), (yyvsp[-6].id));
     }
#line 2018 "y.tab.c"
    break;

  case 50: /* return: RETURN SEMICOLON  */
#line 368 "parser.y"
        {
          (yyval.node) = ASTreturn(NULL);
        }
#line 2026 "y.tab.c"
    break;

  case 51: /* return: RETURN expr SEMICOLON  */
#line 372 "parser.y"
        {
          (yyval.node) = ASTreturn((yyvsp[-1].node));
        }
#line 2034 "y.tab.c"
    break;

  case 52: /* block: CURLYBRACE_L stmts CURLYBRACE_R  */
#line 379 "parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
      }
#line 2042 "y.tab.c"
    break;

  case 53: /* block: stmt  */
#line 383 "parser.y"
      {
        (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
      }
#line 2050 "y.tab.c"
    break;

  case 54: /* funcall: ID BRACKET_L BRACKET_R  */
#line 389 "parser.y"
        {
          // No arguments
          (yyval.node) = ASTfuncall(NULL, (yyvsp[-2].id));
        }
#line 2059 "y.tab.c"
    break;

  case 55: /* funcall: ID BRACKET_L exprs BRACKET_R  */
#line 394 "parser.y"
        {
          (yyval.node) = ASTfuncall((yyvsp[-1].node), (yyvsp[-3].id));
        }
#line 2067 "y.tab.c"
    break;

  case 56: /* expr: BRACKET_L expr BRACKET_R  */
#line 401 "parser.y"
      {
        // $$ = ASTexprstmt($2);
        (yyval.node) = (yyvsp[-1].node);
      }
#line 2076 "y.tab.c"
    break;

  case 57: /* expr: expr PLUS expr  */
#line 406 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_add);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2085 "y.tab.c"
    break;

  case 58: /* expr: expr MINUS expr  */
#line 411 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_sub);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2094 "y.tab.c"
    break;

  case 59: /* expr: expr SLASH expr  */
#line 416 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_div);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2103 "y.tab.c"
    break;

  case 60: /* expr: expr STAR expr  */
#line 421 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_mul);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2112 "y.tab.c"
    break;

  case 61: /* expr: expr PERCENT expr  */
#line 426 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_mod);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2121 "y.tab.c"
    break;

  case 62: /* expr: expr LE expr  */
#line 431 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_le);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2130 "y.tab.c"
    break;

  case 63: /* expr: expr LT expr  */
#line 436 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_lt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2139 "y.tab.c"
    break;

  case 64: /* expr: expr GE expr  */
#line 441 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_ge);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2148 "y.tab.c"
    break;

  case 65: /* expr: expr GT expr  */
#line 446 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_gt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2157 "y.tab.c"
    break;

  case 66: /* expr: expr EQ expr  */
#line 451 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_eq);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2166 "y.tab.c"
    break;

  case 67: /* expr: expr OR expr  */
#line 456 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_or);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2175 "y.tab.c"
    break;

  case 68: /* expr: expr AND expr  */
#line 461 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_and);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2184 "y.tab.c"
    break;

  case 69: /* expr: expr NE expr  */
#line 466 "parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_ne);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2193 "y.tab.c"
    break;

  case 70: /* expr: MINUS expr  */
#line 471 "parser.y"
      {
        // This MINUS uses the MONOP_MINUS precedence rule
        // arithmetic negation, used for arithmetic values (=numbers, etc)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_neg);
        // AddLocToNode($$, &@2);
      }
#line 2204 "y.tab.c"
    break;

  case 71: /* expr: EXCLAMATION expr  */
#line 478 "parser.y"
      {
        // logical negation, used for boolean values (true, false)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_not);
        // AddLocToNode($$, &@2);
      }
#line 2214 "y.tab.c"
    break;

  case 72: /* expr: BRACKET_L type BRACKET_R expr  */
#line 484 "parser.y"
      {
        // Type cast (can be int, float and bool)
        (yyval.node) = ASTcast((yyvsp[0].node), (yyvsp[-2].ctype));
      }
#line 2223 "y.tab.c"
    break;

  case 73: /* expr: funcall  */
#line 489 "parser.y"
      {
        // Funcall belongs in expr and stmt, in expr it does not have a SEMICOLON
        (yyval.node) = (yyvsp[0].node);
      }
#line 2232 "y.tab.c"
    break;

  case 74: /* expr: var  */
#line 494 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2240 "y.tab.c"
    break;

  case 75: /* expr: constant  */
#line 498 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2248 "y.tab.c"
    break;

  case 76: /* exprs: expr  */
#line 505 "parser.y"
      {
        (yyval.node) = ASTexprs((yyvsp[0].node), NULL);
      }
#line 2256 "y.tab.c"
    break;

  case 77: /* exprs: exprs COMMA expr  */
#line 509 "parser.y"
      {
        (yyval.node) = ASTexprs((yyvsp[0].node), (yyvsp[-2].node));
      }
#line 2264 "y.tab.c"
    break;

  case 78: /* assign: varlet LET expr SEMICOLON  */
#line 515 "parser.y"
        {
          (yyval.node) = ASTassign((yyvsp[-3].node), (yyvsp[-1].node));
        }
#line 2272 "y.tab.c"
    break;

  case 79: /* type: BOOLTYPE  */
#line 523 "parser.y"
                { (yyval.ctype) = CT_bool; }
#line 2278 "y.tab.c"
    break;

  case 80: /* type: FLOATTYPE  */
#line 524 "parser.y"
                { (yyval.ctype) = CT_float; }
#line 2284 "y.tab.c"
    break;

  case 81: /* type: INTTYPE  */
#line 525 "parser.y"
                { (yyval.ctype) = CT_int; }
#line 2290 "y.tab.c"
    break;

  case 82: /* varlet: ID  */
#line 530 "parser.y"
        {
          (yyval.node) = ASTvarlet((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2299 "y.tab.c"
    break;

  case 83: /* var: ID  */
#line 538 "parser.y"
        {
          (yyval.node) = ASTvar((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2308 "y.tab.c"
    break;

  case 84: /* constant: floatval  */
#line 545 "parser.y"
          {
            // Assign the value of the floatval grammar rule AST creation to this constant node type
            (yyval.node) = (yyvsp[0].node);
          }
#line 2317 "y.tab.c"
    break;

  case 85: /* constant: intval  */
#line 550 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2325 "y.tab.c"
    break;

  case 86: /* constant: boolval  */
#line 554 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2333 "y.tab.c"
    break;

  case 87: /* floatval: FLOAT  */
#line 560 "parser.y"
           {
             (yyval.node) = ASTfloat((yyvsp[0].cflt));
           }
#line 2341 "y.tab.c"
    break;

  case 88: /* intval: NUM  */
#line 566 "parser.y"
        {
          (yyval.node) = ASTnum((yyvsp[0].cint));
        }
#line 2349 "y.tab.c"
    break;

  case 89: /* boolval: TRUEVAL  */
#line 572 "parser.y"
         {
           (yyval.node) = ASTbool(true);
         }
#line 2357 "y.tab.c"
    break;

  case 90: /* boolval: FALSEVAL  */
#line 576 "parser.y"
         {
           (yyval.node) = ASTbool(false);
         }
#line 2365 "y.tab.c"
    break;


#line 2369 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 580 "parser.y"


/* Add location tracking information to a node in the parse tree */
void AddLocToNode(node_st *node, void *begin_loc, void *end_loc)
{
    // Needed because YYLTYPE unpacks later than top-level decl.
    YYLTYPE *loc_b = (YYLTYPE*)begin_loc;
    YYLTYPE *loc_e = (YYLTYPE*)end_loc;
    NODE_BLINE(node) = loc_b->first_line;
    NODE_BCOL(node) = loc_b->first_column;
    NODE_ELINE(node) = loc_e->last_line;
    NODE_ECOL(node) = loc_e->last_column;
}

/*
yyerror is called by the parser when it encounters a syntax error in the input file.

yyerror should print out user-friendly error messages when there is a syntax error in the input file.
And it should terminate the program.

It takes one argument, which is the char * describing the error message (char * == string type).
CTI (Control and Information) is used to print out the error message with the line number 
and column number where the error occurred. Then  the program is aborted using CTIabortOnError.
*/
static int yyerror( char *error)
{
  CTI(CTI_ERROR, true, "line %d, col %d\nError parsing source code: %s\n",
            global.line, global.col, error);
  CTIabortOnError();
  return( 0);
}

node_st *SPdoScanParse(node_st *root)
{
    DBUG_ASSERT(root == NULL, "Started parsing with existing syntax tree.");
    yyin = fopen(global.input_file, "r");
    if (yyin == NULL) {
        CTI(CTI_ERROR, true, "Cannot open file '%s'.", global.input_file);
        CTIabortOnError();
    }
    // To allow debugging define yydebug = 1; and define variables at the top
    // yydebug = 1;
    yyparse();
    return parseresult;
}
