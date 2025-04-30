%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);
int yylex(void);
%}

%token i a t e b

%%

S: i E t S S' 
  | a
  ;

S': e S
   | /* empty */
   ;

E: b
  ;

%%

int main(void)
{
    printf("Enter a string: ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

