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
  YYSYMBOL_funheader = 49,                 /* funheader  */
  YYSYMBOL_globdecl = 50,                  /* globdecl  */
  YYSYMBOL_globdef = 51,                   /* globdef  */
  YYSYMBOL_params = 52,                    /* params  */
  YYSYMBOL_param = 53,                     /* param  */
  YYSYMBOL_funbody = 54,                   /* funbody  */
  YYSYMBOL_vardecl = 55,                   /* vardecl  */
  YYSYMBOL_vardecls = 56,                  /* vardecls  */
  YYSYMBOL_stmts = 57,                     /* stmts  */
  YYSYMBOL_stmt = 58,                      /* stmt  */
  YYSYMBOL_ifelse = 59,                    /* ifelse  */
  YYSYMBOL_while = 60,                     /* while  */
  YYSYMBOL_dowhile = 61,                   /* dowhile  */
  YYSYMBOL_for = 62,                       /* for  */
  YYSYMBOL_return = 63,                    /* return  */
  YYSYMBOL_block = 64,                     /* block  */
  YYSYMBOL_funcall = 65,                   /* funcall  */
  YYSYMBOL_expr = 66,                      /* expr  */
  YYSYMBOL_args = 67,                      /* args  */
  YYSYMBOL_assign = 68,                    /* assign  */
  YYSYMBOL_type = 69,                      /* type  */
  YYSYMBOL_varlet = 70,                    /* varlet  */
  YYSYMBOL_constant = 71,                  /* constant  */
  YYSYMBOL_floatval = 72,                  /* floatval  */
  YYSYMBOL_intval = 73,                    /* intval  */
  YYSYMBOL_boolval = 74                    /* boolval  */
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
#define YYLAST   406

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

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
       0,   117,   117,   123,   127,   134,   138,   142,   149,   153,
     157,   166,   170,   177,   188,   192,   198,   204,   214,   218,
     225,   232,   236,   240,   245,   252,   258,   265,   270,   277,
     281,   289,   293,   297,   301,   305,   309,   314,   318,   325,
     329,   335,   341,   347,   351,   357,   361,   368,   372,   380,
     384,   391,   395,   401,   407,   413,   419,   425,   431,   437,
     443,   449,   455,   461,   467,   473,   481,   488,   494,   499,
     504,   512,   513,   516,   526,   527,   528,   529,   533,   548,
     552,   556,   562,   568,   574,   578
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
  "decl", "fundef", "funheader", "globdecl", "globdef", "params", "param",
  "funbody", "vardecl", "vardecls", "stmts", "stmt", "ifelse", "while",
  "dowhile", "for", "return", "block", "funcall", "expr", "args", "assign",
  "type", "varlet", "constant", "floatval", "intval", "boolval", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     316,  -111,  -111,  -111,  -111,    20,    20,     2,  -111,   316,
    -111,     8,  -111,  -111,    10,  -111,    24,    33,    27,  -111,
    -111,   357,     1,  -111,    58,    23,   357,    35,  -111,    62,
      81,    87,    25,    89,   124,    86,    20,    63,  -111,    63,
    -111,  -111,  -111,  -111,  -111,   101,  -111,    83,    40,  -111,
     157,  -111,   108,  -111,   141,   157,   157,    63,  -111,    84,
      92,    82,  -111,   157,   157,  -111,  -111,  -111,  -111,   117,
    -111,   304,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,   116,  -111,  -111,   119,   121,    97,   320,  -111,  -111,
     348,    16,   199,   217,   123,   137,   109,   235,   120,  -111,
    -111,   141,  -111,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,  -111,  -111,    20,  -111,
    -111,   136,   157,    25,    25,  -111,   157,  -111,   126,  -111,
     157,    29,    75,    75,  -111,  -111,  -111,   125,   125,   125,
     125,   337,   337,   361,   387,  -111,   348,   115,  -111,   253,
     157,  -111,  -111,    25,   146,   288,  -111,  -111,   157,   181,
      25,   157,  -111,   271,    25,  -111
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    76,    75,    74,    77,     0,     0,     0,     2,     4,
       5,     0,     6,     7,     0,    10,     0,     0,     0,     1,
       3,    24,    78,    15,     0,     0,    24,    78,    14,    78,
       0,     0,     0,     0,     0,     0,    28,    22,    23,    30,
      33,    34,    35,    36,    37,     0,    31,     0,     0,    17,
       0,    13,     0,    16,     0,     0,     0,     0,    48,     0,
       0,     0,    45,     0,     0,    84,    85,    83,    82,    69,
      68,     0,    70,    79,    80,    81,     9,    27,    21,    29,
      38,    78,    26,    12,     0,    19,     0,     0,     8,    49,
      71,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    25,    11,     0,    20,
      73,    32,     0,     0,     0,    47,     0,    78,     0,    51,
       0,     0,    53,    52,    55,    54,    56,    57,    58,    59,
      60,    61,    64,    62,    63,    18,    72,    39,    41,     0,
       0,    67,    50,     0,     0,     0,    40,    42,     0,     0,
       0,     0,    44,     0,     0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,   144,  -111,  -111,    47,  -111,  -111,    39,  -111,
     132,  -111,   131,   -12,    -2,  -111,  -111,  -111,  -111,  -111,
    -110,   -21,   -33,    60,    -8,     3,    66,  -111,  -111,  -111,
    -111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    13,    84,    85,
      35,    36,    37,    38,    58,    40,    41,    42,    43,    44,
      59,    70,    90,    91,    46,    47,    24,    72,    73,    74,
      75
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    71,    19,    14,    48,    45,    23,    49,    16,    18,
      28,    45,    14,   147,   148,    21,    45,    87,    45,    39,
     121,   122,    92,    93,    39,    78,    48,    79,    97,    51,
      99,   100,    57,   152,   122,    39,    45,    39,    48,    82,
      26,    53,    22,   156,    83,    94,     1,     2,     3,     4,
     162,    86,    15,    17,   165,    39,    25,    29,    30,    27,
      31,    32,    33,    34,    98,    54,     1,     2,     3,     4,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,    50,    55,    61,   105,   106,   107,   146,
      56,    63,    60,   149,    76,    29,    30,   151,    31,    32,
      33,    34,    45,    45,    64,    65,    66,    80,     1,     2,
       3,     4,    67,    68,    69,    81,    88,   155,    96,    95,
     101,    86,   116,   117,   130,   159,   118,    61,   163,   119,
      62,   125,    45,    63,   103,   104,   105,   106,   107,    45,
     126,   127,   -50,    45,    61,    89,    64,    65,    66,   153,
      63,   150,   157,    20,    67,    68,    69,   145,    52,     0,
      61,   131,   128,    64,    65,    66,    63,    77,     0,     0,
       0,    67,    68,    69,     0,     0,     0,     0,     0,    64,
      65,    66,     0,     0,     0,   160,   161,    67,    68,    69,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   123,     0,     0,     0,     0,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   124,     0,     0,     0,     0,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   129,
       0,     0,     0,     0,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   154,     0,     0,
       0,     0,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   164,     0,     0,     0,     0,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   158,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     102,     0,     0,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   120,     0,     0,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     1,     2,     3,     4,   103,   104,   105,   106,
     107,   108,   109,   110,   111,     5,     6,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     0,   115,     1,     2,     3,     4,     0,     0,    29,
      30,     0,    31,    32,    33,    34,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113
};

