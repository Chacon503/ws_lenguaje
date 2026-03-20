/*
 * parser_helper.c -- WS Language v3.0
 * Typed value assignment and console output.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser_helper.h"
#include "symbols.h"

void assign_numeric_value(SymbolEntry* entry, DataType data_type, double value) {
    switch (data_type) {
        case TYPE_INT:    entry->data.i_value = (int)   value; break;
        case TYPE_DOUBLE: entry->data.d_value = (double)value; break;
        case TYPE_CHAR:   entry->data.c_value = (char)  value; break;
        case TYPE_BOOL:   entry->data.b_value = (int)   value; break;
        case TYPE_STRING:
            fprintf(stderr, "[WS ERROR] Cannot assign numeric value to string variable '%s'.\n",
                    entry->identifier);
            return;
    }
    entry->is_initialized = 1;
}

void assign_string_value(SymbolEntry* entry, DataType data_type, char* value) {
    if (data_type == TYPE_STRING) {
        if (entry->data.s_value) free(entry->data.s_value);
        entry->data.s_value   = strdup(value);
        entry->is_initialized = 1;
        free(value);
    } else {
        fprintf(stderr, "[WS ERROR] Cannot assign string value to non-string variable '%s'.\n",
                entry->identifier);
        free(value);
    }
}

void print_value(SymbolEntry* entry) {
    if (!entry->is_initialized) {
        fprintf(stderr, "[WS WARN] Variable '%s' printed before initialization.\n",
                entry->identifier);
        return;
    }
    switch (entry->data_type) {
        case TYPE_INT:    printf("%d\n",  entry->data.i_value); break;
        case TYPE_DOUBLE: printf("%f\n",  entry->data.d_value); break;
        case TYPE_CHAR:   printf("'%c'\n",entry->data.c_value); break;
        case TYPE_STRING: printf("%s\n",  entry->data.s_value ? entry->data.s_value : ""); break;
        case TYPE_BOOL:   printf("%s\n",  entry->data.b_value ? "true" : "false"); break;
    }
}
