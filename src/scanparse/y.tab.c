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



#line 99 "y.tab.c"

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
    MONOP_MINUS = 296,             /* MONOP_MINUS  */
    TYPECAST = 297,                /* TYPECAST  */
    FUNCTIONCALL = 298             /* FUNCTIONCALL  */
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
#define MONOP_MINUS 296
#define TYPECAST 297
#define FUNCTIONCALL 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 37 "parser.y"

 char               *id;
 int                 cint;
 float               cflt;
 enum Type           ctype;
 node_st             *node;

#line 243 "y.tab.c"

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
  YYSYMBOL_MONOP_MINUS = 41,               /* MONOP_MINUS  */
  YYSYMBOL_TYPECAST = 42,                  /* TYPECAST  */
  YYSYMBOL_FUNCTIONCALL = 43,              /* FUNCTIONCALL  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_decls = 46,                     /* decls  */
  YYSYMBOL_decl = 47,                      /* decl  */
  YYSYMBOL_fundef = 48,                    /* fundef  */
  YYSYMBOL_globdecl = 49,                  /* globdecl  */
  YYSYMBOL_globdef = 50,                   /* globdef  */
  YYSYMBOL_params = 51,                    /* params  */
  YYSYMBOL_param = 52,                     /* param  */
  YYSYMBOL_funbody = 53,                   /* funbody  */
  YYSYMBOL_vardecl = 54,                   /* vardecl  */
  YYSYMBOL_vardecls = 55,                  /* vardecls  */
  YYSYMBOL_stmts = 56,                     /* stmts  */
  YYSYMBOL_stmt = 57,                      /* stmt  */
  YYSYMBOL_ifelse = 58,                    /* ifelse  */
  YYSYMBOL_while = 59,                     /* while  */
  YYSYMBOL_dowhile = 60,                   /* dowhile  */
  YYSYMBOL_for = 61,                       /* for  */
  YYSYMBOL_return = 62,                    /* return  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_funcall = 64,                   /* funcall  */
  YYSYMBOL_expr = 65,                      /* expr  */
  YYSYMBOL_args = 66,                      /* args  */
  YYSYMBOL_assign = 67,                    /* assign  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_varlet = 69,                    /* varlet  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   424

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   124,   130,   137,   144,   150,   162,   168,
     174,   180,   186,   193,   218,   230,   236,   242,   247,   256,
     260,   269,   278,   284,   290,   297,   305,   311,   319,   326,
     335,   339,   347,   351,   355,   361,   367,   373,   380,   386,
     398,   404,   412,   420,   428,   434,   442,   447,   455,   461,
     471,   477,   486,   490,   496,   502,   508,   514,   520,   526,
     532,   538,   544,   550,   556,   562,   568,   576,   583,   589,
     594,   599,   607,   613,   621,   631,   632,   633,   634,   638,
     653,   658,   662,   668,   674,   680,   684
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
  "IF", "ELSE", "WHILE", "DO", "FOR", "RETURN", "EXTERN", "EXPORT",
  "MONOP_MINUS", "TYPECAST", "FUNCTIONCALL", "$accept", "program", "decls",
  "decl", "fundef", "globdecl", "globdef", "params", "param", "funbody",
  "vardecl", "vardecls", "stmts", "stmt", "ifelse", "while", "dowhile",
  "for", "return", "block", "funcall", "expr", "args", "assign", "type",
  "varlet", "constant", "floatval", "intval", "boolval", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-150)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,  -150,  -150,  -150,  -150,   195,   195,     3,  -150,    52,
    -150,  -150,  -150,   -25,   -13,    -7,  -150,  -150,    11,  -150,
       5,    17,    18,  -150,    83,  -150,   157,   146,  -150,   172,
    -150,    21,    31,    29,    32,    95,   157,   157,  -150,  -150,
    -150,  -150,    50,  -150,   321,  -150,  -150,  -150,  -150,  -150,
      57,    56,    62,   359,    77,   195,  -150,   216,    89,  -150,
    -150,   132,  -150,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,  -150,   359,    92,    97,
     117,   125,    70,   126,   162,   122,   195,   386,  -150,   386,
    -150,  -150,  -150,  -150,  -150,   128,  -150,   106,   359,  -150,
    -150,   157,  -150,   350,     8,   103,   103,  -150,  -150,  -150,
      59,    59,    59,    59,   400,   400,   363,   389,   131,   359,
     132,   157,   157,   386,  -150,   105,   118,  -150,   337,  -150,
    -150,  -150,  -150,  -150,   139,  -150,   140,  -150,  -150,   157,
    -150,   143,    84,   234,   252,   144,   154,   115,  -150,  -150,
    -150,   350,  -150,   152,    70,    70,  -150,   157,  -150,   134,
     127,  -150,   270,   157,    70,   161,   305,  -150,  -150,   157,
     198,    70,   157,  -150,   288,    70,  -150
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    77,    76,    75,    78,     0,     0,     0,     2,     4,
       5,     6,     7,     0,     0,     0,     1,     3,    79,    16,
       0,     0,    79,    15,     0,    18,     0,     0,    14,     0,
      17,     0,     0,    20,     0,     0,     0,     0,    85,    86,
      84,    83,    70,    69,     0,    71,    80,    81,    82,    13,
       0,     0,     0,    25,     0,     0,    21,     0,     0,    66,
      67,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    25,     0,    79,
       0,     0,     0,     0,     0,     0,    29,    23,    24,    31,
      34,    35,    36,    37,    38,     0,    32,     0,    25,    19,
      52,     0,    50,    72,     0,    54,    53,    56,    55,    57,
      58,    59,    60,    61,    62,    65,    63,    64,     0,    25,
       0,     0,     0,     0,    49,     0,     0,    46,     0,    11,
      28,    22,    30,    39,    79,    27,     0,    68,    51,     0,
       9,     0,     0,     0,     0,     0,     0,     0,    47,    26,
      10,    73,     8,    33,     0,     0,    48,     0,    79,     0,
      40,    42,     0,     0,     0,     0,     0,    41,    43,     0,
       0,     0,     0,    45,     0,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,   160,  -150,  -150,  -150,  -150,    30,  -150,   -69,
    -150,    91,   -71,   -81,  -150,  -150,  -150,  -150,  -150,  -149,
     -22,   -26,    58,   -11,    27,    23,  -150,  -150,  -150,  -150
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    32,    33,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,   125,
      43,   103,   104,    96,    97,    20,    45,    46,    47,    48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,   124,    19,    16,    23,   160,   161,    18,   118,    57,
      59,    60,   138,   139,    24,   167,   131,    25,   132,    21,
      27,    29,   173,    28,    30,    22,   176,    13,    53,   136,
      26,    95,    14,    15,    55,    54,    13,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     141,    34,   145,    61,    34,    95,    34,    50,   128,    52,
      95,    76,    58,    77,    56,    95,    78,    95,    63,    64,
      65,    66,    67,   124,   124,   137,    95,   123,     1,     2,
       3,     4,    34,   124,    98,    99,   135,    31,   153,   139,
     124,     5,     6,   101,   124,   143,   144,    95,    35,   119,
     120,    95,    79,    80,    36,    81,    82,    83,    84,     1,
       2,     3,     4,   151,    65,    66,    67,    37,    38,    39,
     121,     1,     2,     3,     4,    40,    41,    42,   122,   126,
     129,   162,    95,    95,   133,    35,   102,   166,   134,   140,
     146,    36,    95,   170,   147,   149,   174,   158,   150,    95,
      49,   152,   156,    95,    37,    38,    39,   157,   -51,   163,
      35,   164,    40,    41,    42,    35,    36,   168,   127,    17,
     159,    36,     1,     2,     3,     4,    51,   130,   142,    37,
      38,    39,     0,     0,    37,    38,    39,    40,    41,    42,
       0,     0,    40,    41,    42,     0,     0,     0,     1,     2,
       3,     4,   171,   172,     0,     0,     0,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     100,     1,     2,     3,     4,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   154,     0,
       0,     0,     0,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   155,     0,     0,     0,
       0,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   165,     0,     0,     0,     0,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,   175,     0,     0,     0,     0,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     169,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    62,     0,     0,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,   148,     0,     0,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,    75,     1,     2,     3,     4,     0,
       0,    79,    80,     0,    81,    82,    83,    84,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    79,    80,
       0,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
      26,    82,    13,     0,    15,   154,   155,    32,    77,    35,
      36,    37,     4,     5,     3,   164,    87,     6,    89,    32,
       3,     3,   171,     6,     6,    32,   175,     0,     7,    98,
      25,    53,     5,     6,     5,     4,     9,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
     119,    24,   123,     3,    27,    77,    29,    27,    84,    29,
      82,     4,    35,     7,    32,    87,     4,    89,     9,    10,
      11,    12,    13,   154,   155,   101,    98,     7,    26,    27,
      28,    29,    55,   164,     7,    55,    97,     4,     4,     5,
     171,    39,    40,     4,   175,   121,   122,   119,     3,     7,
       3,   123,    32,    33,     9,    35,    36,    37,    38,    26,
      27,    28,    29,   139,    11,    12,    13,    22,    23,    24,
       3,    26,    27,    28,    29,    30,    31,    32,     3,     3,
       8,   157,   154,   155,     6,     3,     4,   163,    32,     8,
      35,     9,   164,   169,    26,     6,   172,    32,     8,   171,
       4,     8,     8,   175,    22,    23,    24,     3,     6,    25,
       3,    34,    30,    31,    32,     3,     9,     6,     6,     9,
     147,     9,    26,    27,    28,    29,     4,    86,   120,    22,
      23,    24,    -1,    -1,    22,    23,    24,    30,    31,    32,
      -1,    -1,    30,    31,    32,    -1,    -1,    -1,    26,    27,
      28,    29,     4,     5,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       4,    26,    27,    28,    29,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     4,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     4,    -1,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     4,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     4,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       5,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,    26,    27,    28,    29,    -1,
      -1,    32,    33,    -1,    35,    36,    37,    38,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    32,    33,
      -1,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    29,    39,    40,    45,    46,    47,
      48,    49,    50,    68,    68,    68,     0,    46,    32,    67,
      69,    32,    32,    67,     3,     6,    25,     3,     6,     3,
       6,     4,    51,    52,    68,     3,     9,    22,    23,    24,
      30,    31,    32,    64,    65,    70,    71,    72,    73,     4,
      51,     4,    51,     7,     4,     5,    32,    65,    68,    65,
      65,     3,     6,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     4,     7,     4,    32,
      33,    35,    36,    37,    38,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    64,    67,    68,     7,    51,
       4,     4,     4,    65,    66,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    53,     7,
       3,     3,     3,     7,    57,    63,     3,     6,    65,     8,
      55,    56,    56,     6,    32,    67,    53,    65,     4,     5,
       8,    53,    66,    65,    65,    56,    35,    26,     6,     6,
       8,    65,     8,     4,     4,     4,     8,     3,    32,    69,
      63,    63,    65,    25,    34,     4,    65,    63,     6,     5,
      65,     4,     5,    63,    65,     4,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      48,    48,    48,    48,    49,    50,    50,    50,    50,    51,
      51,    52,    53,    53,    53,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    67,    68,    68,    68,    68,    69,
      70,    70,    70,    71,    72,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     9,     8,
       8,     7,     6,     5,     4,     3,     2,     4,     3,     3,
       1,     2,     2,     1,     1,     0,     3,     2,     2,     1,
       2,     1,     1,     4,     1,     1,     1,     1,     1,     2,
       5,     7,     5,     7,    12,    10,     2,     3,     3,     1,
       3,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     1,
       1,     1,     1,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
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
#line 119 "parser.y"
         {
           parseresult = ASTprogram((yyvsp[0].node));
         }
#line 1589 "y.tab.c"
    break;

  case 3: /* decls: decl decls  */
