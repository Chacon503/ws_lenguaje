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
    ctx->returned = 0;
    memset(&ctx->return_value, 0, sizeof(Value));
    return ctx;
}

void interp_free(InterpreterContext* ctx) {
    if (!ctx) return;

    if (ctx->return_value.s_val) {
        free(ctx->return_value.s_val);
    }

    free(ctx);
}


static Value value_int(int val) {
    Value v = {0};
    v.type = TYPE_INT;
    v.i_val = val;
    return v;
}

static Value value_double(double val) {
    Value v = {0};
    v.type = TYPE_DOUBLE;
    v.d_val = val;
    return v;
}

static Value value_char(char val) {
    Value v = {0};
    v.type = TYPE_CHAR;
    v.c_val = val;
    return v;
}

static Value value_bool(int val) {
    Value v = {0};
    v.type = TYPE_BOOL;
    v.b_val = val;
    return v;
}

static Value value_string(char* val) {
    Value v = {0};
    v.type = TYPE_STRING;
    v.s_val = strdup(val);
    return v;
}

static void print_value(DataType type, Value val) {
    switch (type) {
        case TYPE_INT:    printf("%d\n",  val.i_val); break;
        case TYPE_DOUBLE: printf("%g\n",  val.d_val); break;
        case TYPE_CHAR:   printf("'%c'\n", val.c_val); break;
        case TYPE_STRING: printf("%s\n",  val.s_val ? val.s_val : ""); break;
        case TYPE_BOOL:   printf("%s\n",  val.b_val ? "true" : "false"); break;
    }
}

static double to_double(Value val) {
    switch (val.type) {
        case TYPE_INT:    return (double) val.i_val;
        case TYPE_DOUBLE: return val.d_val;
        case TYPE_BOOL:   return (double) val.b_val;
        case TYPE_CHAR:   return (double) val.c_val;
        default:          return 0.0;
    }
}

static void store_value(SymbolEntry* entry, Value val) {
    double n = to_double(val);
    switch (entry->data_type) {
        case TYPE_INT:    entry->data.i_value = (int) n; break;
        case TYPE_DOUBLE: entry->data.d_value = n; break;
        case TYPE_CHAR:   entry->data.c_value = (char)(int) n; break;
        case TYPE_BOOL:   entry->data.b_value = (n != 0.0) ? 1 : 0; break;
        case TYPE_STRING:
            if (entry->data.s_value) free(entry->data.s_value);
            entry->data.s_value = strdup(val.s_val ? val.s_val : "");
            break;
    }
    entry->is_initialized = 1;
}

Value interp_eval_expr(InterpreterContext* ctx, ASTNode* expr) {
    if (!expr) {
        return value_int(0);
    }

    switch (expr->node_type) {
        case NODE_LITERAL: {
            switch (expr->data.literal.type) {
                case TYPE_INT:    return value_int(expr->data.literal.value.i_val);
                case TYPE_DOUBLE: return value_double(expr->data.literal.value.d_val);
                case TYPE_CHAR:   return value_char(expr->data.literal.value.c_val);
                case TYPE_STRING: return value_string(expr->data.literal.value.s_val);
                case TYPE_BOOL:   return value_bool(expr->data.literal.value.b_val);
                default:          return value_int(0);
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
                case TYPE_INT:    return value_int(entry->data.i_value);
                case TYPE_DOUBLE: return value_double(entry->data.d_value);
                case TYPE_CHAR:   return value_char(entry->data.c_value);
                case TYPE_STRING: return value_string(entry->data.s_value);
                case TYPE_BOOL:   return value_bool(entry->data.b_value);
                default:          return value_int(0);
            }
        }

        case NODE_BINOP: {
            Value left  = interp_eval_expr(ctx, expr->data.binop.left);
            Value right = interp_eval_expr(ctx, expr->data.binop.right);
            double l = to_double(left);
            double r = to_double(right);

            switch (expr->data.binop.op) {
                case BINOP_PLUS:  return value_double(l + r);
                case BINOP_MINUS: return value_double(l - r);
                case BINOP_MUL:   return value_double(l * r);
                case BINOP_DIV:
                    if (r == 0) {
                        fprintf(stderr, "[WS ERROR] Line %d: Division by zero.\n", expr->line_number);
                        return value_double(0);
                    }
                    return value_double(l / r);
                case BINOP_EQ:  return value_bool(l == r ? 1 : 0);
                case BINOP_NE:  return value_bool(l != r ? 1 : 0);
                case BINOP_LT:  return value_bool(l <  r ? 1 : 0);
                case BINOP_LE:  return value_bool(l <= r ? 1 : 0);
                case BINOP_GT:  return value_bool(l >  r ? 1 : 0);
                case BINOP_GE:  return value_bool(l >= r ? 1 : 0);
                case BINOP_AND: return value_bool((l != 0 && r != 0) ? 1 : 0);
                case BINOP_OR:  return value_bool((l != 0 || r != 0) ? 1 : 0);
                default:        return value_double(0);
            }
        }

        case NODE_UNARY: {
            Value operand = interp_eval_expr(ctx, expr->data.unary.operand);
            double v = to_double(operand);
            switch (expr->data.unary.op) {
                case UNARY_NEG: return value_double(-v);
                case UNARY_NOT: return value_bool(v == 0 ? 1 : 0);
                default:        return value_double(0);
            }
        }

        default:
            return value_int(0);
    }
}

static void interp_execute_stmt(InterpreterContext* ctx, ASTNode* stmt) {
    if (!stmt || ctx->returned) return;

    switch (stmt->node_type) {
        case NODE_VAR_DECL: {
            if (insert_in_current_scope(stmt->data.var_decl.name,
                                        stmt->data.var_decl.type,
                                        stmt->line_number) == 0) {
                SymbolEntry* entry = find_entry(stmt->data.var_decl.name);
                if (stmt->data.var_decl.initializer) {
                    Value init_val = interp_eval_expr(ctx, stmt->data.var_decl.initializer);
                    store_value(entry, init_val);
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
                store_value(entry, val);
            }
            break;
        }

        case NODE_PRINT: {
            Value val = interp_eval_expr(ctx, stmt->data.print_stmt.expr);
            if (stmt->data.print_stmt.expr->node_type == NODE_IDENTIFIER) {
                SymbolEntry* entry = find_entry(stmt->data.print_stmt.expr->data.identifier.name);
                if (!entry) {
                    fprintf(stderr, "[WS ERROR] Line %d: Undefined variable '%s'.\n",
                            stmt->line_number, stmt->data.print_stmt.expr->data.identifier.name);
                    break;
                }
                print_value(entry->data_type, val);
            } else {
                print_value(val.type, val);
            }
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
            if (to_double(cond) != 0) {
                interp_execute_stmt(ctx, stmt->data.if_stmt.then_branch);
            } else if (stmt->data.if_stmt.else_branch) {
                interp_execute_stmt(ctx, stmt->data.if_stmt.else_branch);
            }
            break;
        }

        case NODE_WHILE: {
            while (1) {
                Value cond = interp_eval_expr(ctx, stmt->data.while_stmt.condition);
                if (to_double(cond) == 0) break;
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