static const yytype_int16 yycheck[] =
{
      21,    34,     0,     0,     3,    26,    14,     6,     5,     6,
      18,    32,     9,   123,   124,     7,    37,    50,    39,    21,
       4,     5,    55,    56,    26,    37,     3,    39,    61,     6,
      63,    64,     7,     4,     5,    37,    57,    39,     3,    47,
       7,     6,    32,   153,     4,    57,    26,    27,    28,    29,
     160,    48,     5,     6,   164,    57,    32,    32,    33,    32,
      35,    36,    37,    38,    61,     3,    26,    27,    28,    29,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    25,     3,     3,    11,    12,    13,   122,
       3,     9,     3,   126,     8,    32,    33,   130,    35,    36,
      37,    38,   123,   124,    22,    23,    24,     6,    26,    27,
      28,    29,    30,    31,    32,    32,     8,   150,    26,    35,
       3,   118,     6,     4,     4,   158,     5,     3,   161,    32,
       6,     8,   153,     9,     9,    10,    11,    12,    13,   160,
       3,    32,     6,   164,     3,     4,    22,    23,    24,    34,
       9,    25,     6,     9,    30,    31,    32,   118,    26,    -1,
       3,   101,    96,    22,    23,    24,     9,    36,    -1,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    -1,    -1,    -1,     4,     5,    30,    31,    32,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     4,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     4,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     4,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     4,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     4,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     5,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       6,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     6,    -1,    -1,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    26,    27,    28,    29,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    39,    40,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    21,    26,    27,    28,    29,    -1,    -1,    32,
      33,    -1,    35,    36,    37,    38,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    29,    39,    40,    45,    46,    47,
      48,    49,    50,    51,    69,    49,    69,    49,    69,     0,
      46,     7,    32,    68,    70,    32,     7,    32,    68,    32,
      33,    35,    36,    37,    38,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    65,    68,    69,     3,     6,
      25,     6,    54,     6,     3,     3,     3,     7,    58,    64,
       3,     3,     6,     9,    22,    23,    24,    30,    31,    32,
      65,    66,    71,    72,    73,    74,     8,    56,    57,    57,
       6,    32,    68,     4,    52,    53,    69,    66,     8,     4,
      66,    67,    66,    66,    57,    35,    26,    66,    69,    66,
      66,     3,     6,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,     6,     4,     5,    32,
       6,     4,     5,     4,     4,     8,     3,    32,    70,     4,
       4,    67,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    52,    66,    64,    64,    66,
      25,    66,     4,    34,     4,    66,    64,     6,     5,    66,
       4,     5,    64,    66,     4,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      48,    49,    49,    50,    51,    51,    51,    51,    52,    52,
      53,    54,    54,    54,    54,    55,    55,    56,    56,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    60,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    69,    69,    69,    69,    70,    71,
      71,    71,    72,    73,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     5,     4,
       2,     5,     4,     4,     3,     2,     4,     3,     3,     1,
       2,     2,     1,     1,     0,     3,     2,     2,     1,     2,
       1,     1,     4,     1,     1,     1,     1,     1,     2,     5,
       7,     5,     7,    12,    10,     2,     3,     3,     1,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     1,     1,
       1,     1,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
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
#line 118 "parser.y"
         {
          //  parseresult = ASTprogram($1);
         }
#line 1585 "y.tab.c"
    break;

  case 3: /* decls: decl decls  */
#line 124 "parser.y"
        {
          //printf("decl and decls\n");
        }
#line 1593 "y.tab.c"
    break;

  case 4: /* decls: decl  */
#line 128 "parser.y"
        {
          //printf("one decl\n");
        }
#line 1601 "y.tab.c"
    break;

  case 5: /* decl: fundef  */
#line 135 "parser.y"
        {
          //printf("fundef decl\n");
        }
#line 1609 "y.tab.c"
    break;

  case 6: /* decl: globdecl  */
#line 139 "parser.y"
        {
          //printf("globdecl decl\n");
        }
#line 1617 "y.tab.c"
    break;

  case 7: /* decl: globdef  */
#line 143 "parser.y"
        {
          //printf("globdef decl\n");
        }
#line 1625 "y.tab.c"
    break;

  case 8: /* fundef: EXPORT funheader CURLYBRACE_L funbody CURLYBRACE_R  */
#line 150 "parser.y"
        {
          //printf("fun def with export\n");
        }
#line 1633 "y.tab.c"
    break;

  case 9: /* fundef: funheader CURLYBRACE_L funbody CURLYBRACE_R  */
#line 154 "parser.y"
        {
          //printf("fun def without export\n");
        }
#line 1641 "y.tab.c"
    break;

  case 10: /* fundef: EXTERN funheader  */
#line 158 "parser.y"
        {
          //printf("fun dec (fundef is also used for a fundec)\n");
        }
#line 1649 "y.tab.c"
    break;

  case 11: /* funheader: type ID BRACKET_L params BRACKET_R  */
#line 167 "parser.y"
        {
          //printf("fun header\n");
        }
#line 1657 "y.tab.c"
    break;

  case 12: /* funheader: type ID BRACKET_L BRACKET_R  */
#line 171 "parser.y"
        {
          //printf("fun header without params\n");
        }
#line 1665 "y.tab.c"
    break;

  case 13: /* globdecl: EXTERN type ID SEMICOLON  */
#line 178 "parser.y"
         {
          // $ refereert naar de positie in je regel
          // $$ = betekent wat die teruggeeft aan coconut
          // in ID zit de waarde die je lexer daarin heeft gezet met STRCopy(yytext)
           (yyval.node) = ASTglobdecl((yyvsp[-2].ctype), (yyvsp[-1].id));
           //printf("global declaration\n");
         }
#line 1677 "y.tab.c"
    break;

  case 14: /* globdef: EXPORT type assign  */
#line 189 "parser.y"
        {
          //printf("glob def with export and assignment (= expr)\n");
        }
#line 1685 "y.tab.c"
    break;

  case 15: /* globdef: type assign  */
#line 193 "parser.y"
        {
          //TODO: how to decide between globdef and vardecl for this part, because == same
          // Can I just do vardecl here??
          //printf("glob def type and assign\n");
        }
#line 1695 "y.tab.c"
    break;

  case 16: /* globdef: EXPORT type ID SEMICOLON  */
#line 199 "parser.y"
        {
          //TODO: how to decide between globdef and vardecl for this part, because == same
          // Can I just do vardecl here??
          //printf("glob def with export\n");
        }
#line 1705 "y.tab.c"
    break;

  case 17: /* globdef: type ID SEMICOLON  */
#line 205 "parser.y"
        {
          //TODO: how to decide between globdef and vardecl for this part, because == same
          // Can I just do vardecl here??
          //printf("glob def without export\n");
        }
#line 1715 "y.tab.c"
    break;

  case 18: /* params: param COMMA params  */
#line 215 "parser.y"
        {
            //printf("param with params\n");
        }
#line 1723 "y.tab.c"
    break;

  case 19: /* params: param  */
#line 219 "parser.y"
        {
            //printf("param\n");
        }
#line 1731 "y.tab.c"
    break;

  case 20: /* param: type ID  */
#line 226 "parser.y"
      {
          //printf("fun body with 0 or infinite vardecls and statements\n");
      }
#line 1739 "y.tab.c"
    break;

  case 21: /* funbody: vardecls stmts  */
#line 233 "parser.y"
        {
          //printf("fun body with 1 or infinite vardecls and statements\n");
        }
#line 1747 "y.tab.c"
    break;

  case 22: /* funbody: vardecls  */
#line 237 "parser.y"
        {
          //printf("fun body with only 1 or infinite vardecls\n");
        }
#line 1755 "y.tab.c"
    break;

  case 23: /* funbody: stmts  */
#line 241 "parser.y"
        {
          //printf("fun body with only 1 or infinite statements\n");
        }
#line 1763 "y.tab.c"
    break;

  case 24: /* funbody: %empty  */
#line 245 "parser.y"
        {
          (yyval.node) = NULL;
          //printf("empty fun body\n");
        }
#line 1772 "y.tab.c"
    break;

  case 25: /* vardecl: type ID SEMICOLON  */
#line 253 "parser.y"
        {
          // dims expr is NULL, initial expr is var, next is NULL, type is type
          // $$ = ASTvardecl(NULL, $2, NULL, $3);
          //printf("var decl\n");
        }
#line 1782 "y.tab.c"
    break;

  case 26: /* vardecl: type assign  */
#line 259 "parser.y"
        {
          // $$ = ASTvardecl(NULL, $2, NULL, $3);
          //printf("var decl with assign\n");
        }
#line 1791 "y.tab.c"
    break;

  case 27: /* vardecls: vardecl vardecls  */
#line 266 "parser.y"
         {
           // Probably no action here because the action to the ast is handled in vardecl and VarDecls is not a node!
           //printf("vardecls empty\n");
         }
#line 1800 "y.tab.c"
    break;

  case 28: /* vardecls: vardecl  */
#line 271 "parser.y"
         {
           //printf("one vardecl from vardecls\n");
         }
#line 1808 "y.tab.c"
    break;

  case 29: /* stmts: stmt stmts  */
#line 278 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[-1].node), (yyvsp[0].node));
        }
