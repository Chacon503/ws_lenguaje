/*
 * symbols.c -- WS Language v3.0
 * Symbol table implementation (singly-linked list).
 */
#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SymbolEntry* root_table = NULL;

SymbolEntry* create_entry(char* name, int line) {
    if (find_entry(name) != NULL) {
        fprintf(stderr, "[WS ERROR] Line %d: variable '%s' already declared.\n", line, name);
    }
    SymbolEntry* node = (SymbolEntry*) malloc(sizeof(SymbolEntry));
    if (!node) {
        fprintf(stderr, "[WS ERROR] Out of memory for variable '%s'.\n", name);
        exit(1);
    }
    node->data_type      = TYPE_INT;
    node->data.i_value   = 0;
    node->identifier     = strdup(name);
    node->line_number    = line;
    node->is_initialized = 0;
    node->next           = root_table;
    root_table           = node;
    return node;
}

SymbolEntry* find_entry(char* name) {
    SymbolEntry* current = root_table;
    while (current != NULL) {
        if (strcmp(current->identifier, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void print_table(void) {
    SymbolEntry* current = root_table;
    printf("\n+------------------+----------+------+----------------+\n");
    printf(  "|          Symbol Table -- WS Lang                   |\n");
    printf(  "+------------------+----------+------+----------------+\n");
    printf(  "| Name             | Type     | Line | Value          |\n");
    printf(  "+------------------+----------+------+----------------+\n");
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
    printf("+------------------+----------+------+----------------+\n\n");
}

void free_table(void) {
    SymbolEntry* current = root_table;
    while (current != NULL) {
        SymbolEntry* next = current->next;
        free(current->identifier);
        if (current->data_type == TYPE_STRING && current->data.s_value)
            free(current->data.s_value);
        free(current);
        current = next;
    }
    root_table = NULL;
}