#line 125 "parser.y"
        {
          //TODO: How do I get the decl and next decl in the ASTnode???
          (yyval.node) = ASTdecls((yyvsp[-1].node), NULL);
          //printf("decl and decls\n");
        }
#line 1599 "y.tab.c"
    break;

  case 4: /* decls: decl  */
#line 131 "parser.y"
        {
          //printf("one decl\n");
        }
#line 1607 "y.tab.c"
    break;

  case 5: /* decl: fundef  */
#line 138 "parser.y"
        {
          //TODO: is this correct?
          (yyval.node) = (yyvsp[0].node);
          //TODO: how do I create the Decls node for the AST????
          //printf("fundef decl\n");
        }
#line 1618 "y.tab.c"
    break;

  case 6: /* decl: globdecl  */
#line 145 "parser.y"
        {
          //TODO: is this correct?
          (yyval.node) = (yyvsp[0].node);
          //printf("globdecl decl\n");
        }
#line 1628 "y.tab.c"
    break;

  case 7: /* decl: globdef  */
#line 151 "parser.y"
        {
          //TODO: is this correct?
          (yyval.node) = (yyvsp[0].node);
          //printf("globdef decl\n");
        }
#line 1638 "y.tab.c"
    break;

  case 8: /* fundef: EXPORT type ID BRACKET_L params BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 163 "parser.y"
        {
          //TODO: how do I get funbody and params inside the ASTfundef???
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-7].ctype), (yyvsp[-6].id), true);
          //printf("fun def including funheader params with export\n");
        }
#line 1648 "y.tab.c"
    break;

  case 9: /* fundef: EXPORT type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 169 "parser.y"
        {
          // TODO
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), true);
          //printf("fun def without funheader params with export\n");
        }
#line 1658 "y.tab.c"
    break;

  case 10: /* fundef: type ID BRACKET_L params BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 175 "parser.y"
        {
          // TODO
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-7].ctype), (yyvsp[-6].id), false);
          //printf("fun def including funheader params without export\n");
        }
#line 1668 "y.tab.c"
    break;

  case 11: /* fundef: type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 181 "parser.y"
        {
          //TODO
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), false);
          //printf("fun def wihtout funheader params without export\n");
        }
#line 1678 "y.tab.c"
    break;

  case 12: /* fundef: EXTERN type ID BRACKET_L params BRACKET_R  */