#line 1816 "y.tab.c"
    break;

  case 30: /* stmts: stmt  */
#line 282 "parser.y"
        {
          (yyval.node) = ASTstmts((yyvsp[0].node), NULL);
        }
#line 1824 "y.tab.c"
    break;

  case 31: /* stmt: assign  */
#line 290 "parser.y"
      {
         (yyval.node) = (yyvsp[0].node);
      }
#line 1832 "y.tab.c"
    break;

  case 32: /* stmt: ID BRACKET_L args BRACKET_R  */
#line 294 "parser.y"
      {
        //printf("ID expr with args for statement grammar \n");
      }
#line 1840 "y.tab.c"
    break;

  case 33: /* stmt: ifelse  */
#line 298 "parser.y"
      {
        //printf("ifelse in statement found \n");
      }
#line 1848 "y.tab.c"
    break;

  case 34: /* stmt: while  */
#line 302 "parser.y"
      {
        //printf("while in statement found \n");
      }
#line 1856 "y.tab.c"
    break;

  case 35: /* stmt: dowhile  */
#line 306 "parser.y"
      {
        //printf("do while in statement found \n");
      }
#line 1864 "y.tab.c"
    break;

  case 36: /* stmt: for  */
#line 310 "parser.y"
      {
        //printf("for in statement found \n");
      }
