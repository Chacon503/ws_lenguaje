%{
/*
 * parser.y -- WS Language v3.0
 * LALR(1) grammar.
 * Variable syntax: name type => value;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"

int  yylex(void);
void yyerror(const char* s);

extern FILE* yyin;
extern int   yylineno;
%}

%union {
    int    i_val;
    int    b_val;
    double d_val;
    char   c_val;
    char*  s_val;
    int    type_enum;
    struct SymbolEntry* entry;
}

%token PRINT
%token INT_TYPE CHAR_TYPE DOUBLE_TYPE BOOL_TYPE STRING_TYPE
%token ARROW SEMICOLON LPARENT RPARENT
%token PLUS SUB MUL DIV

%token <entry>  IDENTIFIER
%token <d_val>  NUMBER
%token <d_val>  DOUBLE_LITERAL
%token <c_val>  CHAR_LITERAL
%token <b_val>  BOOL_LITERAL
%token <s_val>  STRING_LITERAL

%left  PLUS SUB
%left  MUL  DIV

%type <type_enum> data_type
%type <d_val>     expression

%%

program
    : program statement
    | /* empty */
    ;

statement
    : variable_definition SEMICOLON
    | print_statement     SEMICOLON
    ;

data_type
    : INT_TYPE     { $$ = TYPE_INT;    }
    | DOUBLE_TYPE  { $$ = TYPE_DOUBLE; }
    | CHAR_TYPE    { $$ = TYPE_CHAR;   }
    | STRING_TYPE  { $$ = TYPE_STRING; }
    | BOOL_TYPE    { $$ = TYPE_BOOL;   }
    ;

expression
    : NUMBER                       { $$ = $1; }
    | DOUBLE_LITERAL               { $$ = (double) $1; }
    | CHAR_LITERAL                 { $$ = (double) $1; }
    | BOOL_LITERAL                 { $$ = (double) $1; }
    | IDENTIFIER {
        switch ($1->data_type) {
            case TYPE_INT:    $$ = (double) $1->data.i_value; break;
            case TYPE_DOUBLE: $$ = $1->data.d_value;          break;
            case TYPE_BOOL:
                fprintf(stderr, "[WS ERROR] Line %d: cannot operate on a boolean variable.\n", yylineno);
                $$ = 0; break;
            case TYPE_CHAR:
                fprintf(stderr, "[WS ERROR] Line %d: cannot operate on a char variable.\n", yylineno);
                $$ = 0; break;
            case TYPE_STRING:
                fprintf(stderr, "[WS ERROR] Line %d: cannot operate on a string variable.\n", yylineno);
                $$ = 0; break;
        }
    }
    | expression PLUS expression   { $$ = $1 + $3; }
    | expression SUB  expression   { $$ = $1 - $3; }
    | expression MUL  expression   { $$ = $1 * $3; }
    | expression DIV  expression   {
        if ($3 == 0) {
            fprintf(stderr, "[WS ERROR] Line %d: division by zero.\n", yylineno);
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | LPARENT expression RPARENT   { $$ = $2; }
    ;

/* name type => value; */
variable_definition
    : IDENTIFIER data_type ARROW expression {
        $1->data_type = (DataType) $2;
        assign_numeric_value($1, $2, $4);
    }
    | IDENTIFIER data_type ARROW STRING_LITERAL {
        $1->data_type = (DataType) $2;
        assign_string_value($1, $2, $4);
    }
    ;

print_statement
    : PRINT IDENTIFIER     { print_value($2); }
    | PRINT STRING_LITERAL { printf("%s\n", $2); free($2); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "[WS ERROR] Line %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.ws>\n", argv[0]);
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "[WS ERROR] Could not open file: %s\n", argv[1]);
        return 1;
    }
    yyin = file;
    int result = yyparse();
    fclose(file);
    if (result == 0) {
        printf("\nCompilation successful.\n");
    }
    free_table();
    return result;
}
