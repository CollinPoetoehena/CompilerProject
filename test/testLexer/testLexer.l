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

  // regular expressions for common lexemes
  // '\' is used to escape a character, such as '.' or '/'
DIGIT            [0-9]
NONZERO_DIGIT    [1-9]
LETTER           [a-zA-Z]
INTEGER          {DIGIT}+
  // FLOAT accepts: '123.456', '.456'
FLOAT            ({DIGIT}+\.{DIGIT}*)?
COMMENT_MULTI    \/\*[^*]*\*+([^/*][^*]*\*+)*\/
COMMENT_ONE      \/\/[^\n]*
COMMENT          ({COMMENT_ONE}|{COMMENT_MULTI})

%%

{COMMENT}                   { printf("Comment:\n%s\n", yytext); }


%%


