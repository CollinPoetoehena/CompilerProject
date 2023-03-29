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
#line 1 "src/scanparse/parser.y"


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

#line 101 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"

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

#include "parser.h"
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
#define YYLAST   545

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  213

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
       0,   121,   121,   127,   132,   139,   143,   147,   154,   159,
     165,   170,   176,   184,   193,   198,   204,   209,   215,   223,
     233,   241,   246,   251,   256,   263,   268,   275,   279,   283,
     288,   293,   299,   304,   309,   316,   320,   326,   330,   334,
     338,   342,   347,   351,   358,   363,   369,   375,   381,   386,
     393,   398,   406,   410,   415,   421,   427,   435,   440,   445,
     450,   455,   460,   465,   470,   475,   480,   485,   490,   495,
     500,   505,   512,   518,   524,   529,   533,   540,   545,   553,
     563,   564,   565,   569,   577,   584,   589,   593,   599,   606,
     613,   618
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

#define YYPACT_NINF (-155)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-84)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     481,  -155,  -155,  -155,   -26,   136,   143,    21,  -155,   481,
    -155,  -155,  -155,    -9,    35,    30,    31,    45,    47,  -155,
    -155,    62,     7,    64,    68,    77,    75,    15,  -155,   236,
      79,    78,    59,    57,   102,  -155,   106,   147,  -155,   236,
      88,   113,   200,   236,   236,  -155,  -155,  -155,  -155,   115,
    -155,   405,  -155,  -155,  -155,  -155,  -155,   117,   114,   120,
     116,   123,   131,   134,   135,   152,   150,   155,   421,   117,
     153,   283,   173,  -155,  -155,   211,  -155,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
       2,   180,   189,    66,   197,   241,   193,   175,  -155,   175,
    -155,  -155,  -155,  -155,  -155,   437,  -155,   170,   179,   117,
     -10,  -155,   210,  -155,   212,   117,   214,   117,   218,  -155,
     209,   117,  -155,   236,  -155,   372,   215,   174,   174,  -155,
    -155,  -155,   242,   242,   242,   242,   502,   502,   513,   526,
     236,   236,   158,  -155,   194,   220,  -155,   453,  -155,  -155,
    -155,  -155,     1,   236,   228,  -155,  -155,  -155,   229,   117,
     230,   117,  -155,   232,  -155,   236,  -155,   301,   319,  -155,
     240,   246,   224,  -155,   -10,   236,   469,  -155,  -155,   249,
    -155,   253,  -155,  -155,    66,    66,  -155,   236,   237,  -155,
     485,  -155,  -155,  -155,   254,  -155,   337,   236,   -10,    66,
     284,   389,  -155,  -155,  -155,   236,   265,    66,   236,  -155,
     355,    66,  -155
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    82,    81,    80,     0,     0,     0,     0,     2,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     1,
       3,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    23,     0,
       0,     0,     0,     0,     0,    90,    91,    89,    88,    84,
      74,     0,    75,    76,    85,    86,    87,    30,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,    71,    72,     0,    22,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,    28,    29,    36,
      38,    39,    40,    41,    42,     0,    37,     0,     0,    30,
       0,    19,     0,    13,     0,    30,     0,    30,     0,    21,
       0,    30,    57,     0,    55,    77,     0,    59,    58,    61,
      60,    62,    63,    64,    65,    66,    67,    70,    68,    69,
       0,     0,     0,    54,     0,     0,    50,     0,    17,    27,
      35,    43,     0,     0,     0,    25,    18,    12,     0,    30,
       0,    30,    11,     0,    73,     0,    56,     0,     0,    53,
       0,     0,     0,    51,    31,     0,     0,    16,    15,     0,
       9,     0,    10,    78,     0,     0,    52,     0,     0,    33,
       0,    79,    14,     8,    44,    46,     0,     0,    32,     0,
       0,     0,    34,    45,    47,     0,     0,     0,     0,    49,
       0,     0,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,   280,  -155,  -155,  -155,  -155,    -5,   -45,  -154,
     -95,   -92,  -155,  -155,  -155,  -155,  -155,   -76,  -155,   -29,
     126,  -155,     3,  -155,  -155,  -155,  -155,  -155,  -155
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
      51,   143,   149,    13,   150,    75,    14,   174,    16,    18,
      68,    30,    13,    71,    73,    74,     1,     2,     3,    40,
     189,    19,    41,    21,   120,    32,   175,   -83,    61,    63,
      32,    65,    67,     1,     2,     3,    32,    32,    22,    32,
      32,     1,     2,     3,   202,    72,   125,   170,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,    60,    23,    24,   154,    27,   147,    33,    28,    42,
     158,    34,   160,   142,    35,    43,   163,    25,    37,    26,
      36,    38,    58,     1,     2,     3,    57,    29,    44,    45,
      46,    59,   143,   143,   164,    69,    47,    48,    90,    91,
      39,    92,    93,    94,    95,   155,    62,   143,   194,   195,
      64,   167,   168,    32,   179,   143,   181,    70,    75,   143,
      42,   109,   111,   203,   176,   110,    43,   112,     1,     2,
       3,   209,     1,     2,     3,   212,   125,   113,   114,    44,
      45,    46,   115,     1,     2,     3,   190,    47,    48,    90,
      91,    66,    92,    93,    94,    95,   116,   117,   196,   118,
     121,    42,     1,     2,     3,    15,   169,    43,   201,     1,
       2,     3,    17,     1,     2,     3,   206,   123,    42,   210,
      44,    45,    46,   140,    43,    79,    80,    81,    47,    48,
      90,    91,   141,    92,    93,    94,    95,    44,    45,    46,
     145,   148,   152,    42,   153,    47,    48,    90,    91,    43,
      92,    93,    94,    95,    42,   124,   156,   162,   157,   166,
      43,   159,    44,    45,    46,   161,     1,     2,     3,   171,
      47,    48,    49,    44,    45,    46,   177,   178,   180,    42,
     182,    47,    48,    49,    42,    43,   172,   146,   186,   187,
      43,    77,    78,    79,    80,    81,   188,   192,    44,    45,
      46,   193,   197,    44,    45,    46,    47,    48,    49,   207,
     208,    47,    48,    49,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   122,   199,    20,
     204,   183,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   184,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   185,     0,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   200,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   211,
       0,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   165,     0,     0,
       0,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,   205,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    76,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,   119,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   151,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,   173,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,   191,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   198,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,     1,     2,     3,
       4,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       5,     6,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,    89,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
      29,    93,    97,     0,    99,     3,    32,     6,     5,     6,
      39,     4,     9,    42,    43,    44,    26,    27,    28,     4,
     174,     0,    27,    32,    69,    22,    25,    25,    33,    34,
      27,    36,    37,    26,    27,    28,    33,    34,     3,    36,
      37,    26,    27,    28,   198,    42,    75,   142,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     4,    32,    32,   109,     3,    95,     3,     6,     3,
     115,     3,   117,     7,     6,     9,   121,    32,     3,    32,
       3,     6,     4,    26,    27,    28,     7,    25,    22,    23,
      24,    32,   184,   185,   123,     7,    30,    31,    32,    33,
      25,    35,    36,    37,    38,   110,     4,   199,   184,   185,
       4,   140,   141,   110,   159,   207,   161,     4,     3,   211,
       3,     7,     6,   199,   153,     5,     9,     4,    26,    27,
      28,   207,    26,    27,    28,   211,   165,     6,     4,    22,
      23,    24,     7,    26,    27,    28,   175,    30,    31,    32,
      33,     4,    35,    36,    37,    38,     4,     7,   187,     4,
       7,     3,    26,    27,    28,    29,     8,     9,   197,    26,
      27,    28,    29,    26,    27,    28,   205,     4,     3,   208,
      22,    23,    24,     3,     9,    11,    12,    13,    30,    31,
      32,    33,     3,    35,    36,    37,    38,    22,    23,    24,
       3,     8,    32,     3,    25,    30,    31,    32,    33,     9,
      35,    36,    37,    38,     3,     4,     6,     8,     6,     4,
       9,     7,    22,    23,    24,     7,    26,    27,    28,    35,
      30,    31,    32,    22,    23,    24,     8,     8,     8,     3,
       8,    30,    31,    32,     3,     9,    26,     6,     8,     3,
       9,     9,    10,    11,    12,    13,    32,     8,    22,    23,
      24,     8,    25,    22,    23,    24,    30,    31,    32,     4,
       5,    30,    31,    32,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     4,    34,     9,
       6,   165,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     4,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     4,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     4,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     4,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     5,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     6,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     6,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     6,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     6,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     6,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     6,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    26,    27,    28,
      29,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      39,    40,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    21,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19
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
      53,     7,     8,    53,    64,     5,     4,    64,    64,     8,
      55,    35,    26,     6,     6,    25,    64,     8,     8,    53,
       8,    53,     8,    65,     4,     4,     8,     3,    32,    54,
      64,     6,     8,     8,    62,    62,    64,    25,     6,    34,
       4,    64,    54,    62,     6,     5,    64,     4,     5,    62,
      64,     4,    62
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      50,    51,    51,    51,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    57,    57,    58,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65,    66,
      67,    67,    67,    68,    69,    70,    70,    70,    71,    72,
      73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     9,     8,
       8,     7,     7,     6,     9,     8,     8,     7,     7,     6,
       4,     6,     5,     4,     3,     4,     2,     2,     1,     1,
       0,     3,     5,     4,     6,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     5,     7,     5,     7,    12,    10,
       2,     3,     3,     2,     1,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
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
#line 122 "src/scanparse/parser.y"
         {
           parseresult = ASTprogram((yyvsp[0].node));
         }
