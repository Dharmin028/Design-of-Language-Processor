# Design-of-Language-Processor


## to run lex file:
##### 1-> go to cmd and traverse to path where lex file exist (cd C:\path\to\your\lex\file
)
##### 2-> flex demo.l (replace demo with filename)
##### 3-> gcc lex.yy.c -o lexer.exe
##### 4 -> lexer.exe


## to run YACC file:

### Create the files:
#### 1-> Create two files: demo.y (YACC file) and example.l (Lex file).  (replace demo and example with original file name)

### Compile the Lex and YACC files:
#### Use the following commands to generate the necessary files:

##### 2-> yacc -d demo.y — This generates the y.tab.c (C source) and y.tab.h (header file). (replace demo with original file name)
##### 3-> lex example.l — This generates the lex.yy.c file. (replace example with original file name)

### Compile the C files:
#### Use the gcc command to compile the generated C files:
##### 4-> gcc -o parser y.tab.c lex.yy.c -ll -ly — This will compile and link the files to generate the executable parser.

### Run the program:

##### 5-> Execute the program by running: ./parser.
