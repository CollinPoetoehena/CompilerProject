%{
  // This is a lexer only used for testing regexes, do not use it for the real lexer!
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

%}
%p 6000 /* set positions to 6000 */
%e 2000 /* set nodes to 1100 */
%option noyywrap
%option nounput
%option yylineno

%%

  // Keywords
"if"                       { printf("If:\n%s\n", yytext); }  
"else"                     { printf("Else:\n%s\n", yytext); }       
"while"                    { printf("While:\n%s\n", yytext); }
"do"                       { printf("Do:\n%s\n", yytext); }
"for"                      { printf("For:\n%s\n", yytext); }
"return"                   { printf("Return:\n%s\n", yytext); }
"extern"                   { printf("Extern:\n%s\n", yytext); }
"export"                   { printf("Export:\n%s\n", yytext); }

%%


