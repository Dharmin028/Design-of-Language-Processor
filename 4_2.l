%{
#include <stdio.h>
#include <string.h>
%}

%%
[Cc][Hh][Aa][Rr][Uu][Ss][Aa][Tt]  { printf("university"); }
.|\n                             { ECHO; } // Echo all other characters
%%

int main() {
    printf("Enter input text:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}


//in cmd at file path of this file
//lex replace_charusat.l
//gcc lex.yy.c -o replace_charusat
//./replace_charusat
