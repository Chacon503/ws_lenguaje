%{
/*
 * parser.y -- WS Lenguaje
 * LALR(1) grammar with AST generation.
 * Variable syntax: name type => value;
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser_helper.h"
#include "ast.h"
#include "interpreter.h"

int  yylex(void);
void yyerror(const char* s);

extern FILE* yyin;
extern int   yylineno;

ASTNode* root_ast = NULL;
InterpreterContext* interp = NULL;
%}

%union {
    int    i_val;
    int    b_val;
    double d_val;
    char   c_val;
    char*  s_val;
    int    type_enum;
    struct SymbolEntry* entry;
    struct ASTNode* ast_node;
    struct ASTNode** ast_array;
}

%token PRINT FUNCTION RETURN IF ELSE WHILE
%token INT_TYPE CHAR_TYPE DOUBLE_TYPE BOOL_TYPE STRING_TYPE
%token ARROW SEMICOLON LPARENT RPARENT LBRACE RBRACE COMMA EQUALS
%token PLUS SUB MUL DIV EQ NE LT LE GT GE AND OR NOT

%token <s_val>   IDENTIFIER
%token <d_val>  NUMBER
%token <d_val>  DOUBLE_LITERAL
%token <c_val>  CHAR_LITERAL
%token <b_val>  BOOL_LITERAL
%token <s_val>  STRING_LITERAL

%left  OR
%left  AND
%left  EQ NE
%left  LT LE GT GE
%left  PLUS SUB
%left  MUL  DIV
%right NOT

%type <type_enum>     data_type
%type <ast_node>      expression
%type <ast_node>      statement
%type <ast_node>      block
%type <ast_node>      var_declaration
%type <ast_node>      var_assignment
%type <ast_node>      print_statement
%type <ast_node>      function_declaration
%type <ast_node>      function_call
%type <ast_node>      if_statement
%type <ast_node>      while_statement
%type <ast_array>     statements
%type <ast_array>     parameter_list
%type <ast_array>     argument_list

%%

program
    : statements {
        if ($1 != NULL) {
            /* Count statements in the array */
            int count = 0;
            while ($1[count] != NULL) count++;
            root_ast = ast_create_program($1, count);
        }
    }
    ;

statements
    : statement {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 100);
        if ($1 != NULL) {
            arr[0] = $1;
            arr[1] = NULL;
        } else {
            arr[0] = NULL;
        }
        $$ = arr;
    }
    | statements statement {
        if ($2 != NULL) {
            int i = 0;
            while ($1[i] != NULL) i++;
            $1[i] = $2;
            $1[i + 1] = NULL;
        }
        $$ = $1;
    }
    | /* empty */ {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 100);
        arr[0] = NULL;
        $$ = arr;
    }
    ;