#line 1480 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 3: /* decls: decl decls  */
#line 128 "src/scanparse/parser.y"
        {
          // $$ = means what you return to coconut
          (yyval.node) = ASTdecls((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1489 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 4: /* decls: decl  */
#line 133 "src/scanparse/parser.y"
        {
          // Next is NULL
          (yyval.node) = ASTdecls((yyvsp[0].node), NULL);
        }
#line 1498 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 5: /* decl: fundef  */
#line 140 "src/scanparse/parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1506 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 6: /* decl: globdecl  */
#line 144 "src/scanparse/parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1514 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 7: /* decl: globdef  */
#line 148 "src/scanparse/parser.y"
        {
          (yyval.node) = (yyvsp[0].node);
        }
#line 1522 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 8: /* fundef: EXPORT type ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 155 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-7].ctype), (yyvsp[-6].id), true);
          AddLocToNode((yyval.node), &(yylsp[-8]), &(yylsp[0]));
        }
#line 1531 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 9: /* fundef: EXPORT type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 160 "src/scanparse/parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), true);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 1541 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 10: /* fundef: type ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 166 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-7].ctype), (yyvsp[-6].id), false);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 1550 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 11: /* fundef: type ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 171 "src/scanparse/parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, (yyvsp[-6].ctype), (yyvsp[-5].id), false);
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 1560 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 12: /* fundef: EXTERN type ID BRACKET_L param BRACKET_R SEMICOLON  */
#line 177 "src/scanparse/parser.y"
        {
          // Empty funbody. FunDec always starts with extern and ends with a ;
          node_st *fundefNode = ASTfundef(NULL, (yyvsp[-2].node), (yyvsp[-5].ctype), (yyvsp[-4].id), true);
          FUNDEF_IS_FUNDECL(fundefNode) = true;
          (yyval.node) = fundefNode;
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 1572 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 13: /* fundef: EXTERN type ID BRACKET_L BRACKET_R SEMICOLON  */
#line 185 "src/scanparse/parser.y"
        {
          // Empty param and empty funbody. FunDec always starts with extern and ends with a ;
          node_st *fundefNode = ASTfundef(NULL, NULL, (yyvsp[-4].ctype), (yyvsp[-3].id), true);
          FUNDEF_IS_FUNDECL(fundefNode) = true;
          (yyval.node) = fundefNode;
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1584 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 14: /* fundef: EXPORT VOIDTYPE ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 194 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), CT_void, (yyvsp[-6].id), true);
          AddLocToNode((yyval.node), &(yylsp[-8]), &(yylsp[0]));
        }
#line 1593 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 15: /* fundef: EXPORT VOIDTYPE ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 199 "src/scanparse/parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, CT_void, (yyvsp[-5].id), true);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 1603 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 16: /* fundef: VOIDTYPE ID BRACKET_L param BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 205 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfundef((yyvsp[-1].node), (yyvsp[-4].node), CT_void, (yyvsp[-6].id), false);
          AddLocToNode((yyval.node), &(yylsp[-7]), &(yylsp[0]));
        }
#line 1612 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 17: /* fundef: VOIDTYPE ID BRACKET_L BRACKET_R CURLYBRACE_L funbody CURLYBRACE_R  */
#line 210 "src/scanparse/parser.y"
        {
          // Empty param
          (yyval.node) = ASTfundef((yyvsp[-1].node), NULL, CT_void, (yyvsp[-5].id), false);
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 1622 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 18: /* fundef: EXTERN VOIDTYPE ID BRACKET_L param BRACKET_R SEMICOLON  */
#line 216 "src/scanparse/parser.y"
        {
          // Empty funbody. FunDec always starts with extern and ends with a ;
          node_st *fundefNode = ASTfundef(NULL, (yyvsp[-2].node), CT_void, (yyvsp[-4].id), true);
          FUNDEF_IS_FUNDECL(fundefNode) = true;
          (yyval.node) = fundefNode;
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 1634 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 19: /* fundef: EXTERN VOIDTYPE ID BRACKET_L BRACKET_R SEMICOLON  */
#line 224 "src/scanparse/parser.y"
        {
          // Empty param and empty funbody. FunDec always starts with extern and ends with a ;
          node_st *fundefNode = ASTfundef(NULL, NULL, CT_void, (yyvsp[-3].id), true);
          FUNDEF_IS_FUNDECL(fundefNode) = true;
          (yyval.node) = fundefNode;
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1646 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 20: /* globdecl: EXTERN type ID SEMICOLON  */
#line 234 "src/scanparse/parser.y"
         {
          // ID has the value that the lexer put into it with STRCopy(yytext)
           (yyval.node) = ASTglobdecl((yyvsp[-2].ctype), (yyvsp[-1].id));
           AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
         }
#line 1656 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 21: /* globdef: EXPORT type ID LET expr SEMICOLON  */
#line 242 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), true);
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1665 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 22: /* globdef: type ID LET expr SEMICOLON  */
#line 247 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, (yyvsp[-1].node), (yyvsp[-4].ctype), (yyvsp[-3].id), false);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 1674 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 23: /* globdef: EXPORT type ID SEMICOLON  */
#line 252 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), true);
          AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
        }
#line 1683 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 24: /* globdef: type ID SEMICOLON  */
#line 257 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTglobdef(NULL, NULL, (yyvsp[-2].ctype), (yyvsp[-1].id), false);
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 1692 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 25: /* param: type ID COMMA param  */
#line 264 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTparam(NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
        AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
      }
#line 1701 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 26: /* param: type ID  */
#line 269 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTparam(NULL, NULL, (yyvsp[0].id), (yyvsp[-1].ctype));
        AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
      }
#line 1710 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 27: /* funbody: vardecl stmts  */
#line 276 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfunbody((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1718 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 28: /* funbody: vardecl  */
#line 280 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfunbody((yyvsp[0].node), NULL);
        }
#line 1726 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 29: /* funbody: stmts  */
#line 284 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfunbody(NULL, (yyvsp[0].node));
        }
#line 1734 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 30: /* funbody: %empty  */
#line 288 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfunbody(NULL, NULL);
        }
#line 1742 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 31: /* vardecl: type ID SEMICOLON  */
#line 294 "src/scanparse/parser.y"
        {
          // dims expr is NULL, initial expr is NULL, next is NULL, name is ID, type is type
          (yyval.node) = ASTvardecl(NULL, NULL, NULL, (yyvsp[-1].id), (yyvsp[-2].ctype));
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 1752 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 32: /* vardecl: type ID LET expr SEMICOLON  */
#line 300 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, (yyvsp[-1].node), NULL, (yyvsp[-3].id), (yyvsp[-4].ctype));
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 1761 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 33: /* vardecl: type ID SEMICOLON vardecl  */
#line 305 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, NULL, (yyvsp[0].node), (yyvsp[-2].id), (yyvsp[-3].ctype));
          AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
        }
#line 1770 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 34: /* vardecl: type ID LET expr SEMICOLON vardecl  */
#line 310 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvardecl(NULL, (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-4].id), (yyvsp[-5].ctype));
          AddLocToNode((yyval.node), &(yylsp[-5]), &(yylsp[0]));
        }