#line 187 "parser.y"
        {
          //TODO: get params in the ASTfundef
          // No need to do anything with EXTERN for the FunDec because they are always external!
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), true);
          //printf("fun dec including funheader params (fundef is also used for a fundec)\n");
        }
#line 1689 "y.tab.c"
    break;

  case 13: /* fundef: EXTERN type ID BRACKET_L BRACKET_R  */
#line 194 "parser.y"
        {
          //TODO
          (yyval.node) = ASTfundef(NULL, NULL, (yyvsp[-3].ctype), (yyvsp[-2].id), true);
          // No need to do anything with EXTERN for the FunDec because they are always external!
          //printf("fun dec without funheader params (fundef is also used for a fundec)\n");
        }
#line 1700 "y.tab.c"
    break;

  case 14: /* globdecl: EXTERN type ID SEMICOLON  */
#line 219 "parser.y"
         {
          // $ refereert naar de positie in je regel
          // $$ = betekent wat die teruggeeft aan coconut
          // in ID zit de waarde die je lexer daarin heeft gezet met STRCopy(yytext)
           (yyval.node) = ASTglobdecl((yyvsp[-2].ctype), (yyvsp[-1].id));
           //TODO: what is Ids node in main.ccn?????
           //printf("global declaration\n");
         }
#line 1713 "y.tab.c"
    break;

  case 15: /* globdef: EXPORT type assign  */
