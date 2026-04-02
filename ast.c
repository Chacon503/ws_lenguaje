#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private helper */
static ASTNode* ast_alloc(ASTNodeType type, int line) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "[WS ERROR] Out of memory for AST node.\n");
        exit(1);
    }
    node->node_type = type;
    node->line_number = line;
    return node;
}

/* Program and Block */
ASTNode* ast_create_program(ASTNode** statements, int count) {
    ASTNode* node = ast_alloc(NODE_PROGRAM, 0);
    node->data.block.statements = statements;
    node->data.block.statement_count = count;
    return node;
}

ASTNode* ast_create_block(ASTNode** statements, int count) {
    ASTNode* node = ast_alloc(NODE_BLOCK, 0);
    node->data.block.statements = statements;
    node->data.block.statement_count = count;
    return node;
}

/* Variable Declaration */
ASTNode* ast_create_var_decl(char* name, DataType type, ASTNode* initializer, int line) {
    ASTNode* node = ast_alloc(NODE_VAR_DECL, line);
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.type = type;
    node->data.var_decl.initializer = initializer;
    return node;
}

/* Variable Assignment */
ASTNode* ast_create_var_assign(char* name, ASTNode* value, int line) {
    ASTNode* node = ast_alloc(NODE_VAR_ASSIGN, line);
    node->data.var_assign.name = strdup(name);
    node->data.var_assign.value = value;
    return node;
}

/* Print Statement */
ASTNode* ast_create_print(ASTNode* expr, int line) {
    ASTNode* node = ast_alloc(NODE_PRINT, line);
    node->data.print_stmt.expr = expr;
    return node;
}

/* Function Declaration */
ASTNode* ast_create_func_decl(char* name, ASTNode** params, int param_count,
                               DataType return_type, ASTNode* body, int line) {
    ASTNode* node = ast_alloc(NODE_FUNC_DECL, line);
    node->data.func_decl.name = strdup(name);
    node->data.func_decl.params = params;
    node->data.func_decl.param_count = param_count;
    node->data.func_decl.return_type = return_type;
    node->data.func_decl.body = body;
    return node;
}

/* Function Call */
ASTNode* ast_create_func_call(char* name, ASTNode** args, int arg_count, int line) {
    ASTNode* node = ast_alloc(NODE_FUNC_CALL, line);
    node->data.func_call.name = strdup(name);
    node->data.func_call.args = args;
    node->data.func_call.arg_count = arg_count;
    return node;
}

/* If Statement */
ASTNode* ast_create_if(ASTNode* cond, ASTNode* then_br, ASTNode* else_br, int line) {
    ASTNode* node = ast_alloc(NODE_IF, line);
    node->data.if_stmt.condition = cond;
    node->data.if_stmt.then_branch = then_br;
    node->data.if_stmt.else_branch = else_br;
    return node;
}

/* While Statement */
ASTNode* ast_create_while(ASTNode* cond, ASTNode* body, int line) {
    ASTNode* node = ast_alloc(NODE_WHILE, line);
    node->data.while_stmt.condition = cond;
    node->data.while_stmt.body = body;
    return node;
}

/* Return Statement */
ASTNode* ast_create_return(ASTNode* value, int line) {
    ASTNode* node = ast_alloc(NODE_RETURN, line);
    node->data.return_stmt.value = value;
    return node;
}