#line 1779 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 35: /* stmts: stmt stmts  */
#line 317 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1787 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 36: /* stmts: stmt  */
#line 321 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
        }
#line 1795 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 37: /* stmt: assign  */
#line 327 "src/scanparse/parser.y"
      {
         (yyval.node) = (yyvsp[0].node);
      }
#line 1803 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 38: /* stmt: ifelse  */
#line 331 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1811 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 39: /* stmt: while  */
#line 335 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1819 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 40: /* stmt: dowhile  */
#line 339 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1827 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 41: /* stmt: for  */
#line 343 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1835 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 42: /* stmt: return  */
#line 348 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 1843 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 43: /* stmt: expr SEMICOLON  */
#line 352 "src/scanparse/parser.y"
      {
        // This is an expression in a statement, therefore the name Expr Statement, so does not belong in expr
        (yyval.node) = ASTexprstmt((yyvsp[-1].node));
      }
#line 1852 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 44: /* ifelse: IF BRACKET_L expr BRACKET_R block  */
#line 359 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-2].node), (yyvsp[0].node), NULL);
          AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
        }
#line 1861 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 45: /* ifelse: IF BRACKET_L expr BRACKET_R block ELSE block  */
#line 364 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTifelse((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
          AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
        }
#line 1870 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 46: /* while: WHILE BRACKET_L expr BRACKET_R block  */
#line 370 "src/scanparse/parser.y"
       {
        (yyval.node) = ASTwhile((yyvsp[-2].node), (yyvsp[0].node));
        AddLocToNode((yyval.node), &(yylsp[-4]), &(yylsp[0]));
       }
