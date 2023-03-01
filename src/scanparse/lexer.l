%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "parser.h"
#include "palm/str.h"
#include "global/globals.h"
#include "palm/ctinfo.h"


#define FILTER(token) \
  global.col += yyleng;  \
  return( token);

#define LINEBUF_SIZE 256
#define YY_NO_UNPUT
#define YY_NO_INPUT

static inline void token_action();

int yycolumn = 1;
#define YY_USER_ACTION token_action();

%}

  /* Declare IN_COMMENT state for multi line comments */ 
%s IN_COMMENT

%p 6000 /* set positions to 6000 */
%e 2000 /* set nodes to 1100 */
%option noyywrap
%option nounput
%option yylineno

  // regular expressions for common lexemes
  // '\' is used to escape a character, in this case the '.'
DIGIT            [0-9]
NONZERO_DIGIT    [1-9]
LETTER           [a-zA-Z]
INTEGER          {DIGIT}+
  // This FLOAT accepts: '123.456', '.456'
FLOAT            ({DIGIT}+\.{DIGIT}*)?

%%
  /* 
  Comments on top because you want to check those first.

  INITIAL and IN_COMMENT are states that you can be in.
  This structure also detects unterminated comments and throws 
  a syntax error if an unterminated comment is found.

  This is tested and working. It can appear that it does not work because
  not all grammar rules are finished yet so an empty program could result in a syntax error.
  */
<INITIAL>{
"/*"              BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"*/"      BEGIN(INITIAL);
[^*\n]+   // eat comment in chunks
"*"       // eat the lone star
\n        yylineno++;
}
"//".*                     { /* consume comment */ }

  /* Keywords */
"if"                       { FILTER( IF); }  
"else"                     { FILTER( ELSE); }       
"while"                    { FILTER( WHILE); }
"do"                       { FILTER( DO); }
"for"                      { FILTER( FOR); }
"return"                   { FILTER( RETURN); }
"extern"                   { FILTER( EXTERN); }
"export"                   { FILTER( EXPORT); }

"("                        { FILTER( BRACKET_L); }
")"                        { FILTER( BRACKET_R); }
"{"                        { FILTER( CURLYBRACE_L); }
"}"                        { FILTER( CURLYBRACE_R); }
","                        { FILTER( COMMA); }
";"                        { FILTER( SEMICOLON); }
  
"-"                        { FILTER( MINUS); }
"+"                        { FILTER( PLUS);  }
"*"                        { FILTER( STAR);  } 
"/"                        { FILTER( SLASH);  } 
"%"                        { FILTER( PERCENT);  } 
 
"<="                       { FILTER( LE);    }
"<"                        { FILTER( LT);    } 
">="                       { FILTER( GE);    }
">"                        { FILTER( GT);    }
"=="                       { FILTER( EQ);    }
"!="                       { FILTER( NE);    }
"&&"                       { FILTER( AND);    }
"||"                       { FILTER( OR);    }

"="                        { FILTER( LET);    }

  /* Negation */
"!"                        { FILTER( EXCLAMATION);    }

"true"                     { FILTER( TRUEVAL); }
"false"                    { FILTER( FALSEVAL); }

  /* civic types */
"int"                      { FILTER( INTTYPE); }
"float"                    { FILTER( FLOATTYPE); }
"bool"                     { FILTER( BOOLTYPE); }
"void"                     { FILTER( VOIDTYPE); }

  /* ID in parser now contains the value that is in yytext (read from input)  */
[A-Za-z][A-Za-z0-9_]*      { yylval.id = STRcpy(yytext);
                             FILTER( ID);
                           }

{INTEGER}                  { yylval.cint=atoi(yytext);
                             FILTER( NUM);
                           }
{FLOAT}                    { yylval.cflt=atof(yytext);
                             FILTER( FLOAT);
                           }

  /* Whitespace and other characters at the bottom, you want to read them if there is no other token */
\n.*                       { 
                             yycolumn = 1;
                             global.line += 1;
                             global.col = 0;
                             yyless(1);
                           }
[ \t]                      { global.col += yyleng;
                           } 
%%

static inline void token_action() {
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = yycolumn;
    yylloc.last_column = yycolumn + yyleng - 1;
    yycolumn += yyleng;
}