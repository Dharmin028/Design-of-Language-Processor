%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit   [0-9]+(\.[0-9]+)?
%%

{digit}   { yylval.val = atof(yytext); return DIGIT; }
\+        { return PLUS; }
\-        { return MINUS; }
\*        { return MULTIPLY; }
\/        { return DIVIDE; }
\^        { return EXPONENT; }
\(        { return LPAREN; }
\)        { return RPAREN; }
[ \t\n]   { /* Ignore whitespace */ }
.         { printf("Invalid character: %s\n", yytext); exit(1); }

%%