#line 1872 "y.tab.c"
    break;

  case 37: /* stmt: return  */
#line 315 "parser.y"
      {
        //printf("return in statement found \n");
      }
#line 1880 "y.tab.c"
    break;

  case 38: /* stmt: funcall SEMICOLON  */
#line 319 "parser.y"
      {
        // Funcall belongs in expr and stmt, in stmt it has a SEMICOLON
        //printf("expr function call\n");
      }
#line 1889 "y.tab.c"
    break;

  case 39: /* ifelse: IF BRACKET_L expr BRACKET_R block  */
#line 326 "parser.y"
        {
          //printf("IF without else block \n");
        }
#line 1897 "y.tab.c"
    break;

  case 40: /* ifelse: IF BRACKET_L expr BRACKET_R block ELSE block  */
#line 330 "parser.y"
        {
          //printf("IF including else block \n");
        }
#line 1905 "y.tab.c"
    break;

  case 41: /* while: WHILE BRACKET_L expr BRACKET_R block  */
#line 336 "parser.y"
               {
                 //printf("WHILE statement \n");
               }
#line 1913 "y.tab.c"
    break;

  case 42: /* dowhile: DO block WHILE BRACKET_L expr BRACKET_R SEMICOLON  */
#line 342 "parser.y"
               {
                 //printf("DO-WHILE statement \n");
               }