#line 231 "parser.y"
        {
          //TODO: how do I get the expr and ID in the AST???
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-1].ctype), NULL, true);
          //printf("glob def with export and assignment (= expr)\n");
        }
#line 1723 "y.tab.c"
    break;

  case 16: /* globdef: type assign  */
#line 237 "parser.y"
        {
          //TODO: how do I get the expr and ID in the AST???
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-1].ctype), NULL, false);
          //printf("glob def type and assign\n");
        }
#line 1733 "y.tab.c"
    break;

  case 17: /* globdef: EXPORT type ID SEMICOLON  */
#line 243 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), true);
          //printf("glob def with export\n");
        }
#line 1742 "y.tab.c"
    break;

  case 18: /* globdef: type ID SEMICOLON  */
#line 248 "parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), false);
          //printf("glob def without export\n");
        }
#line 1751 "y.tab.c"
    break;

  case 19: /* params: param COMMA params  */
#line 257 "parser.y"
        {
            //printf("param with params\n");
        }
#line 1759 "y.tab.c"
    break;

  case 20: /* params: param  */
#line 261 "parser.y"
        {
          //TODO: is this correct???
          (yyval.node) = (yyvsp[0].node);
            //printf("param\n");
        }
#line 1769 "y.tab.c"
    break;

  case 21: /* param: type ID  */
