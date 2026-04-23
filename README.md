# WS Language — Compilador / Intérprete

WS es un lenguaje de programación interpretado con **tipado estático**, diseñado para aprender los fundamentos de construcción de compiladores usando Flex (análisis léxico), Bison (análisis sintáctico) y un intérprete de árbol AST en C.

---

## Índice

1. [Arquitectura del proyecto](#1-arquitectura-del-proyecto)
2. [Archivos fuente](#2-archivos-fuente)
3. [Pipeline de compilación](#3-pipeline-de-compilación)
4. [Sintaxis del lenguaje WS](#4-sintaxis-del-lenguaje-ws)
   - [Tipos de datos](#41-tipos-de-datos)
   - [Declaración de variables](#42-declaración-de-variables)
   - [Reasignación de variables](#43-reasignación-de-variables)
   - [Operadores](#44-operadores)
   - [Print](#45-print)
   - [Bloques y scopes](#46-bloques-y-scopes)
   - [Condicional if / else](#47-condicional-if--else)
   - [Bucle while](#48-bucle-while)
   - [Funciones](#49-funciones)
   - [Comentarios](#410-comentarios)
5. [Sistema de scopes y shadowing](#5-sistema-de-scopes-y-shadowing)
6. [Árbol AST — estructura interna](#6-árbol-ast--estructura-interna)
7. [Compilación y uso](#7-compilación-y-uso)
8. [Ejemplos completos](#8-ejemplos-completos)
9. [Manejo de errores](#9-manejo-de-errores)

---

## 1. Arquitectura del proyecto

```
lexer.l        →  flex   →  lex.yy.c         (analizador léxico)
parser.y       →  bison  →  parser.tab.c/h   (analizador sintáctico + AST)
ast.c / ast.h                                 (nodos del árbol AST)
symbols.c / symbols.h                         (tabla de símbolos por scopes)
interpreter.c / interpreter.h                 (intérprete del AST)
parser_helper.c / parser_helper.h             (utilidades de asignación de valores)
Makefile                                      (sistema de construcción)
```

### Flujo de ejecución

```
archivo.ws
    │
    ▼
[Lexer — lexer.l]
    Convierte el texto fuente en tokens (IDENTIFIER, NUMBER, IF, WHILE, …)
    │
    ▼
[Parser — parser.y]
    Aplica la gramática LALR(1), construye el AST y lo almacena en root_ast
    │
    ▼
[Intérprete — interpreter.c]
    Recorre el AST recursivamente y ejecuta cada nodo
    │
    ▼
Salida estándar
```

---

## 2. Archivos fuente

| Archivo | Descripción |
|---------|-------------|
| `lexer.l` | Reglas Flex: define tokens, palabras reservadas, literales y operadores |
| `parser.y` | Gramática Bison: reglas sintácticas, construcción del AST y punto de entrada `main` |
| `ast.h` | Definición de todos los tipos de nodos AST (`ASTNodeType`, `ASTNode`, `BinOpType`, …) |
| `ast.c` | Funciones de creación (`ast_create_*`), impresión (`ast_print`) y liberación (`ast_free`) de nodos |
| `symbols.h` | Definición de `SymbolEntry`, `Scope` y la pila de scopes (`scope_stack`) |
| `symbols.c` | Implementación de `push_scope`, `pop_scope`, `insert_in_current_scope`, `find_entry` |
| `interpreter.h` | Definición de `Value` (valor en tiempo de ejecución), `FunctionDef` e `InterpreterContext` |
| `interpreter.c` | Evaluación de expresiones (`interp_eval_expr`) y ejecución de sentencias (`interp_execute_stmt`) |
| `parser_helper.h` | Declaraciones de utilidades de asignación y print para la tabla de símbolos |
| `parser_helper.c` | Implementación de `assign_numeric_value`, `assign_string_value`, `print_value` |
| `Makefile` | Reglas de construcción: `make`, `make run`, `make run-file`, `make clean` |
| `run_tests.sh` | Script que ejecuta todos los archivos `test_*.ws` y reporta resultados |
| `funciones.ws` | Ejemplo principal: funciones, recursión, while, if/else |

---

## 3. Pipeline de compilación

### Fase 1 — Análisis léxico (Flex)

`lexer.l` define expresiones regulares que transforman el texto fuente en una secuencia de **tokens**. Los tokens relevantes son:

| Token | Patrón | Descripción |
|-------|--------|-------------|
| `IDENTIFIER` | `[a-zA-Z_][a-zA-Z0-9_]*` | Nombre de variable o función |
| `NUMBER` | `[0-9]+` | Literal entero |
| `DOUBLE_LITERAL` | `[0-9]*\.[0-9]+` | Literal flotante |
| `STRING_LITERAL` | `"..."` | Cadena de texto |
| `CHAR_LITERAL` | `'c'` | Carácter individual |
| `BOOL_LITERAL` | `true` / `false` | Literal booleano |
| `IF`, `ELSE`, `WHILE` | — | Palabras reservadas de control |
| `FUNCTION` | `function` / `func` | Declaración de función |
| `RETURN` | `return` | Retorno de función |
| `ARROW` | `=>` | Operador de inicialización |
| `EQUALS` | `=` | Operador de asignación |
| Operadores | `+ - * / == != < <= > >= && \|\| !` | Aritmética, comparación, lógica |

### Fase 2 — Análisis sintáctico (Bison)

`parser.y` contiene una gramática LALR(1) que reconoce la estructura del programa y construye el **AST**. Al finalizar el parsing con éxito, invoca `interp_execute(interp, root_ast)`.

### Fase 3 — Interpretación (AST Walking)

`interpreter.c` recorre el árbol de forma recursiva:
- `interp_eval_expr` evalúa expresiones y devuelve un `Value`.
- `interp_execute_stmt` ejecuta sentencias (declaraciones, asignaciones, if, while, return, etc.).
- `interp_execute` es el punto de entrada que itera sobre las sentencias del programa.

---

## 4. Sintaxis del lenguaje WS

### 4.1 Tipos de datos

| Tipo | Descripción | Ejemplo de literal |
|------|-------------|-------------------|
| `int` | Entero con signo | `42` |
| `double` | Punto flotante de doble precisión | `3.14` |
| `char` | Carácter único | `'A'` |
| `string` | Cadena de texto | `"Hola WS"` |
| `boolean` | Valor lógico | `true` / `false` |

---

### 4.2 Declaración de variables

```
nombre  tipo  =>  expresión;
```

```ws
edad      int     => 22;
precio    double  => 19.99;
saludo    string  => "Hola WS";
inicial   char    => 'W';
activo    boolean => true;
resultado int     => 3 + 4 * 2;
```

- El operador `=>` inicializa la variable con el valor de la expresión de la derecha.
- La variable queda en el **scope actual** y no puede ser redeclarada en el mismo scope.

---

### 4.3 Reasignación de variables

```
nombre  =  expresión;
```

```ws
x int => 5;
x = x + 1;    // x ahora vale 6
```

- Solo se puede reasignar una variable ya declarada (en cualquier scope visible).
- No se escribe el tipo en la reasignación.

---

### 4.4 Operadores

#### Aritméticos

| Operador | Descripción | Ejemplo |
|----------|-------------|---------|
| `+` | Suma | `a + b` |
| `-` | Resta | `a - b` |
| `*` | Multiplicación | `a * b` |
| `/` | División | `a / b` |
| `-` (unario) | Negación | `-a` |

#### Comparación

| Operador | Descripción |
|----------|-------------|
| `==` | Igual |
| `!=` | Distinto |
| `<` | Menor que |
| `<=` | Menor o igual |
| `>` | Mayor que |
| `>=` | Mayor o igual |

#### Lógicos

| Operador | Descripción |
|----------|-------------|
| `&&` | AND lógico |
| `\|\|` | OR lógico |
| `!` | NOT lógico |

#### Precedencia (de menor a mayor)

```
||  →  &&  →  == !=  →  < <= > >=  →  + -  →  * /  →  ! - (unario)
```

---

### 4.5 Print

Imprime el valor de una variable o expresión en la salida estándar:

```ws
print variable;
print expresión;
print "texto literal";
```

```ws
x int => 42;
print x;           // imprime: 42
print x * 2;       // imprime: 84
print "OK";        // imprime: OK
```

Formato de salida por tipo:

| Tipo | Formato |
|------|---------|
| `int` | `42` |
| `double` | `3.14` (sin ceros innecesarios, usando `%g`) |
| `char` | `'A'` |
| `string` | `Hola WS` |
| `boolean` | `true` / `false` |

---

### 4.6 Bloques y scopes

Un bloque es una secuencia de sentencias entre llaves `{ }`. Crea un nuevo **scope**:

```ws
x int => 10;

{
    y int => 20;    // y solo existe dentro de este bloque
    print x;        // puede acceder a x del scope externo
    print y;
}

// print y;  ← ERROR: y no existe aquí
print x;            // x sigue existiendo
```

---

### 4.7 Condicional if / else

```
if ( condición ) bloque
if ( condición ) bloque else bloque
```

```ws
x int => 7;

if (x > 5) {
    print 1;
} else {
    print 0;
}
```

- La condición puede ser cualquier expresión (valor distinto de cero = verdadero).
- La cláusula `else` es opcional.

---

### 4.8 Bucle while

```
while ( condición ) bloque
```

```ws
i int => 0;

while (i < 5) {
    print i;
    i = i + 1;
}
```

- Repite el bloque mientras la condición sea verdadera (distinta de cero).
- Si hay un `return` dentro, el bucle se interrumpe.

---

### 4.9 Funciones

#### Declaración

```
function nombre ( parámetros ) tipo_retorno {
    sentencias
    return expresión;
}
```

Los parámetros tienen la forma `nombre tipo` separados por comas:

```ws
function suma(a int, b int) int {
    return a + b;
}

function factorial(n int) int {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
```

#### Llamada

```ws
resultado int => suma(3, 4);       // como inicializador
print factorial(5);                // como expresión directa
```

- Los argumentos se evalúan en el scope del llamador.
- Cada llamada crea un nuevo scope para los parámetros.
- Las funciones pueden ser recursivas.
- Se pueden definir **antes o después** de su uso (el intérprete registra las funciones en un primer recorrido implícito: se declaran al ejecutarse la sentencia de declaración, por lo que deben aparecer antes de la primera llamada).

---

### 4.10 Comentarios

```ws
// Comentario de una línea

/* Comentario
   de múltiples líneas */
```

---

## 5. Sistema de scopes y shadowing

La tabla de símbolos está implementada como una **pila de scopes** (`Scope* scope_stack`). Cada scope es una lista enlazada de `SymbolEntry`.

```
scope_stack
    │
    ▼
[ Scope nivel 2 ] → variable_local → …
    │  next
    ▼
[ Scope nivel 1 ] → variable_funcion → …
    │  next
    ▼
[ Scope nivel 0 ] → variable_global → …
    │  next
    ▼
  NULL
```

**Reglas:**
- `push_scope()` se llama al entrar a un bloque o función.
- `pop_scope()` se llama al salir, liberando todas las variables del scope.
- `insert_in_current_scope(nombre, tipo, linea)` declara una variable solo en el scope más interno. Retorna `-1` si ya existe en ese scope.
- `find_entry(nombre)` busca desde el scope más interno hacia el global. Devuelve la primera ocurrencia.

**Shadowing:** una variable interna con el mismo nombre que una externa la "oculta" dentro de su scope, sin modificarla:

```ws
x int => 100;
{
    x int => 200;   // shadowing: x local oculta x global
    print x;        // 200
}
print x;            // 100 (x global no fue modificada)
```

---

## 6. Árbol AST — estructura interna

Todos los nodos del árbol comparten la estructura `ASTNode`:

```c
typedef struct ASTNode {
    ASTNodeType node_type;   // tipo de nodo
    int         line_number; // línea en el fuente
    union { ... } data;      // datos específicos del tipo de nodo
} ASTNode;
```

### Tipos de nodos (`ASTNodeType`)

| Nodo | Descripción | Campos relevantes |
|------|-------------|-------------------|
| `NODE_PROGRAM` | Raíz del programa | `block.statements[]`, `block.statement_count` |
| `NODE_BLOCK` | Bloque `{ }` | `block.statements[]`, `block.statement_count` |
| `NODE_VAR_DECL` | Declaración `nombre tipo => expr` | `var_decl.name`, `.type`, `.initializer` |
| `NODE_VAR_ASSIGN` | Asignación `nombre = expr` | `var_assign.name`, `.value` |
| `NODE_PRINT` | Sentencia `print` | `print_stmt.expr` |
| `NODE_FUNC_DECL` | Declaración de función | `func_decl.name`, `.params[]`, `.param_count`, `.return_type`, `.body` |
| `NODE_FUNC_CALL` | Llamada a función | `func_call.name`, `.args[]`, `.arg_count` |
| `NODE_IF` | Condicional | `if_stmt.condition`, `.then_branch`, `.else_branch` |
| `NODE_WHILE` | Bucle while | `while_stmt.condition`, `.body` |
| `NODE_RETURN` | Sentencia return | `return_stmt.value` |
| `NODE_BINOP` | Operación binaria | `binop.op`, `.left`, `.right` |
| `NODE_UNARY` | Operación unaria | `unary.op`, `.operand` |
| `NODE_IDENTIFIER` | Variable | `identifier.name` |
| `NODE_LITERAL` | Valor literal | `literal.type`, `.value` |
| `NODE_PARAM` | Parámetro de función | `param.name`, `.type` |

### Valores en tiempo de ejecución (`Value`)

```c
typedef struct {
    DataType type;   // TYPE_INT, TYPE_DOUBLE, TYPE_CHAR, TYPE_STRING, TYPE_BOOL
    int      i_val;
    double   d_val;
    char     c_val;
    int      b_val;
    char*    s_val;
} Value;
```

El campo `type` es fundamental: permite que `to_double(val)` lea el campo correcto según el tipo real del valor, evitando lecturas incorrectas de memoria.

---

## 7. Compilación y uso

### Requisitos

- `gcc`
- `flex`
- `bison`
- `make`

### Construir el compilador

```bash
make
```

Genera el binario `ws_compiler` en el directorio actual.

### Ejecutar un programa WS

```bash
./ws_compiler archivo.ws
```

### Usar `make run` (ejecuta `funciones.ws`)

```bash
make run
```

### Ejecutar un archivo personalizado

```bash
make run-file FILE=mi_programa.ws
```

### Limpiar archivos generados

```bash
make clean
```

Elimina `ws_compiler`, `lex.yy.c`, `parser.tab.c` y `parser.tab.h`.

### Ejecutar todos los tests

```bash
bash run_tests.sh
```

---

## 8. Ejemplos completos

### Ejemplo 1 — Tipos básicos

```ws
edad      int     => 22;
precio    double  => 19.99;
saludo    string  => "Hola WS";
inicial   char    => 'W';
activo    boolean => true;

print edad;      // 22
print precio;    // 19.99
print saludo;    // Hola WS
print inicial;   // 'W'
print activo;    // true
```

### Ejemplo 2 — Operaciones y expresiones

```ws
a int => 10;
b int => 3;

suma        int => a + b;
diferencia  int => a - b;
producto    int => a * b;
cociente    int => a / b;

print suma;        // 13
print diferencia;  // 7
print producto;    // 30
print cociente;    // 3
```

### Ejemplo 3 — Condicional

```ws
nota int => 75;

if (nota >= 60) {
    print 1;   // aprobado
} else {
    print 0;   // reprobado
}
```

### Ejemplo 4 — Bucle while

```ws
contador int => 1;

while (contador <= 5) {
    print contador;
    contador = contador + 1;
}
// imprime 1, 2, 3, 4, 5
```

### Ejemplo 5 — Función simple

```ws
function cuadrado(n int) int {
    return n * n;
}

x int => cuadrado(7);
print x;   // 49
```

### Ejemplo 6 — Función recursiva (factorial)

```ws
function factorial(n int) int {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

print factorial(5);   // 120
print factorial(10);  // 3628800
```

### Ejemplo 7 — Shadowing de variables

```ws
x int => 100;
print x;   // 100

{
    x int => 200;
    print x;   // 200

    {
        x int => 300;
        print x;   // 300
    }

    print x;   // 200
}

print x;   // 100
```

### Ejemplo 8 — Programa completo (`funciones.ws`)

```ws
function factorial(n int) int {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

function suma(a int, b int) int {
    return a + b;
}

x int => 5;
y int => 3;

fact      int => factorial(x);
resultado int => suma(x, y);

print fact;       // 120
print resultado;  // 8

i int => 0;
while (i < 3) {
    print i;
    i = i + 1;
}
// imprime 0, 1, 2

if (resultado > 10) {
    print 999;
} else {
    print 111;   // imprime 111 (8 no es > 10)
}
```

---

## 9. Manejo de errores

El compilador reporta errores con el formato:

```
[WS ERROR] Line N: mensaje
```

### Errores del parser (sintácticos)

```
[WS ERROR] Line 5: syntax error
```

Se producen cuando el código no sigue la gramática definida en `parser.y`.

### Errores del intérprete (semánticos / en tiempo de ejecución)

| Error | Causa |
|-------|-------|
| `Undefined variable 'x'` | Se usa una variable no declarada |
| `Undefined function 'f'` | Se llama a una función no declarada |
| `Variable 'x' already declared in this scope` | Redeclaración en el mismo scope |
| `Function 'f' expects N arguments, got M` | Número incorrecto de argumentos |
| `Division by zero` | División por cero en tiempo de ejecución |
| `Out of memory` | Sin memoria para asignar un nodo AST o entrada en tabla |