#line 1879 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 47: /* dowhile: DO block WHILE BRACKET_L expr BRACKET_R SEMICOLON  */
#line 376 "src/scanparse/parser.y"
          {
           (yyval.node) = ASTdowhile((yyvsp[-2].node), (yyvsp[-5].node));
           AddLocToNode((yyval.node), &(yylsp[-6]), &(yylsp[0]));
          }
#line 1888 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 48: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr COMMA expr BRACKET_R block  */
#line 382 "src/scanparse/parser.y"
     {
      (yyval.node) = ASTfor((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-8].id));
      AddLocToNode((yyval.node), &(yylsp[-11]), &(yylsp[0]));
     }
#line 1897 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 49: /* for: FOR BRACKET_L INTTYPE ID LET expr COMMA expr BRACKET_R block  */
#line 387 "src/scanparse/parser.y"
     {
      // No step means NULL, which will be used as + 1, this is coded somewhere else
      (yyval.node) = ASTfor((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), (yyvsp[-6].id));
      AddLocToNode((yyval.node), &(yylsp[-9]), &(yylsp[0]));
     }
#line 1907 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 50: /* return: RETURN SEMICOLON  */
#line 394 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTreturn(NULL);
          AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
        }
#line 1916 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 51: /* return: RETURN expr SEMICOLON  */
#line 399 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTreturn((yyvsp[-1].node));
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 1925 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 52: /* block: CURLYBRACE_L stmts CURLYBRACE_R  */
#line 407 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
      }