#line 270 "parser.y"
      {
        //TODO: is this correct
        (yyval.node) = ASTparam(NULL, (yyvsp[0].id), (yyvsp[-1].ctype));
          //printf("fun body with 0 or infinite vardecls and statements\n");
      }
#line 1779 "y.tab.c"
    break;

  case 22: /* funbody: vardecls stmts  */
#line 279 "parser.y"
        {
          // TODO: how do I get the VarDecls and Stmts in the ASTfunbody????
          (yyval.node) = ASTfunbody(NULL, NULL);
          //printf("fun body with 1 or infinite vardecls and statements\n");
        }
#line 1789 "y.tab.c"
    break;

  case 23: /* funbody: vardecls  */
#line 285 "parser.y"
        {
          // TODO
          (yyval.node) = ASTfunbody(NULL, NULL);
          //printf("fun body with only 1 or infinite vardecls\n");
        }
#line 1799 "y.tab.c"
    break;

  case 24: /* funbody: stmts  */
#line 291 "parser.y"
        {
          // TODO
          (yyval.node) = ASTfunbody(NULL, NULL);
          //printf("fun body with only 1 or infinite statements\n");
        }
#line 1809 "y.tab.c"
    break;

  case 25: /* funbody: %empty  */
#line 297 "parser.y"
        {
          //TODO: is this correct for an empty functionbody???
          (yyval.node) = NULL;
          //printf("empty fun body\n");
        }
#line 1819 "y.tab.c"
    break;

  case 26: /* vardecl: type ID SEMICOLON  */
#line 306 "parser.y"
        {
          // dims expr is NULL, initial expr is NULL, next is NULL, name is ID, type is type
          (yyval.node) = ASTvardecl(NULL, NULL, NULL, (yyvsp[-1].id), (yyvsp[-2].ctype));
          //printf("var decl\n");
        }
#line 1829 "y.tab.c"
    break;

  case 27: /* vardecl: type assign  */
#line 312 "parser.y"
        {
          //TODO: how do I get the assign expr in the ASTvardecl node????
          // $$ = ASTvardecl(NULL, NULL, NULL, $2, $1);
          //printf("var decl with assign\n");
        }
#line 1839 "y.tab.c"
    break;

  case 28: /* vardecls: vardecl vardecls  */
#line 320 "parser.y"
         {
           // TODO: how to make this vardecls???

           // Probably no action here because the action to the ast is handled in vardecl and VarDecls is not a node!
           //printf("vardecls empty\n");
         }
#line 1850 "y.tab.c"
    break;

  case 29: /* vardecls: vardecl  */
#line 327 "parser.y"
         {
          // TODO: is this correct??
          (yyval.node) = (yyvsp[0].node);
           //printf("one vardecl from vardecls\n");
         }
#line 1860 "y.tab.c"
    break;

  case 30: /* stmts: stmt stmts  */
#line 336 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1868 "y.tab.c"
    break;

  case 31: /* stmts: stmt  */
#line 340 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
        }
#line 1876 "y.tab.c"
    break;

  case 32: /* stmt: assign  */
#line 348 "parser.y"
      {
         (yyval.node) = (yyvsp[0].node);
      }
#line 1884 "y.tab.c"
    break;

  case 33: /* stmt: ID BRACKET_L args BRACKET_R  */