/* Binary Operation */
ASTNode* ast_create_binop(BinOpType op, ASTNode* left, ASTNode* right, int line) {
    ASTNode* node = ast_alloc(NODE_BINOP, line);
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

/* Unary Operation */
ASTNode* ast_create_unary(UnaryOpType op, ASTNode* operand, int line) {
    ASTNode* node = ast_alloc(NODE_UNARY, line);
    node->data.unary.op = op;
    node->data.unary.operand = operand;
    return node;
}

/* Identifier */
ASTNode* ast_create_identifier(char* name, int line) {
    ASTNode* node = ast_alloc(NODE_IDENTIFIER, line);
    node->data.identifier.name = strdup(name);
    return node;
}

/* Literals */
ASTNode* ast_create_literal_int(int value, int line) {
    ASTNode* node = ast_alloc(NODE_LITERAL, line);
    node->data.literal.type = TYPE_INT;
    node->data.literal.value.i_val = value;
    return node;
}

ASTNode* ast_create_literal_double(double value, int line) {
    ASTNode* node = ast_alloc(NODE_LITERAL, line);
    node->data.literal.type = TYPE_DOUBLE;
    node->data.literal.value.d_val = value;
    return node;
}

ASTNode* ast_create_literal_char(char value, int line) {
    ASTNode* node = ast_alloc(NODE_LITERAL, line);
    node->data.literal.type = TYPE_CHAR;
    node->data.literal.value.c_val = value;
    return node;
}

ASTNode* ast_create_literal_string(char* value, int line) {
    ASTNode* node = ast_alloc(NODE_LITERAL, line);
    node->data.literal.type = TYPE_STRING;
    node->data.literal.value.s_val = strdup(value);
    return node;
}

ASTNode* ast_create_literal_bool(int value, int line) {
    ASTNode* node = ast_alloc(NODE_LITERAL, line);
    node->data.literal.type = TYPE_BOOL;
    node->data.literal.value.b_val = value;
    return node;
}

/* Parameter */
ASTNode* ast_create_param(char* name, DataType type, int line) {
    ASTNode* node = ast_alloc(NODE_PARAM, line);
    node->data.param.name = strdup(name);
    node->data.param.type = type;
    return node;
}

/* Utility Functions */
static void indent_print(int indent) {
    for (int i = 0; i < indent; i++) printf("  ");
}

static const char* binop_to_string(BinOpType op) {
    switch (op) {
        case BINOP_PLUS: return "+";
        case BINOP_MINUS: return "-";
        case BINOP_MUL: return "*";
        case BINOP_DIV: return "/";
        case BINOP_EQ: return "==";
        case BINOP_NE: return "!=";
        case BINOP_LT: return "<";
        case BINOP_LE: return "<=";
        case BINOP_GT: return ">";
        case BINOP_GE: return ">=";
        case BINOP_AND: return "&&";
        case BINOP_OR: return "||";
        default: return "?";
    }
}

static const char* type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_DOUBLE: return "double";
        case TYPE_CHAR: return "char";
        case TYPE_STRING: return "string";
        case TYPE_BOOL: return "boolean";
        default: return "unknown";
    }
}

