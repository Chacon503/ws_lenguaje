#ifndef INTERPRETER_H
#define INTERPRETER_H

/*
 * interpreter.h -- WS Language v3.0
 * AST Interpreter with scope shadowing
 */

#include "ast.h"
#include "symbols.h"

typedef struct {
    DataType type;
    int i_val;
    double d_val;
    char c_val;
    int b_val;
    char* s_val;
} Value;

typedef struct {
    int returned;
    Value return_value;
} InterpreterContext;

/* Interpreter initialization and cleanup */
InterpreterContext* interp_create(void);
void interp_free(InterpreterContext* ctx);

/* Execution */
void interp_execute(InterpreterContext* ctx, ASTNode* program);
Value interp_eval_expr(InterpreterContext* ctx, ASTNode* expr);


#endif /* INTERPRETER_H */