#line 1921 "y.tab.c"
    break;

  case 43: /* for: FOR BRACKET_L INTTYPE varlet LET expr COMMA expr COMMA expr BRACKET_R block  */
#line 348 "parser.y"
               {
                 //printf("FOR statement with second expr \n");
               }
#line 1929 "y.tab.c"
    break;

  case 44: /* for: FOR BRACKET_L INTTYPE varlet LET expr COMMA expr BRACKET_R block  */
#line 352 "parser.y"
               {
                 //printf("FOR statement without second expr \n");
               }
#line 1937 "y.tab.c"
    break;

  case 45: /* return: RETURN SEMICOLON  */
#line 358 "parser.y"
        {
          //printf("RETURN statement without expr \n");
        }
#line 1945 "y.tab.c"
    break;

  case 46: /* return: RETURN expr SEMICOLON  */
#line 362 "parser.y"
        {
          //printf("RETURN statement including expr \n");
        }
#line 1953 "y.tab.c"
    break;

  case 47: /* block: CURLYBRACE_L stmts CURLYBRACE_R  */
#line 369 "parser.y"
      {
        //printf("block with curly braces \n");
      }
#line 1961 "y.tab.c"
    break;

  case 48: /* block: stmt  */
#line 373 "parser.y"
      {
        //printf("stmt block without curly braces \n");
      }
