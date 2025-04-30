%{
#include "y.tab.h"
%}

%%

i       { return i; }
a       { return a; }
t       { return t; }
e       { return e; }
b       { return b; }
\n      { return 0; }
[ \t]   { /* ignore whitespace */ }
.       { return yyerror("Invalid character"); }

%%