statement
    : var_declaration SEMICOLON { $$ = $1; }
    | var_assignment SEMICOLON { $$ = $1; }
    | print_statement SEMICOLON { $$ = $1; }
    | function_declaration { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | block { $$ = $1; }
    | RETURN expression SEMICOLON {
        $$ = ast_create_return($2, yylineno);
    }
    | function_call SEMICOLON { $$ = $1; }
    ;

block
    : LBRACE statements RBRACE {
        if ($2 != NULL) {
            int count = 0;
            while ($2[count] != NULL) count++;
            $$ = ast_create_block($2, count);
        } else {
            $$ = ast_create_block(NULL, 0);
        }
    }
    ;

data_type
    : INT_TYPE     { $$ = TYPE_INT;    }
    | DOUBLE_TYPE  { $$ = TYPE_DOUBLE; }
    | CHAR_TYPE    { $$ = TYPE_CHAR;   }
    | STRING_TYPE  { $$ = TYPE_STRING; }
    | BOOL_TYPE    { $$ = TYPE_BOOL;   }
    ;

var_declaration
    : IDENTIFIER data_type ARROW expression {
        $$ = ast_create_var_decl($1, (DataType)$2, $4, yylineno);
        free($1);
    }
    | IDENTIFIER data_type ARROW STRING_LITERAL {
        $$ = ast_create_var_decl($1, (DataType)$2, 
            ast_create_literal_string($4, yylineno), yylineno);
        free($1);
    }
    | IDENTIFIER data_type ARROW CHAR_LITERAL {
        $$ = ast_create_var_decl($1, (DataType)$2, 
            ast_create_literal_char($4, yylineno), yylineno);
        free($1);
    }
    | IDENTIFIER data_type ARROW BOOL_LITERAL {
        $$ = ast_create_var_decl($1, (DataType)$2, 
            ast_create_literal_bool($4, yylineno), yylineno);
        free($1);
    }
    ;

var_assignment
    : IDENTIFIER EQUALS expression {
        $$ = ast_create_var_assign($1, $3, yylineno);
        free($1);
    }
    | IDENTIFIER EQUALS STRING_LITERAL {
        $$ = ast_create_var_assign($1, 
            ast_create_literal_string($3, yylineno), yylineno);
        free($1);
    }
    ;

print_statement
    : PRINT IDENTIFIER { 
        $$ = ast_create_print(ast_create_identifier($2, yylineno), yylineno);
        free($2);
    }
    | PRINT STRING_LITERAL {
        $$ = ast_create_print(ast_create_literal_string($2, yylineno), yylineno);
        free($2);
    }
    | PRINT expression {
        $$ = ast_create_print($2, yylineno);
    }
    ;

function_declaration
    : FUNCTION IDENTIFIER LPARENT parameter_list RPARENT data_type LBRACE statements RBRACE {
        int param_count = 0;
        while ($4 != NULL && $4[param_count] != NULL) param_count++;
        
        int stmt_count = 0;
        while ($8 != NULL && $8[stmt_count] != NULL) stmt_count++;
        
        ASTNode* body = ast_create_block($8, stmt_count);
        $$ = ast_create_func_decl($2, $4, param_count, (DataType)$6, body, yylineno);
        free($2);
    }
    | FUNCTION IDENTIFIER LPARENT RPARENT data_type LBRACE statements RBRACE {
        int stmt_count = 0;
        while ($7 != NULL && $7[stmt_count] != NULL) stmt_count++;
        
        ASTNode* body = ast_create_block($7, stmt_count);
        $$ = ast_create_func_decl($2, NULL, 0, (DataType)$5, body, yylineno);
        free($2);
    }
    ;

parameter_list
    : IDENTIFIER data_type {
        ASTNode** params = (ASTNode**) malloc(sizeof(ASTNode*) * 10);
        params[0] = ast_create_param($1, (DataType)$2, yylineno);
        params[1] = NULL;
        $$ = params;
        free($1);
    }
    | parameter_list COMMA IDENTIFIER data_type {
        int i = 0;
        while ($1[i] != NULL) i++;
        $1[i] = ast_create_param($3, (DataType)$4, yylineno);
        $1[i + 1] = NULL;
        $$ = $1;
        free($3);
    }
    ;

if_statement
    : IF LPARENT expression RPARENT block {
        $$ = ast_create_if($3, $5, NULL, yylineno);
    }
    | IF LPARENT expression RPARENT block ELSE block {
        $$ = ast_create_if($3, $5, $7, yylineno);
    }
    ;


while_statement
    : WHILE LPARENT expression RPARENT block {
        $$ = ast_create_while($3, $5, yylineno);
    }
    ;

function_call
    : IDENTIFIER LPARENT argument_list RPARENT {
        int arg_count = 0;
        if ($3 != NULL) {
            while ($3[arg_count] != NULL) arg_count++;
        }
        $$ = ast_create_func_call($1, $3, arg_count, yylineno);
        free($1);
    }
    ;

argument_list
    : expression {
        ASTNode** arr = (ASTNode**) malloc(sizeof(ASTNode*) * 10);
        arr[0] = $1;
        arr[1] = NULL;
        $$ = arr;
    }
    | argument_list COMMA expression {
        int i = 0;
        while ($1[i] != NULL) i++;
        $1[i] = $3;
        $1[i + 1] = NULL;
        $$ = $1;
    }
    | /* empty */ {
        $$ = NULL;
    }
    ;

expression
    : NUMBER                       { $$ = ast_create_literal_int((int)$1, yylineno); }
    | DOUBLE_LITERAL               { $$ = ast_create_literal_double($1, yylineno); }
    | CHAR_LITERAL                 { $$ = ast_create_literal_char($1, yylineno); }
    | BOOL_LITERAL                 { $$ = ast_create_literal_bool($1, yylineno); }
    | STRING_LITERAL               { $$ = ast_create_literal_string($1, yylineno); }
    | IDENTIFIER                   { $$ = ast_create_identifier($1, yylineno); free($1); }
    | expression PLUS expression   { $$ = ast_create_binop(BINOP_PLUS, $1, $3, yylineno); }
    | expression SUB  expression   { $$ = ast_create_binop(BINOP_MINUS, $1, $3, yylineno); }
    | expression MUL  expression   { $$ = ast_create_binop(BINOP_MUL, $1, $3, yylineno); }
    | expression DIV  expression   { $$ = ast_create_binop(BINOP_DIV, $1, $3, yylineno); }
    | expression EQ expression     { $$ = ast_create_binop(BINOP_EQ, $1, $3, yylineno); }
    | expression NE expression     { $$ = ast_create_binop(BINOP_NE, $1, $3, yylineno); }
    | expression LT expression     { $$ = ast_create_binop(BINOP_LT, $1, $3, yylineno); }
    | expression LE expression     { $$ = ast_create_binop(BINOP_LE, $1, $3, yylineno); }
    | expression GT expression     { $$ = ast_create_binop(BINOP_GT, $1, $3, yylineno); }
    | expression GE expression     { $$ = ast_create_binop(BINOP_GE, $1, $3, yylineno); }
    | expression AND expression    { $$ = ast_create_binop(BINOP_AND, $1, $3, yylineno); }
    | expression OR expression     { $$ = ast_create_binop(BINOP_OR, $1, $3, yylineno); }
    | NOT expression               { $$ = ast_create_unary(UNARY_NOT, $2, yylineno); }
    | SUB expression %prec MUL    { $$ = ast_create_unary(UNARY_NEG, $2, yylineno); }
    | LPARENT expression RPARENT   { $$ = $2; }
    | function_call                { $$ = $1; }
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
    push_scope();
    
    interp = interp_create();
    
    int result = yyparse();
    fclose(file);
    
    if (result == 0 && root_ast != NULL) {
        printf("\nParsing successful. Executing...\n\n");
        interp_execute(interp, root_ast);
        ast_free(root_ast);
        printf("\n[SUCCESS] Program executed successfully.\n");
    } else if (result == 0) {
        printf("\nNo statements to execute.\n");
    }
    
    interp_free(interp);
    free_table();
    return result;
}