#line 1969 "y.tab.c"
    break;

  case 49: /* funcall: ID BRACKET_L BRACKET_R  */
#line 381 "parser.y"
        {
          //printf("fun call without args with semicolon\n");
        }
#line 1977 "y.tab.c"
    break;

  case 50: /* funcall: ID BRACKET_L args BRACKET_R  */
#line 385 "parser.y"
        {
          //printf("fun call with args with semicolon\n");
        }
#line 1985 "y.tab.c"
    break;

  case 51: /* expr: BRACKET_L expr BRACKET_R  */
#line 392 "parser.y"
      {
        //printf("expr with brackets \n");
      }
#line 1993 "y.tab.c"
    break;

  case 52: /* expr: expr PLUS expr  */
#line 396 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_add);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2003 "y.tab.c"
    break;

  case 53: /* expr: expr MINUS expr  */
#line 402 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_sub);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2013 "y.tab.c"
    break;

  case 54: /* expr: expr SLASH expr  */
#line 408 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_div);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2023 "y.tab.c"
    break;

  case 55: /* expr: expr STAR expr  */
#line 414 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mul);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2033 "y.tab.c"
    break;

  case 56: /* expr: expr PERCENT expr  */
#line 420 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_mod);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2043 "y.tab.c"
    break;

  case 57: /* expr: expr LE expr  */
#line 426 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_le);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2053 "y.tab.c"
    break;

  case 58: /* expr: expr LT expr  */
#line 432 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_lt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2063 "y.tab.c"
    break;

  case 59: /* expr: expr GE expr  */
#line 438 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ge);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2073 "y.tab.c"
    break;

  case 60: /* expr: expr GT expr  */
#line 444 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_gt);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2083 "y.tab.c"
    break;

  case 61: /* expr: expr EQ expr  */
#line 450 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_eq);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2093 "y.tab.c"
    break;

  case 62: /* expr: expr OR expr  */
#line 456 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_or);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2103 "y.tab.c"
    break;

  case 63: /* expr: expr AND expr  */
#line 462 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_and);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        // //printf("expr binop expr including brackets \n");
      }
#line 2113 "y.tab.c"
    break;

  case 64: /* expr: expr NE expr  */
#line 468 "parser.y"
      {
        (yyval.node) = ASTbinop( (yyvsp[-2].node), (yyvsp[0].node), BO_ne);
        AddLocToNode((yyval.node), &(yylsp[-2]), &(yylsp[0]));
        //printf("expr binop expr including brackets \n");
      }
#line 2123 "y.tab.c"
    break;

  case 65: /* expr: MINUS expr  */
#line 474 "parser.y"
      {
        // This MINUS uses the MONOP_MINUS precedence rule
        // arithmetic negation, used for arithmetic values (=numbers, etc)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_neg);
        // AddLocToNode($$, &@2);
        //printf("monop expr including brackets \n");
      }
