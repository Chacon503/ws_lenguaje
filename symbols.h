#ifndef SYMBOLS_H
#define SYMBOLS_H

/*
 * symbols.h -- WS Language v3.0
 * Symbol table: type definitions and entry structure.
 */

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_BOOL
} DataType;

typedef struct SymbolEntry {
    DataType data_type;
    char*    identifier;
    int      line_number;
    int      is_initialized;
    union {
        int    i_value;
        int    b_value;
        double d_value;
        char   c_value;
        char*  s_value;
    } data;
    struct SymbolEntry* next;
} SymbolEntry;

typedef struct Scope {
    SymbolEntry* table;
    struct Scope* next;
} Scope;

extern Scope* scope_stack;

SymbolEntry* create_entry(char* name, int line);
SymbolEntry* find_entry(char* name);
void         print_table(void);
void         free_table(void);
void         push_scope(void);
void         pop_scope(void);
int          insert_in_current_scope(char* name, DataType type, int line);

#endif /* SYMBOLS_H */
