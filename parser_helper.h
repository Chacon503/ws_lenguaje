#ifndef PARSER_HELPER_H
#define PARSER_HELPER_H

/*
 * parser_helper.h -- WS Language v3.0
 * Helper functions for parser semantic actions.
 */

#include "symbols.h"

void assign_numeric_value(SymbolEntry* entry, DataType data_type, double value);
void assign_string_value(SymbolEntry* entry, DataType data_type, char* value);
void print_value(SymbolEntry* entry);

#endif /* PARSER_HELPER_H */