#line 352 "parser.y"
      {
        //printf("ID expr with args for statement grammar \n");
      }
#line 1892 "y.tab.c"
    break;

  case 34: /* stmt: ifelse  */
#line 356 "parser.y"
      {
        //TODO: is this correct???
        (yyval.node) = (yyvsp[0].node);
        //printf("ifelse in statement found \n");
      }
#line 1902 "y.tab.c"
    break;

  case 35: /* stmt: while  */
#line 362 "parser.y"
      {
        //TODO: is this correct???
        (yyval.node) = (yyvsp[0].node);
        //printf("while in statement found \n");
      }
#line 1912 "y.tab.c"
    break;

  case 36: /* stmt: dowhile  */
#line 368 "parser.y"
      {
        //TODO: is this correct???
        (yyval.node) = (yyvsp[0].node);
        //printf("do while in statement found \n");
      }
#line 1922 "y.tab.c"
    break;

  case 37: /* stmt: for  */
#line 374 "parser.y"
      {
        //TODO: is this correct???
        (yyval.node) = (yyvsp[0].node);
        //printf("for in statement found \n");
      }
#line 1932 "y.tab.c"
    break;

  case 38: /* stmt: return  */
#line 381 "parser.y"
      {
        //TODO: is this correct???
        (yyval.node) = (yyvsp[0].node);
        //printf("return in statement found \n");
      }
#line 1942 "y.tab.c"
    break;

  case 39: /* stmt: funcall SEMICOLON  */
#line 387 "parser.y"
      {
        //TODO: how to add this one to the AST???
        //Maybe access it with: 
        // node_st *n = ASTfuncall(); VARDECL_NEXT(n) = next; VARDECL_DIMS(n) = NULL;

        // Funcall belongs in expr and stmt, in stmt it has a SEMICOLON
        //printf("expr function call\n");
      }
#line 1955 "y.tab.c"
    break;

  case 40: /* ifelse: IF BRACKET_L expr BRACKET_R block  */
#line 399 "parser.y"
        {
          //TODO: how to get the Stmts: then and else_block in????
          (yyval.node) = ASTifelse((yyvsp[-2].node), NULL, NULL);
          //printf("IF without else block \n");
        }
#line 1965 "y.tab.c"
    break;

  case 41: /* ifelse: IF BRACKET_L expr BRACKET_R block ELSE block  */
#line 405 "parser.y"
        {
          //TODO: how to get the Stmts: then and else_block in????
          (yyval.node) = ASTifelse((yyvsp[-4].node), NULL, NULL);
          //printf("IF including else block \n");
        }
#line 1975 "y.tab.c"
    break;

  case 42: /* while: WHILE BRACKET_L expr BRACKET_R block  */
#line 413 "parser.y"
       {
        //TODO: how to get the Stmts: block in????
        (yyval.node) = ASTwhile((yyvsp[-2].node), NULL);
        //printf("WHILE statement \n");
      }
#line 1985 "y.tab.c"
    break;

  case 43: /* dowhile: DO block WHILE BRACKET_L expr BRACKET_R SEMICOLON  */
#line 421 "parser.y"
               {
                //TODO: how to get the Stmts: block in????
                (yyval.node) = ASTdowhile((yyvsp[-2].node), NULL);
                //printf("DO-WHILE statement \n");
               }
#line 1995 "y.tab.c"
    break;

  case 44: /* for: FOR BRACKET_L INTTYPE varlet LET expr COMMA expr COMMA expr BRACKET_R block  */
#line 429 "parser.y"
     {
      //TODO: how to get the Stmts: block in????
      (yyval.node) = ASTfor((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), NULL);
      //printf("FOR statement with second expr \n");
     }
#line 2005 "y.tab.c"
    break;

  case 45: /* for: FOR BRACKET_L INTTYPE varlet LET expr COMMA expr BRACKET_R block  */
#line 435 "parser.y"
     {
      //TODO: how to get the Stmts: block in???? And how to code standard step +1, can it just be +1???
      (yyval.node) = ASTfor((yyvsp[-4].node), (yyvsp[-2].node), NULL, NULL);
      //printf("FOR statement without second expr \n");
     }
