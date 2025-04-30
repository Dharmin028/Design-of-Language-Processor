%{
#include <stdio.h>

int char_count = 0;  // To count characters
int word_count = 0;  // To count words
int line_count = 0;  // To count lines

%}

%%

\n      { line_count++; }  // Count lines (new line symbol)
[ \t]   { /* Ignore spaces and tabs */ }
[a-zA-Z0-9]+ { word_count++; char_count += yyleng; }  // Count words and characters (excluding spaces)
.       { char_count++; }  // Count other characters

%%

int main() {
    FILE *input_file = fopen("input.txt", "r");  // Open the input file
    if (input_file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    yyin = input_file;  // Set input file for Lex
    yylex();  // Start lexical analysis

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    fclose(input_file);
    return 0;
}

int yywrap() {
    return 1;
}


