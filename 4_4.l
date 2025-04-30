%{
#include <stdio.h>
#include <string.h>

int length_check = 0;
int has_lower = 0;
int has_upper = 0;
int has_digit = 0;
int has_symbol = 0;
%}

%%
[a-z]       { has_lower = 1; }
[A-Z]       { has_upper = 1; }
[0-9]       { has_digit = 1; }
[*;#$@]     { has_symbol = 1; }
.|\n        { length_check++; }  // Count all characters, including spaces and symbols

%%

int main() {
    char password[100];
    printf("Enter password: ");
    fgets(password, 100, stdin);
    
    // Remove newline character if exists
    password[strcspn(password, "\n")] = 0;

    // Process the password with Lex
    yyin = stdin; // Use stdin as input
    yylex();

    // Check the conditions for a valid password
    if (length_check >= 9 && length_check <= 15 && has_lower && has_upper && has_digit && has_symbol) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}

int yywrap() {
    return 1;
}
