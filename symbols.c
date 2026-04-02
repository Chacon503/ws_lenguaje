/*
 * symbols.c -- WS Language v3.0
 * Symbol table implementation with scopes (stack of linked lists).
 */
#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Scope* scope_stack = NULL;

void push_scope(void) {
    Scope* new_scope = (Scope*) malloc(sizeof(Scope));
    if (!new_scope) {
        fprintf(stderr, "[WS ERROR] Out of memory for new scope.\n");
        exit(1);
    }
    new_scope->table = NULL;
    new_scope->next = scope_stack;
    scope_stack = new_scope;
}

void pop_scope(void) {
    if (scope_stack == NULL) {
        fprintf(stderr, "[WS ERROR] No scope to pop.\n");
        return;
    }
    Scope* top = scope_stack;
    scope_stack = scope_stack->next;
    // Free the table in this scope
    SymbolEntry* current = top->table;
    while (current != NULL) {
        SymbolEntry* next = current->next;
        free(current->identifier);
        if (current->data_type == TYPE_STRING && current->data.s_value)
            free(current->data.s_value);
        free(current);
        current = next;
    }
    free(top);
}

int insert_in_current_scope(char* name, DataType type, int line) {
    if (scope_stack == NULL) {
        push_scope(); // Ensure at least global scope
    }
    // Check if already in current scope
    SymbolEntry* current = scope_stack->table;
    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) {
            return -1; // Already declared in this scope
        }
        current = current->next;
    }
    // Insert
    SymbolEntry* node = (SymbolEntry*) malloc(sizeof(SymbolEntry));
    if (!node) {
        fprintf(stderr, "[WS ERROR] Out of memory for variable '%s'.\n", name);
        exit(1);
    }
    node->data_type      = type;
    node->identifier     = strdup(name);
    node->line_number    = line;
    node->is_initialized = 0;
    node->next           = scope_stack->table;
    scope_stack->table   = node;
    return 0;
}

SymbolEntry* find_entry(char* name) {
    Scope* current_scope = scope_stack;
    while (current_scope != NULL) {
        SymbolEntry* current = current_scope->table;
        while (current != NULL) {
            if (strcmp(current->identifier, name) == 0) return current;
            current = current->next;
        }
        current_scope = current_scope->next;
    }
    return NULL;
}

SymbolEntry* create_entry(char* name, int line) {
    // This is now deprecated, use insert_in_current_scope
    return NULL;
}

void print_table(void) {
    Scope* current_scope = scope_stack;
    int scope_level = 0;
    while (current_scope != NULL) {
        printf("\nScope Level %d:\n", scope_level);
        printf("+------------------+----------+------+----------------+\n");
        printf("|          Symbol Table -- WS Lang                   |\n");
        printf("+------------------+----------+------+----------------+\n");
        printf("| Name             | Type     | Line | Value          |\n");
        printf("+------------------+----------+------+----------------+\n");
        SymbolEntry* current = current_scope->table;
        while (current != NULL) {
            const char* type_name;
            switch (current->data_type) {
                case TYPE_INT:    type_name = "int";     break;
                case TYPE_DOUBLE: type_name = "double";  break;
                case TYPE_CHAR:   type_name = "char";    break;
                case TYPE_STRING: type_name = "string";  break;
                case TYPE_BOOL:   type_name = "boolean"; break;
                default:          type_name = "?";
            }
            printf("| %-16s | %-8s | %4d | ", current->identifier, type_name, current->line_number);
            if (!current->is_initialized) {
                printf("(unset)         |\n");
            } else {
                switch (current->data_type) {
                    case TYPE_INT:    printf("%-14d |\n",  current->data.i_value); break;
                    case TYPE_DOUBLE: printf("%-14.4f |\n", current->data.d_value); break;
                    case TYPE_CHAR:   printf("'%c'%-11s |\n", current->data.c_value, ""); break;
                    case TYPE_STRING: printf("\"%-13s\" |\n", current->data.s_value ? current->data.s_value : ""); break;
                    case TYPE_BOOL:   printf("%-14s |\n",  current->data.b_value ? "true" : "false"); break;
                }
            }
            current = current->next;
        }
        printf("+------------------+----------+------+----------------+\n");
        current_scope = current_scope->next;
        scope_level++;
    }
}

void free_table(void) {
    while (scope_stack != NULL) {
        pop_scope();
    }
}
