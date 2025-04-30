%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Variables to identify and classify tokens
int is_keyword(char *str);
int is_operator(char c);
int is_punctuation(char c);
int is_constant(char *str);
int is_identifier(char *str);
%}

%%
"int"|"char"|"return"   { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*  { 
    if (is_keyword(yytext)) {
        printf("Keyword: %s\n", yytext);
    } else if (is_identifier(yytext)) {
        printf("Identifier: %s\n", yytext);
    }
}
[0-9]+                  { printf("Constant: %s\n", yytext); }
\'[a-zA-Z0-9]\'         { printf("String: %s\n", yytext); }
"="|"+"|"-"|"*"|"/"    { printf("Operator: %s\n", yytext); }
[;,{}()\[\]]            { printf("Punctuation: %s\n", yytext); }
[ \t\n]+                { /* Ignore whitespaces */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* Ignore comments */ }
.                       { printf("Lexical Error: Invalid token %s\n", yytext); }

%%

int main() {
    FILE *input_file = fopen("input.c", "r");
    if (input_file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    yyin = input_file;  // Set the input file for Lex
    yylex();  // Perform lexical analysis

    fclose(input_file);
    return 0;
}

int yywrap() {
    return 1;
}

int is_keyword(char *str) {
    // Check if the string is a C keyword
    if (strcmp(str, "int") == 0 || strcmp(str, "char") == 0 || strcmp(str, "return") == 0) {
        return 1;
    }
    return 0;
}

int is_operator(char c) {
    // Check if the character is a valid operator
    return (c == '=' || c == '+' || c == '-' || c == '*' || c == '/');
}

int is_punctuation(char c) {
    // Check if the character is a valid punctuation symbol
    return (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}');
}

int is_constant(char *str) {
    // Check if the string is a valid constant (integer for simplicity)
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int is_identifier(char *str) {
    // Check if the string is a valid identifier
    if (isalpha(str[0]) || str[0] == '_') {
        for (int i = 1; str[i] != '\0'; i++) {
            if (!isalnum(str[i]) && str[i] != '_') {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
