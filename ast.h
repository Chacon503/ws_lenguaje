#ifndef AST_H
#define AST_H

/*
 * ast.h -- WS Language v3.0
 * Abstract Syntax Tree node definitions
 */

#include "symbols.h"

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_VAR_DECL,
    NODE_VAR_ASSIGN,
    NODE_PRINT,
    NODE_FUNC_DECL,
    NODE_FUNC_CALL,
    NODE_IF,
    NODE_WHILE,
    NODE_RETURN,
    NODE_EXPR_STMT,
    NODE_BINOP,
    NODE_UNARY,
    NODE_IDENTIFIER,
    NODE_LITERAL,
    NODE_PARAM,
    NODE_ARG_LIST
} ASTNodeType;

typedef enum {
    BINOP_PLUS,
    BINOP_MINUS,
    BINOP_MUL,
    BINOP_DIV,
    BINOP_EQ,
    BINOP_NE,
    BINOP_LT,
    BINOP_LE,
    BINOP_GT,
    BINOP_GE,
    BINOP_AND,
    BINOP_OR
} BinOpType;

typedef enum {
    UNARY_NEG,
    UNARY_NOT
} UnaryOpType;

typedef union {
    int    i_val;
    double d_val;
    char   c_val;
    int    b_val;
    char*  s_val;
} LiteralValue;

typedef struct ASTNode {
    ASTNodeType node_type;
    int line_number;
    
    union {
        /* NODE_PROGRAM, NODE_BLOCK */
        struct {
            struct ASTNode** statements;
            int statement_count;
        } block;
        
        /* NODE_VAR_DECL */
        struct {
            char* name;
            DataType type;
            struct ASTNode* initializer;
        } var_decl;
        
        /* NODE_VAR_ASSIGN */
        struct {
            char* name;
            struct ASTNode* value;
        } var_assign;
        
        /* NODE_PRINT */
        struct {
            struct ASTNode* expr;
        } print_stmt;
        
        /* NODE_FUNC_DECL */
        struct {
            char* name;
            struct ASTNode** params;
            int param_count;
            DataType return_type;
            struct ASTNode* body;
        } func_decl;
        
        /* NODE_FUNC_CALL */
        struct {
            char* name;
            struct ASTNode** args;
            int arg_count;
        } func_call;
        
        /* NODE_IF */
        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_stmt;
        
        /* NODE_WHILE */
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;
        
        /* NODE_RETURN */
        struct {
            struct ASTNode* value;
        } return_stmt;
        
        /* NODE_BINOP */
        struct {
            BinOpType op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;
        
        /* NODE_UNARY */
        struct {
            UnaryOpType op;
            struct ASTNode* operand;
        } unary;
        
        /* NODE_IDENTIFIER */
        struct {
            char* name;
        } identifier;
        
        /* NODE_LITERAL */
        struct {
            DataType type;
            LiteralValue value;
        } literal;
        
        /* NODE_PARAM */
        struct {
            char* name;
            DataType type;
        } param;
        
        /* NODE_ARG_LIST */
        struct {
            struct ASTNode** args;
            int arg_count;
        } arg_list;
        
    } data;
} ASTNode;

/* AST Node Creation Functions */
ASTNode* ast_create_program(ASTNode** statements, int count);
ASTNode* ast_create_block(ASTNode** statements, int count);
ASTNode* ast_create_var_decl(char* name, DataType type, ASTNode* initializer, int line);
ASTNode* ast_create_var_assign(char* name, ASTNode* value, int line);
ASTNode* ast_create_print(ASTNode* expr, int line);
ASTNode* ast_create_func_decl(char* name, ASTNode** params, int param_count, 
                               DataType return_type, ASTNode* body, int line);
ASTNode* ast_create_func_call(char* name, ASTNode** args, int arg_count, int line);
ASTNode* ast_create_if(ASTNode* cond, ASTNode* then_br, ASTNode* else_br, int line);
ASTNode* ast_create_while(ASTNode* cond, ASTNode* body, int line);
ASTNode* ast_create_return(ASTNode* value, int line);
ASTNode* ast_create_binop(BinOpType op, ASTNode* left, ASTNode* right, int line);
ASTNode* ast_create_unary(UnaryOpType op, ASTNode* operand, int line);
ASTNode* ast_create_identifier(char* name, int line);
ASTNode* ast_create_literal_int(int value, int line);
ASTNode* ast_create_literal_double(double value, int line);
ASTNode* ast_create_literal_char(char value, int line);
ASTNode* ast_create_literal_string(char* value, int line);
ASTNode* ast_create_literal_bool(int value, int line);
ASTNode* ast_create_param(char* name, DataType type, int line);

/* AST Utilities */
void ast_print(ASTNode* node, int indent);
void ast_free(ASTNode* node);

#endif /* AST_H */
