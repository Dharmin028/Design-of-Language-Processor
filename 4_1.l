%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%s\n", yytext); } // Match and print numbers
.|\n      { /* Ignore other characters */ }
%%

int main() {
    printf("Enter input string:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}


//Save the code in a file named extract_numbers.l

// Compile it with:
// lex extract_numbers.l
// gcc lex.yy.c -o extract_numbers
// ./extract_numbers
  
// Input a string (terminate with Enter):
// a1b22c3