#line 1933 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 53: /* block: CURLYBRACE_L CURLYBRACE_R  */
#line 411 "src/scanparse/parser.y"
      {
        // Empty block, return NULL
        (yyval.node) = NULL;
      }
#line 1942 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 54: /* block: stmt  */
#line 416 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
      }
#line 1950 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 55: /* funcall: ID BRACKET_L BRACKET_R  */
#line 422 "src/scanparse/parser.y"
        {
          // No arguments
          (yyval.node) = ASTfuncall(NULL, (yyvsp[-2].id));
          AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        }
#line 1960 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 56: /* funcall: ID BRACKET_L exprs BRACKET_R  */
#line 428 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTfuncall((yyvsp[-1].node), (yyvsp[-3].id));
          AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
        }
#line 1969 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 57: /* expr: BRACKET_L expr BRACKET_R  */
#line 436 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[-1].node);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 1978 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 58: /* expr: expr PLUS expr  */
#line 441 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_add);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 1987 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 59: /* expr: expr MINUS expr  */
#line 446 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_sub);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 1996 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 60: /* expr: expr SLASH expr  */
#line 451 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_div);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2005 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 61: /* expr: expr STAR expr  */
#line 456 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_mul);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2014 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 62: /* expr: expr PERCENT expr  */
#line 461 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_mod);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2023 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 63: /* expr: expr LE expr  */
#line 466 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_le);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2032 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 64: /* expr: expr LT expr  */
#line 471 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_lt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2041 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 65: /* expr: expr GE expr  */
#line 476 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_ge);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2050 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 66: /* expr: expr GT expr  */
#line 481 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_gt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2059 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 67: /* expr: expr EQ expr  */
#line 486 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_eq);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2068 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 68: /* expr: expr OR expr  */
#line 491 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_or);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2077 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 69: /* expr: expr AND expr  */
#line 496 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_and);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2086 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 70: /* expr: expr NE expr  */
#line 501 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTbinop((yyvsp[-2].node), (yyvsp[0].node), BO_ne);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2095 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 71: /* expr: MINUS expr  */
#line 506 "src/scanparse/parser.y"
      {
        // This MINUS uses the MONOP_MINUS precedence rule
        // unary minus, arithmetic negation, used for arithmetic values (=numbers, etc)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_neg);
        AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
      }
