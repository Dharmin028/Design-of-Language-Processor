%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);
void yyerror(char *s);

// Variable to hold the evaluated result
double result;

%}

%union {
    double val;
}

%token <val> DIGIT
%token PLUS MINUS MULTIPLY DIVIDE EXPONENT LPAREN RPAREN

%%

L: E { result = $1; printf("Result: %f\n", result); }
  ;

E: E PLUS T { $$ = $1 + $3; }
  | E MINUS T { $$ = $1 - $3; }
  | T { $$ = $1; }
  ;

T: T MULTIPLY F { $$ = $1 * $3; }
  | T DIVIDE F { $$ = $1 / $3; }
  | F { $$ = $1; }
  ;

F: G EXPONENT F { $$ = pow($1, $3); }
  | G { $$ = $1; }
  ;

G: LPAREN E RPAREN { $$ = $2; }
  | DIGIT { $$ = $1; }
  ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void)
