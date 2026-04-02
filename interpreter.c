#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

InterpreterContext* interp_create(void) {
    InterpreterContext* ctx = (InterpreterContext*) malloc(sizeof(InterpreterContext));
    if (!ctx) {
        fprintf(stderr, "[WS ERROR] Out of memory for interpreter context.\n");
        exit(1);
    }
    ctx->functions = NULL;
    ctx->returned = 0;
    return ctx;
}

void interp_free(InterpreterContext* ctx) {
    if (!ctx) return;
    
    FunctionDef* func = ctx->functions;
    while (func) {
        FunctionDef* next = func->next;
        free(func->name);
        free(func);
        func = next;
    }
    
    if (ctx->return_value.s_val) {
        free(ctx->return_value.s_val);
    }
    
    free(ctx);
}

void interp_register_function(InterpreterContext* ctx, char* name, ASTNode* decl) {
    FunctionDef* func = (FunctionDef*) malloc(sizeof(FunctionDef));
    if (!func) {
        fprintf(stderr, "[WS ERROR] Out of memory for function definition.\n");
        exit(1);
    }
    func->name = strdup(name);
    func->decl_node = decl;
    func->return_type = decl->data.func_decl.return_type;
    func->next = ctx->functions;
    ctx->functions = func;
}

FunctionDef* interp_find_function(InterpreterContext* ctx, char* name) {
    FunctionDef* func = ctx->functions;
    while (func) {
        if (strcmp(func->name, name) == 0) {
            return func;
        }
        func = func->next;
    }
    return NULL;
}

static Value value_int(int val) {
    Value v;
    v.i_val = val;
    return v;
}

static Value value_double(double val) {
    Value v;
    v.d_val = val;
    return v;
}

static Value value_char(char val) {
    Value v;
    v.c_val = val;
    return v;
}

static Value value_bool(int val) {
    Value v;
    v.b_val = val;
    return v;
}

static Value value_string(char* val) {
    Value v;
    v.s_val = strdup(val);
    return v;
}

static Value value_from_double(double val, DataType type) {
    Value v;
    switch (type) {
        case TYPE_INT:
            v.i_val = (int) val;
            break;
        case TYPE_DOUBLE:
            v.d_val = val;
            break;
        case TYPE_CHAR:
            v.c_val = (char) (int) val;
            break;
        case TYPE_BOOL:
            v.b_val = (val != 0) ? 1 : 0;
            break;
        default:
            v.i_val = 0;
            break;
    }
    return v;
}

static void print_value(DataType type, Value val) {
    switch (type) {
        case TYPE_INT:
            printf("%d\n", val.i_val);
            break;
        case TYPE_DOUBLE:
            printf("%f\n", val.d_val);
            break;
        case TYPE_CHAR:
            printf("'%c'\n", val.c_val);
            break;
        case TYPE_STRING:
            printf("%s\n", val.s_val);
            break;
        case TYPE_BOOL:
            printf("%s\n", val.b_val ? "true" : "false");
            break;
    }
}

static double to_double(DataType type, Value val) {
    switch (type) {
        case TYPE_INT:
            return (double) val.i_val;
        case TYPE_DOUBLE:
            return val.d_val;
        case TYPE_BOOL:
            return (double) val.b_val;
        case TYPE_CHAR:
            return (double) val.c_val;
        default:
            return 0.0;
    }
}

