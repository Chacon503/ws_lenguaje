# AST (Abstract Syntax Tree) - WS Lenguaje 

## Descripción General


1. **Ejecutar funciones** con parámetros
2. **Manejar scopes con shadowing** para variables
3. **Generar un árbol sintáctico** antes de ejecutar el programa

## Componentes Principales

### 1. **ast.h y ast.c** - Definiciones del AST

Define toda la estructura de nodos del árbol sintáctico:

#### Tipos de Nodos (ASTNodeType):
- `NODE_PROGRAM` - Raíz del programa
- `NODE_BLOCK` - Bloque de código (scope)
- `NODE_VAR_DECL` - Declaración de variable
- `NODE_VAR_ASSIGN` - Asignación de variable
- `NODE_PRINT` - Sentencia print
- `NODE_FUNC_DECL` - Declaración de función
- `NODE_FUNC_CALL` - Llamada a función
- `NODE_IF` - Sentencia condicional
- `NODE_WHILE` - Bucle while
- `NODE_RETURN` - Sentencia return
- `NODE_BINOP` - Operación binaria (+, -, *, /, ==, etc.)
- `NODE_UNARY` - Operación unaria (negación, not)
- `NODE_IDENTIFIER` - Identificador/variable
- `NODE_LITERAL` - Valor literal (número, string, char, bool)
- `NODE_PARAM` - Parámetro de función

#### Operaciones Binarias Soportadas:
```c
typedef enum {
    BINOP_PLUS, BINOP_MINUS, BINOP_MUL, BINOP_DIV,
    BINOP_EQ, BINOP_NE, BINOP_LT, BINOP_LE, BINOP_GT, BINOP_GE,
    BINOP_AND, BINOP_OR
} BinOpType;
```

### 2. **interpreter.h y interpreter.c** - Evaluador del AST

Implementa un intérprete que recorre el árbol sintáctico y ejecuta el programa.

#### Características Principales:

**Sistema de Valores Dinámicos:**
```c
typedef struct {
    int i_val;      // entero
    double d_val;   // flotante
    char c_val;     // carácter
    int b_val;      // booleano
    char* s_val;    // string
} Value;
```

**Registro de Funciones:**
- Las funciones se registran cuando se declaran
- Cada función almacena su nodo AST para evaluación posterior

**Manejo de Scopes (Shadowing):**
- Usa el sistema de stacks de scopes existente (push_scope/pop_scope)
- Cuando una variable se busca, se busca desde el scope actual hacia arriba
- Las nuevas variables en scopes internos "ocultan" (shadow) las del scope externo

#### Ejemplo de Shadowing:
```ws
x int => 100;
print x;        // Output: 100

{
    x int => 200;
    print x;    // Output: 200 (variable shadowed en este scope)
}

print x;        // Output: 100 (vuelve a la variable del scope exterior)
```

### 3. **Sintaxis Extendida del Lenguaje**

Se han añadido palabras reservadas al lexer:

```c
FUNCTION RETURN IF ELSE WHILE  // palabras reservadas
EQUALS COMMA                     // operadores adicionales
EQ NE LT LE GT GE AND OR NOT   // operadores de comparación y lógica
```

#### Ejemplo de Función:
```ws
function multiply a int, b int int {
    print a;
    print b;
}

x int => 5;
y int => 3;

multiply x y;
```

## Estructura de Ejecución

```
1. Lexer (lexer.l) → Tokens
   ↓
2. Parser (parser.y) → AST
   ↓
3. Intérprete (interpreter.c) → Ejecución
   ↓
4. Output
```

## Ejemplo Completo: Shadowing

```ws
// Scope global: x = 100
x int => 100;
print x;        // Imprime: 100

{
    // Scope 1: x = 200 (oculta el x global)
    x int => 200;
    print x;    // Imprime: 200
    
    {
        // Scope 2: x = 300 (oculta el x del scope 1)
        x int => 300;
        print x;    // Imprime: 300
    }
    
    // Volvemos al scope 1
    print x;    // Imprime: 200
}

// Volvemos al scope global
print x;        // Imprime: 100
```

## Archivos de Prueba

Se incluyen dos archivos de prueba:

### `test_function.ws` - Prueba de funciones
Demuestra:
- Declaración de funciones
- Paso de parámetros
- Ejecución de funciones

### `test_shadowing.ws` - Prueba de shadowing
Demuestra:
- Variables con mismo nombre en diferentes scopes
- Cómo el compilador resuelve identificadores hacia el scope más interno

## Compilación y Ejecución

```bash
# Compilar
make clean && make

# Ejecutar archivo de prueba
./ws_compiler test_shadowing.ws
./ws_compiler test_function.ws
```

## Ventajas de la Implementación

✅ **Separación de fases**: Parsing → AST → Ejecución
✅ **Shadowing correcto**: Las variables locales ocultan las globales
✅ **Funciones de primera clase**: Se pueden declarar y llamar
✅ **Soporte para múltiples tipos**: int, double, char, string, boolean
✅ **Operaciones aritméticas**: +, -, *, /
✅ **Operaciones lógicas**: &&, ||, !, ==, !=, <, >, <=, >=
✅ **Control de flujo**: if/else, while, bloques

## Limitaciones Actuales

- Las funciones no retornan valores explícitamente (el return actual es parcial)
- No hay soporte para arrays
- No hay recursión (aún)
- No hay funciones predefinidas (como strlen, etc.)

## Mejoras Futuras

1. Implementar retorno de valores en funciones
2. Añadir recursión
3. Implementar arrays
4. Añadir funciones predefinidas
5. Optimización del AST
6. Generación de código intermedio (bytecode)
