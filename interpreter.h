#ifndef INTERPRETER_H
#define INTERPRETER_H

/*
 * interpreter.h -- WS Language v3.0
 * AST Interpreter with function support and scope shadowing
 */

#include "ast.h"
#include "symbols.h"

typedef struct {
    int i_val;
    double d_val;
    char c_val;
    int b_val;
    char* s_val;
} Value;

typedef struct FunctionDef {
    char* name;
    ASTNode* decl_node;  /* Function declaration node */
    DataType return_type;
    struct FunctionDef* next;
} FunctionDef;

typedef struct {
    FunctionDef* functions;
    int returned;
    Value return_value;
} InterpreterContext;

/* Interpreter initialization and cleanup */
InterpreterContext* interp_create(void);
void interp_free(InterpreterContext* ctx);

/* Execution */
void interp_execute(InterpreterContext* ctx, ASTNode* program);
Value interp_eval_expr(InterpreterContext* ctx, ASTNode* expr);

/* Function registry */
void interp_register_function(InterpreterContext* ctx, char* name, ASTNode* decl);
FunctionDef* interp_find_function(InterpreterContext* ctx, char* name);

#endif /* INTERPRETER_H */