Value interp_eval_expr(InterpreterContext* ctx, ASTNode* expr) {
    if (!expr) {
        return value_int(0);
    }
    
    switch (expr->node_type) {
        case NODE_LITERAL: {
            switch (expr->data.literal.type) {
                case TYPE_INT:
                    return value_int(expr->data.literal.value.i_val);
                case TYPE_DOUBLE:
                    return value_double(expr->data.literal.value.d_val);
                case TYPE_CHAR:
                    return value_char(expr->data.literal.value.c_val);
                case TYPE_STRING:
                    return value_string(expr->data.literal.value.s_val);
                case TYPE_BOOL:
                    return value_bool(expr->data.literal.value.b_val);
                default:
                    return value_int(0);
            }
        }
        
        case NODE_IDENTIFIER: {
            SymbolEntry* entry = find_entry(expr->data.identifier.name);
            if (!entry) {
                fprintf(stderr, "[WS ERROR] Line %d: Undefined variable '%s'.\n",
                        expr->line_number, expr->data.identifier.name);
                return value_int(0);
            }
            
            switch (entry->data_type) {
                case TYPE_INT:
                    return value_int(entry->data.i_value);
                case TYPE_DOUBLE:
                    return value_double(entry->data.d_value);
                case TYPE_CHAR:
                    return value_char(entry->data.c_value);
                case TYPE_STRING:
                    return value_string(entry->data.s_value);
                case TYPE_BOOL:
                    return value_bool(entry->data.b_value);
                default:
                    return value_int(0);
            }
        }
        
        case NODE_BINOP: {
            Value left = interp_eval_expr(ctx, expr->data.binop.left);
            Value right = interp_eval_expr(ctx, expr->data.binop.right);
            
            double l = to_double(expr->data.binop.left->node_type == NODE_LITERAL ? 
                               expr->data.binop.left->data.literal.type : TYPE_DOUBLE, left);
            double r = to_double(expr->data.binop.right->node_type == NODE_LITERAL ? 
                               expr->data.binop.right->data.literal.type : TYPE_DOUBLE, right);
            
            double result = 0;
            switch (expr->data.binop.op) {
                case BINOP_PLUS:
                    result = l + r;
                    break;
                case BINOP_MINUS:
                    result = l - r;
                    break;
                case BINOP_MUL:
                    result = l * r;
                    break;
                case BINOP_DIV:
                    if (r == 0) {
                        fprintf(stderr, "[WS ERROR] Line %d: Division by zero.\n", expr->line_number);
                        result = 0;
                    } else {
                        result = l / r;
                    }
                    break;
                case BINOP_EQ:
                    return value_bool((l == r) ? 1 : 0);
                case BINOP_NE:
                    return value_bool((l != r) ? 1 : 0);
                case BINOP_LT:
                    return value_bool((l < r) ? 1 : 0);
                case BINOP_LE:
                    return value_bool((l <= r) ? 1 : 0);
                case BINOP_GT:
                    return value_bool((l > r) ? 1 : 0);
                case BINOP_GE:
                    return value_bool((l >= r) ? 1 : 0);
                case BINOP_AND:
                    return value_bool(((int)l && (int)r) ? 1 : 0);
                case BINOP_OR:
                    return value_bool(((int)l || (int)r) ? 1 : 0);
                default:
                    result = 0;
                    break;
            }
            return value_double(result);
        }
        
        case NODE_UNARY: {
            Value operand = interp_eval_expr(ctx, expr->data.unary.operand);
            double val = to_double(TYPE_DOUBLE, operand);
            
            switch (expr->data.unary.op) {
                case UNARY_NEG:
                    return value_double(-val);
                case UNARY_NOT:
                    return value_bool((val == 0) ? 1 : 0);
                default:
                    return value_double(0);
            }
        }
        
        case NODE_FUNC_CALL: {
            FunctionDef* func = interp_find_function(ctx, expr->data.func_call.name);
            if (!func) {
                fprintf(stderr, "[WS ERROR] Line %d: Undefined function '%s'.\n",
                        expr->line_number, expr->data.func_call.name);
                return value_int(0);
            }
            
            /* Evaluate arguments */
            push_scope();
            int arg_count = expr->data.func_call.arg_count;
            int param_count = func->decl_node->data.func_decl.param_count;
            
            if (arg_count != param_count) {
                fprintf(stderr, "[WS ERROR] Line %d: Function '%s' expects %d arguments, got %d.\n",
                        expr->line_number, expr->data.func_call.name, param_count, arg_count);
                pop_scope();
                return value_int(0);
            }
            
            /* Bind parameters to arguments */
            for (int i = 0; i < arg_count; i++) {
                Value arg_val = interp_eval_expr(ctx, expr->data.func_call.args[i]);
                ASTNode* param = func->decl_node->data.func_decl.params[i];
                
                insert_in_current_scope(param->data.param.name, param->data.param.type, expr->line_number);
                SymbolEntry* entry = find_entry(param->data.param.name);
                
                switch (param->data.param.type) {
                    case TYPE_INT:
                        entry->data.i_value = arg_val.i_val;
                        break;
                    case TYPE_DOUBLE:
                        entry->data.d_value = arg_val.d_val;
                        break;
                    case TYPE_CHAR:
                        entry->data.c_value = arg_val.c_val;
                        break;
                    case TYPE_STRING:
                        entry->data.s_value = strdup(arg_val.s_val);
                        break;
                    case TYPE_BOOL:
                        entry->data.b_value = arg_val.b_val;
                        break;
                }
                entry->is_initialized = 1;
            }
            
            /* Execute function body */
            ctx->returned = 0;
            interp_execute(ctx, func->decl_node->data.func_decl.body);
            
            Value result = ctx->return_value;
            ctx->returned = 0;
            
            pop_scope();
            return result;
        }
        
        default:
            return value_int(0);
    }
}