#line 2106 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 72: /* expr: EXCLAMATION expr  */
#line 513 "src/scanparse/parser.y"
      {
        // logical negation, used for boolean values (true, false)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_not);
        AddLocToNode((yyval.node), &(yylsp[-1]), &(yylsp[0]));
      }
#line 2116 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 73: /* expr: BRACKET_L type BRACKET_R expr  */
#line 519 "src/scanparse/parser.y"
      {
        // Type cast (can be int, float and bool)
        (yyval.node) = ASTcast((yyvsp[0].node), (yyvsp[-2].ctype));
        AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
      }
#line 2126 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 74: /* expr: funcall  */
#line 525 "src/scanparse/parser.y"
      {
        // Funcall only belongs in expr rule, then the funcall can be expr SEMICOLON in stmt rule
        (yyval.node) = (yyvsp[0].node);
      }
#line 2135 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 75: /* expr: var  */
#line 530 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2143 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 76: /* expr: constant  */
#line 534 "src/scanparse/parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
      }
#line 2151 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 77: /* exprs: expr  */
#line 541 "src/scanparse/parser.y"
      {
        (yyval.node) = ASTexprs((yyvsp[0].node), NULL);
        AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
      }
#line 2160 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 78: /* exprs: expr COMMA exprs  */
#line 546 "src/scanparse/parser.y"
      {
        // First expr then exprs to avoid reversing the order of exprs!
        (yyval.node) = ASTexprs((yyvsp[-2].node), (yyvsp[0].node));
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
      }
#line 2170 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 79: /* assign: varlet LET expr SEMICOLON  */
#line 554 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTassign((yyvsp[-3].node), (yyvsp[-1].node));
          AddLocToNode((yyval.node), &(yylsp[-3]), &(yylsp[0]));
        }
#line 2179 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 80: /* type: BOOLTYPE  */
#line 563 "src/scanparse/parser.y"
                { (yyval.ctype) = CT_bool; }
#line 2185 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 81: /* type: FLOATTYPE  */
#line 564 "src/scanparse/parser.y"
                { (yyval.ctype) = CT_float; }
#line 2191 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 82: /* type: INTTYPE  */
#line 565 "src/scanparse/parser.y"
                { (yyval.ctype) = CT_int; }
#line 2197 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 83: /* varlet: ID  */
#line 570 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvarlet((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2206 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 84: /* var: ID  */
#line 578 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTvar((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2215 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 85: /* constant: floatval  */
#line 585 "src/scanparse/parser.y"
          {
            // Assign the value of the floatval grammar rule AST creation to this constant node type
            (yyval.node) = (yyvsp[0].node);
          }
#line 2224 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 86: /* constant: intval  */
#line 590 "src/scanparse/parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2232 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 87: /* constant: boolval  */
#line 594 "src/scanparse/parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2240 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 88: /* floatval: FLOAT  */
#line 600 "src/scanparse/parser.y"
           {
             (yyval.node) = ASTfloat((yyvsp[0].cflt));
             AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
           }
#line 2249 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 89: /* intval: NUM  */
#line 607 "src/scanparse/parser.y"
        {
          (yyval.node) = ASTnum((yyvsp[0].cint));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2258 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 90: /* boolval: TRUEVAL  */
#line 614 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTbool(true);
           AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
         }
#line 2267 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;

  case 91: /* boolval: FALSEVAL  */
#line 619 "src/scanparse/parser.y"
         {
           (yyval.node) = ASTbool(false);
           AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
         }
#line 2276 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"
    break;


#line 2280 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.c"

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

#line 624 "src/scanparse/parser.y"


/* 
Add location tracking information to a node in the parse tree.
Cannot easily cause an error in the code because it just changes the standard
locations of the node. When a node is created it gets the standard locations 0.
So, by adding a location to the error message, almost nothing can go wrong for adding
that to the compiler because if something is not correctly added the location will be 0.
*/
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