#line 2135 "y.tab.c"
    break;

  case 66: /* expr: EXCLAMATION expr  */
#line 482 "parser.y"
      {
        // logical negation, used for boolean values (true, false)
        (yyval.node) = ASTmonop((yyvsp[0].node), MO_not);
        // AddLocToNode($$, &@2);
        //printf("expr monop expr including brackets \n");
      }
#line 2146 "y.tab.c"
    break;

  case 67: /* expr: BRACKET_L type BRACKET_R expr  */
#line 489 "parser.y"
      {
        // Type cast
        (yyval.node) = ASTcast((yyvsp[0].node), (yyvsp[-2].ctype));
        //printf("expr with basic type \n");
      }
#line 2156 "y.tab.c"
    break;

  case 68: /* expr: funcall  */
#line 495 "parser.y"
      {
        // Funcall belongs in expr and stmt, in expr it does not have a SEMICOLON
        // //printf("expr function call\n");
      }
#line 2165 "y.tab.c"
    break;

  case 69: /* expr: ID  */
#line 500 "parser.y"
      {
        (yyval.node) = ASTvar((yyvsp[0].id));
        //printf("ID expr \n");
      }
#line 2174 "y.tab.c"
    break;

  case 70: /* expr: constant  */
#line 505 "parser.y"
      {
        (yyval.node) = (yyvsp[0].node);
        //printf("constant expr\n");
      }
#line 2183 "y.tab.c"
    break;

  case 73: /* assign: varlet LET expr SEMICOLON  */
#line 517 "parser.y"
        {
          (yyval.node) = ASTassign((yyvsp[-3].node), (yyvsp[-1].node));
          // //printf("assign without cast\n");
        }
#line 2192 "y.tab.c"
    break;

  case 74: /* type: BOOLTYPE  */
#line 526 "parser.y"
                { (yyval.ctype) = CT_bool; }
#line 2198 "y.tab.c"
    break;

  case 75: /* type: FLOATTYPE  */
#line 527 "parser.y"
                { (yyval.ctype) = CT_float; }
#line 2204 "y.tab.c"
    break;

  case 76: /* type: INTTYPE  */
#line 528 "parser.y"
                { (yyval.ctype) = CT_int; }
#line 2210 "y.tab.c"
    break;

  case 77: /* type: VOIDTYPE  */
#line 529 "parser.y"
                { (yyval.ctype) = CT_void; }
#line 2216 "y.tab.c"
    break;

  case 78: /* varlet: ID  */
#line 534 "parser.y"
        {
          (yyval.node) = ASTvarlet((yyvsp[0].id));
          AddLocToNode((yyval.node), &(yylsp[0]), &(yylsp[0]));
        }
#line 2225 "y.tab.c"
    break;

  case 79: /* constant: floatval  */
#line 549 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2233 "y.tab.c"
    break;

  case 80: /* constant: intval  */
#line 553 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2241 "y.tab.c"
    break;

  case 81: /* constant: boolval  */
#line 557 "parser.y"
          {
            (yyval.node) = (yyvsp[0].node);
          }
#line 2249 "y.tab.c"
    break;

  case 82: /* floatval: FLOAT  */
#line 563 "parser.y"
           {
             (yyval.node) = ASTfloat((yyvsp[0].cflt));
           }
#line 2257 "y.tab.c"
    break;

  case 83: /* intval: NUM  */
#line 569 "parser.y"
        {
          (yyval.node) = ASTnum((yyvsp[0].cint));
        }
#line 2265 "y.tab.c"
    break;

  case 84: /* boolval: TRUEVAL  */
#line 575 "parser.y"
         {
           (yyval.node) = ASTbool(true);
         }
#line 2273 "y.tab.c"
    break;

  case 85: /* boolval: FALSEVAL  */
#line 579 "parser.y"
         {
           (yyval.node) = ASTbool(false);
         }
#line 2281 "y.tab.c"
    break;


#line 2285 "y.tab.c"

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

#line 583 "parser.y"


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