static void interp_execute_stmt(InterpreterContext* ctx, ASTNode* stmt) {
    if (!stmt || ctx->returned) return;
    
    switch (stmt->node_type) {
        case NODE_VAR_DECL: {
            SymbolEntry* entry = NULL;
            if (insert_in_current_scope(stmt->data.var_decl.name, 
                                       stmt->data.var_decl.type, 
                                       stmt->line_number) == 0) {
                entry = find_entry(stmt->data.var_decl.name);
                
                if (stmt->data.var_decl.initializer) {
                    Value init_val = interp_eval_expr(ctx, stmt->data.var_decl.initializer);
                    
                    switch (stmt->data.var_decl.type) {
                        case TYPE_INT:
                            entry->data.i_value = (int)init_val.d_val;
                            break;
                        case TYPE_DOUBLE:
                            entry->data.d_value = init_val.d_val;
                            break;
                        case TYPE_CHAR:
                            entry->data.c_value = init_val.c_val;
                            break;
                        case TYPE_STRING:
                            entry->data.s_value = strdup(init_val.s_val ? init_val.s_val : "");
                            break;
                        case TYPE_BOOL:
                            entry->data.b_value = init_val.b_val;
                            break;
                    }
                    entry->is_initialized = 1;
                }
            } else {
                fprintf(stderr, "[WS ERROR] Line %d: Variable '%s' already declared in this scope.\n",
                        stmt->line_number, stmt->data.var_decl.name);
            }
            break;
        }
        
        case NODE_VAR_ASSIGN: {
            SymbolEntry* entry = find_entry(stmt->data.var_assign.name);
            if (!entry) {
                fprintf(stderr, "[WS ERROR] Line %d: Undefined variable '%s'.\n",
                        stmt->line_number, stmt->data.var_assign.name);
            } else {
                Value val = interp_eval_expr(ctx, stmt->data.var_assign.value);
                
                switch (entry->data_type) {
                    case TYPE_INT:
                        entry->data.i_value = (int)val.d_val;
                        break;
                    case TYPE_DOUBLE:
                        entry->data.d_value = val.d_val;
                        break;
                    case TYPE_CHAR:
                        entry->data.c_value = val.c_val;
                        break;
                    case TYPE_STRING:
                        if (entry->data.s_value) free(entry->data.s_value);
                        entry->data.s_value = strdup(val.s_val ? val.s_val : "");
                        break;
                    case TYPE_BOOL:
                        entry->data.b_value = val.b_val;
                        break;
                }
                entry->is_initialized = 1;
            }
            break;
        }
        
        case NODE_PRINT: {
            if (stmt->data.print_stmt.expr->node_type == NODE_IDENTIFIER) {
                SymbolEntry* entry = find_entry(stmt->data.print_stmt.expr->data.identifier.name);
                if (!entry) {
                    fprintf(stderr, "[WS ERROR] Line %d: Undefined variable '%s'.\n",
                            stmt->line_number, stmt->data.print_stmt.expr->data.identifier.name);
                } else {
                    print_value(entry->data_type, interp_eval_expr(ctx, stmt->data.print_stmt.expr));
                }
            } else if (stmt->data.print_stmt.expr->node_type == NODE_LITERAL) {
                print_value(stmt->data.print_stmt.expr->data.literal.type, 
                           interp_eval_expr(ctx, stmt->data.print_stmt.expr));
            } else {
                Value val = interp_eval_expr(ctx, stmt->data.print_stmt.expr);
                printf("%f\n", val.d_val);
            }
            break;
        }
        
        case NODE_FUNC_DECL: {
            interp_register_function(ctx, stmt->data.func_decl.name, stmt);
            break;
        }
        
        case NODE_BLOCK: {
            push_scope();
            for (int i = 0; i < stmt->data.block.statement_count; i++) {
                if (stmt->data.block.statements[i] != NULL) {
                    interp_execute_stmt(ctx, stmt->data.block.statements[i]);
                    if (ctx->returned) break;
                }
            }
            pop_scope();
            break;
        }
        
        case NODE_RETURN: {
            if (stmt->data.return_stmt.value) {
                ctx->return_value = interp_eval_expr(ctx, stmt->data.return_stmt.value);
            } else {
                ctx->return_value = value_int(0);
            }
            ctx->returned = 1;
            break;
        }
        
        case NODE_IF: {
            Value cond = interp_eval_expr(ctx, stmt->data.if_stmt.condition);
            double cond_val = to_double(TYPE_DOUBLE, cond);
            
            if (cond_val != 0) {
                interp_execute_stmt(ctx, stmt->data.if_stmt.then_branch);
            } else if (stmt->data.if_stmt.else_branch) {
                interp_execute_stmt(ctx, stmt->data.if_stmt.else_branch);
            }
            break;
        }
        
        case NODE_WHILE: {
            while (1) {
                Value cond = interp_eval_expr(ctx, stmt->data.while_stmt.condition);
                double cond_val = to_double(TYPE_DOUBLE, cond);
                
                if (cond_val == 0) break;
                
                interp_execute_stmt(ctx, stmt->data.while_stmt.body);
                if (ctx->returned) break;
            }
            break;
        }
        
        default:
            break;
    }
}

void interp_execute(InterpreterContext* ctx, ASTNode* program) {
    if (!program) return;
    
    if (program->node_type == NODE_PROGRAM) {
        for (int i = 0; i < program->data.block.statement_count; i++) {
            if (program->data.block.statements[i] != NULL) {
                interp_execute_stmt(ctx, program->data.block.statements[i]);
                if (ctx->returned) break;
            }
        }
    } else {
        interp_execute_stmt(ctx, program);
    }
}