void ast_print(ASTNode* node, int indent) {
    if (!node) return;
    
    switch (node->node_type) {
        case NODE_PROGRAM:
            indent_print(indent);
            printf("PROGRAM:\n");
            for (int i = 0; i < node->data.block.statement_count; i++) {
                ast_print(node->data.block.statements[i], indent + 1);
            }
            break;
            
        case NODE_BLOCK:
            indent_print(indent);
            printf("BLOCK:\n");
            for (int i = 0; i < node->data.block.statement_count; i++) {
                ast_print(node->data.block.statements[i], indent + 1);
            }
            break;
            
        case NODE_VAR_DECL:
            indent_print(indent);
            printf("VAR_DECL: %s %s\n", node->data.var_decl.name, type_to_string(node->data.var_decl.type));
            if (node->data.var_decl.initializer) {
                ast_print(node->data.var_decl.initializer, indent + 1);
            }
            break;
            
        case NODE_VAR_ASSIGN:
            indent_print(indent);
            printf("VAR_ASSIGN: %s\n", node->data.var_assign.name);
            ast_print(node->data.var_assign.value, indent + 1);
            break;
            
        case NODE_PRINT:
            indent_print(indent);
            printf("PRINT:\n");
            ast_print(node->data.print_stmt.expr, indent + 1);
            break;
            
        case NODE_FUNC_DECL:
            indent_print(indent);
            printf("FUNC_DECL: %s returns %s\n", node->data.func_decl.name,
                   type_to_string(node->data.func_decl.return_type));
            for (int i = 0; i < node->data.func_decl.param_count; i++) {
                ast_print(node->data.func_decl.params[i], indent + 1);
            }
            ast_print(node->data.func_decl.body, indent + 1);
            break;
            
        case NODE_FUNC_CALL:
            indent_print(indent);
            printf("FUNC_CALL: %s\n", node->data.func_call.name);
            for (int i = 0; i < node->data.func_call.arg_count; i++) {
                ast_print(node->data.func_call.args[i], indent + 1);
            }
            break;
            
        case NODE_IDENTIFIER:
            indent_print(indent);
            printf("IDENTIFIER: %s\n", node->data.identifier.name);
            break;
            
        case NODE_LITERAL:
            indent_print(indent);
            printf("LITERAL: %s = ", type_to_string(node->data.literal.type));
            switch (node->data.literal.type) {
                case TYPE_INT: printf("%d\n", node->data.literal.value.i_val); break;
                case TYPE_DOUBLE: printf("%f\n", node->data.literal.value.d_val); break;
                case TYPE_CHAR: printf("'%c'\n", node->data.literal.value.c_val); break;
                case TYPE_STRING: printf("\"%s\"\n", node->data.literal.value.s_val); break;
                case TYPE_BOOL: printf("%s\n", node->data.literal.value.b_val ? "true" : "false"); break;
            }
            break;
            
        case NODE_BINOP:
            indent_print(indent);
            printf("BINOP: %s\n", binop_to_string(node->data.binop.op));
            ast_print(node->data.binop.left, indent + 1);
            ast_print(node->data.binop.right, indent + 1);
            break;
            
        case NODE_PARAM:
            indent_print(indent);
            printf("PARAM: %s %s\n", node->data.param.name, type_to_string(node->data.param.type));
            break;
            
        default:
            indent_print(indent);
            printf("UNKNOWN NODE TYPE\n");
            break;
    }
}

void ast_free(ASTNode* node) {
    if (!node) return;
    
    switch (node->node_type) {
        case NODE_PROGRAM:
        case NODE_BLOCK:
            for (int i = 0; i < node->data.block.statement_count; i++) {
                ast_free(node->data.block.statements[i]);
            }
            free(node->data.block.statements);
            break;
            
        case NODE_VAR_DECL:
            free(node->data.var_decl.name);
            ast_free(node->data.var_decl.initializer);
            break;
            
        case NODE_VAR_ASSIGN:
            free(node->data.var_assign.name);
            ast_free(node->data.var_assign.value);
            break;
            
        case NODE_PRINT:
            ast_free(node->data.print_stmt.expr);
            break;
            
        case NODE_FUNC_DECL:
            free(node->data.func_decl.name);
            for (int i = 0; i < node->data.func_decl.param_count; i++) {
                ast_free(node->data.func_decl.params[i]);
            }
            free(node->data.func_decl.params);
            ast_free(node->data.func_decl.body);
            break;
            
        case NODE_FUNC_CALL:
            free(node->data.func_call.name);
            for (int i = 0; i < node->data.func_call.arg_count; i++) {
                ast_free(node->data.func_call.args[i]);
            }
            free(node->data.func_call.args);
            break;
            
        case NODE_IF:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_branch);
            ast_free(node->data.if_stmt.else_branch);
            break;
            
        case NODE_WHILE:
            ast_free(node->data.while_stmt.condition);
            ast_free(node->data.while_stmt.body);
            break;
            
        case NODE_RETURN:
            ast_free(node->data.return_stmt.value);
            break;
            
        case NODE_IDENTIFIER:
            free(node->data.identifier.name);
            break;
            
        case NODE_LITERAL:
            if (node->data.literal.type == TYPE_STRING) {
                free(node->data.literal.value.s_val);
            }
            break;
            
        case NODE_BINOP:
            ast_free(node->data.binop.left);
            ast_free(node->data.binop.right);
            break;
            
        case NODE_UNARY:
            ast_free(node->data.unary.operand);
            break;
            
        case NODE_PARAM:
            free(node->data.param.name);
            break;
            
        default:
            break;
    }
    
    free(node);
}