#line 2015 "y.tab.c"
    break;

  case 46: /* return: RETURN SEMICOLON  */
#line 443 "parser.y"
        {
          (yyval.node) = ASTreturn(NULL);
          //printf("RETURN statement without expr \n");
        }
#line 2024 "y.tab.c"
    break;

  case 47: /* return: RETURN expr SEMICOLON  */
#line 448 "parser.y"
        {
          (yyval.node) = ASTreturn((yyvsp[-1].node));
          //printf("RETURN statement including expr \n");
        }
#line 2033 "y.tab.c"
    break;

  case 48: /* block: CURLYBRACE_L stmts CURLYBRACE_R  */
#line 456 "parser.y"
      {
        //TODO: what to do here???

        //printf("block with curly braces \n");
      }
#line 2043 "y.tab.c"
    break;

  case 49: /* block: stmt  */
#line 462 "parser.y"
      {
        //TODO: what to do here???

        //printf("stmt block without curly braces \n");
      }
#line 2053 "y.tab.c"
    break;

  case 50: /* funcall: ID BRACKET_L BRACKET_R  */
#line 472 "parser.y"
        {
          // No arguments
          (yyval.node) = ASTfuncall(NULL, (yyvsp[-2].id));
          //printf("fun call without args with semicolon\n");
        }
#line 2063 "y.tab.c"
    break;

  case 51: /* funcall: ID BRACKET_L args BRACKET_R  */
#line 478 "parser.y"
        {
          // TODO: how to get args in???
          (yyval.node) = ASTfuncall(NULL, (yyvsp[-3].id));
          //printf("fun call with args with semicolon\n");
        }
#line 2073 "y.tab.c"
    break;

  case 52: /* expr: BRACKET_L expr BRACKET_R  */
#line 487 "parser.y"
      {
        //printf("expr with brackets \n");
      }
#line 2081 "y.tab.c"
    break;

  case 53: /* expr: expr PLUS expr  */
#line 491 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_add);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2091 "y.tab.c"
    break;

  case 54: /* expr: expr MINUS expr  */
#line 497 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_sub);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2101 "y.tab.c"
    break;

  case 55: /* expr: expr SLASH expr  */
#line 503 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_div);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2111 "y.tab.c"
    break;

  case 56: /* expr: expr STAR expr  */
#line 509 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mul);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2121 "y.tab.c"
    break;

  case 57: /* expr: expr PERCENT expr  */
#line 515 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mod);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2131 "y.tab.c"
    break;

  case 58: /* expr: expr LE expr  */
#line 521 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_le);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2141 "y.tab.c"
    break;

  case 59: /* expr: expr LT expr  */
#line 527 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_lt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2151 "y.tab.c"
    break;

  case 60: /* expr: expr GE expr  */
#line 533 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ge);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2161 "y.tab.c"
    break;

  case 61: /* expr: expr GT expr  */
#line 539 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_gt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2171 "y.tab.c"
    break;

  case 62: /* expr: expr EQ expr  */
#line 545 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_eq);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2181 "y.tab.c"
    break;

  case 63: /* expr: expr OR expr  */
#line 551 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_or);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2191 "y.tab.c"
    break;

  case 64: /* expr: expr AND expr  */
#line 557 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_and);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2201 "y.tab.c"
    break;

  case 65: /* expr: expr NE expr  */
#line 563 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ne);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        //printf("expr binop expr including brackets \n");
      }
#line 2211 "y.tab.c"
    break;

  case 66: /* expr: MINUS expr  */
#line 569 "parser.y"
      {
        // This MINUS uses the MONOP_MINUS precedence rule
        // arithmetic negation, used for arithmetic values (=numbers, etc)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_neg);
        // AddLocToNode($$, &@2);
        //printf("monop expr including brackets \n");
      }
#line 2223 "y.tab.c"
    break;

  case 67: /* expr: EXCLAMATION expr  */
