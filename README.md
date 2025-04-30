# Design-of-Language-Processor


## to run lex file:
##### 1-> go to cmd and traverse to path where lex file exist
##### 2-> lex demo.l (replace demo with filename)
##### 3-> gcc lex.yy.c -o lexer -ll
##### 4 -> ./lexer


## to run YACC file:

### Create the files:
#### 1-> Create two files: parser.y (YACC file) and lexer.l (Lex file).

### Compile the Lex and YACC files:
#### Use the following commands to generate the necessary files:

##### 2-> yacc -d parser.y — This generates the y.tab.c (C source) and y.tab.h (header file).
##### 3-> lex lexer.l — This generates the lex.yy.c file.

### Compile the C files:
#### Use the gcc command to compile the generated C files:
##### 4-> gcc -o parser y.tab.c lex.yy.c -ll -ly — This will compile and link the files to generate the executable parser.

### Run the program:

##### 5-> Execute the program by running: ./parser.
