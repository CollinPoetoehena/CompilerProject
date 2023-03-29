/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_POETOEC_COMPILERCONSTRUCTION_COMPILERPROJECT_COMPILERPROJECT_BUILD_DEBUG_PARSER_H_INCLUDED
# define YY_YY_HOME_POETOEC_COMPILERCONSTRUCTION_COMPILERPROJECT_COMPILERPROJECT_BUILD_DEBUG_PARSER_H_INCLUDED
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "src/scanparse/parser.y"

 char               *id;
 int                 cint;
 float               cflt;
 enum Type           ctype;
 node_st             *node;

#line 116 "/home/poetoec/CompilerConstruction/CompilerProject/CompilerProject/build-debug/parser.h"

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


#endif /* !YY_YY_HOME_POETOEC_COMPILERCONSTRUCTION_COMPILERPROJECT_COMPILERPROJECT_BUILD_DEBUG_PARSER_H_INCLUDED  */