#line 577 "parser.y"
      {
        // logical negation, used for boolean values (true, false)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_not);
        // AddLocToNode($$, &@2);
        //printf("expr monop expr including brackets \n");
      }
#line 2234 "y.tab.c"
    break;

  case 68: /* expr: BRACKET_L type BRACKET_R expr  */
#line 584 "parser.y"
      {
        // Type cast
        (yyval.node) = ASTcast((yyvsp[0].node), (yyvsp[-2].ctype));
        //printf("expr with basic type \n");
      }
#line 2244 "y.tab.c"
    break;

  case 69: /* expr: funcall  */
#line 590 "parser.y"
      {
        // Funcall belongs in expr and stmt, in expr it does not have a SEMICOLON
        // //printf("expr function call\n");
      }
#line 2253 "y.tab.c"
    break;

  case 70: /* expr: ID  */
#line 595 "parser.y"
      {
        (yyval.node) = ASTvar((yyvsp[0].id));
        //printf("ID expr \n");
      }
#line 2262 "y.tab.c"
    break;

  case 71: /* expr: constant  */
#line 600 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
        //printf("constant expr\n");
      }
#line 2271 "y.tab.c"
    break;

  case 72: /* args: expr  */
#line 608 "parser.y"
      {
        //TODO: how to make expr here????
        
        // //printf("assign without cast\n");
      }
#line 2281 "y.tab.c"
    break;

  case 73: /* args: args COMMA expr  */
#line 614 "parser.y"
      {
        //TODO: What to do here????
        
        // //printf("assign without cast\n");
      }
#line 2291 "y.tab.c"
    break;

  case 74: /* assign: varlet LET expr SEMICOLON  */
#line 622 "parser.y"
        {
          (yyval.node) = ASTassign((yyvsp[-3].node), (yyvsp[-1].node));
          // //printf("assign without cast\n");
        }
#line 2300 "y.tab.c"
    break;

  case 75: /* type: BOOLTYPE  */
#line 631 "parser.y"
                { (yyval.ctype) = CT_bool; }
#line 2306 "y.tab.c"
    break;

  case 76: /* type: FLOATTYPE  */
#line 632 "parser.y"
                { (yyval.ctype) = CT_float; }
#line 2312 "y.tab.c"
    break;

  case 77: /* type: INTTYPE  */
#line 633 "parser.y"
                { (yyval.ctype) = CT_int; }
#line 2318 "y.tab.c"
    break;

  case 78: /* type: VOIDTYPE  */
#line 634 "parser.y"
                { (yyval.ctype) = CT_void; }
#line 2324 "y.tab.c"
    break;

  case 79: /* varlet: ID  */
#line 639 "parser.y"
        {
          (yyval.node) = ASTvarlet((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2333 "y.tab.c"
    break;

  case 80: /* constant: floatval  */
#line 654 "parser.y"
          {
            // Assign the value of the floatval grammar rule AST creation to this constant node type
            (yyval.node) = (yyvsp[0].node);
          }
#line 2342 "y.tab.c"
    break;

  case 81: /* constant: intval  */
#line 659 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2350 "y.tab.c"
    break;

  case 82: /* constant: boolval  */
#line 663 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2358 "y.tab.c"
    break;

  case 83: /* floatval: FLOAT  */
#line 669 "parser.y"
           {
             (yyval.node) = ASTfloat((yyvsp[0].cflt));
           }
#line 2366 "y.tab.c"
    break;

  case 84: /* intval: NUM  */
#line 675 "parser.y"
        {
          (yyval.node) = ASTnum((yyvsp[0].cint));
        }
#line 2374 "y.tab.c"
    break;

  case 85: /* boolval: TRUEVAL  */
#line 681 "parser.y"
         {
           (yyval.node) = ASTbool(true);
         }
#line 2382 "y.tab.c"
    break;

  case 86: /* boolval: FALSEVAL  */
#line 685 "parser.y"
         {
           (yyval.node) = ASTbool(false);
         }
#line 2390 "y.tab.c"
    break;


#line 2394 "y.tab.c"

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

#line 689 "parser.y"


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
    yyparse();
    return parseresult;
}
