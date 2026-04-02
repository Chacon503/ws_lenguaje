# Ejemplos Visuales del AST y Ejecución

## 1. Ejemplo Simple: Variable y Print

### Código:
```ws
x int => 42;
print x;
```

### AST Generado:
```
PROGRAM:
  VAR_DECL: x int
    LITERAL: int = 42
  PRINT:
    IDENTIFIER: x
```

### Ejecución:
```
Parsing successful. Executing...

42

[SUCCESS] Program executed successfully.
```

---

## 2. Ejemplo con Shadowing

### Código:
```ws
x int => 100;
print x;

{
    x int => 200;
    print x;
}

print x;
```

### Flujo de Scopes:
```
┌─────────────────────────────┐
│ GLOBAL SCOPE                │
│  x = 100                    │  ← print x; // 100
│                             │
│  ┌───────────────────────┐  │
│  │ SCOPE 1 (BLOCK)       │  │
│  │  x = 200 (shadowing)  │  │ ← print x; // 200
│  │                       │  │
│  └───────────────────────┘  │
│                             │
│ x = 100 (restored)          │  ← print x; // 100
└─────────────────────────────┘
```

### AST Generado:
```
PROGRAM:
  VAR_DECL: x int
    LITERAL: int = 100
  PRINT:
    IDENTIFIER: x
  BLOCK:
    VAR_DECL: x int          ← Crea nuevo x en nuevo scope
      LITERAL: int = 200
    PRINT:
      IDENTIFIER: x          ← Encuentra el x del scope actual (200)
  PRINT:
    IDENTIFIER: x            ← Encuentra el x global (100)
```

### Ejecución Paso a Paso:
```
1. Crear scope global
2. Declarar x = 100 en scope global
3. print x → busca x en scope actual → encuentra 100
4. Entrar a bloque → push_scope() → crear scope 1
5. Declarar x = 200 en scope 1
6. print x → busca x en scope 1 → encuentra 200
7. Salir del bloque → pop_scope() → eliminar scope 1
8. print x → busca x en scope global → encuentra 100
```

### Output:
```
100
200
100
```

---

## 3. Ejemplo con Múltiples Niveles de Shadowing

### Código:
```ws
x int => 1;
print x;

{
    x int => 2;
    print x;
    
    {
        x int => 3;
        print x;
    }
    
    print x;
}

print x;
```

### Visualización de Stack de Scopes:

```
INICIO: GLOBAL(x=1)
         ├─ print x → 1

ENTER BLOCK 1:
         SCOPE1(x=2)
         ↓
         GLOBAL(x=1)
         ├─ print x → 2

ENTER BLOCK 2:
         SCOPE2(x=3)
         ↓
         SCOPE1(x=2)
         ↓
         GLOBAL(x=1)
         ├─ print x → 3

EXIT BLOCK 2:
         SCOPE1(x=2)
         ↓
         GLOBAL(x=1)
         ├─ print x → 2

EXIT BLOCK 1:
         GLOBAL(x=1)
         ├─ print x → 1
```

### Output:
```
1
2
3
2
1
```

---

## 4. Ejemplo con Funciones (Plannificado)

### Código:
```ws
function sum a int, b int int {
    c int => a + b;
    return c;
}

x int => 5;
y int => 3;

result int => sum x y;
print result;
```

### AST Generado:
```
PROGRAM:
  FUNC_DECL: sum returns int
    PARAM: a int
    PARAM: b int
    BLOCK:
      VAR_DECL: c int
        BINOP: PLUS
          IDENTIFIER: a
          IDENTIFIER: b
      RETURN:
        IDENTIFIER: c
  VAR_DECL: x int
    LITERAL: int = 5
  VAR_DECL: y int
    LITERAL: int = 3
  VAR_DECL: result int
    FUNC_CALL: sum
      IDENTIFIER: x
      IDENTIFIER: y
  PRINT:
    IDENTIFIER: result
```

### Ejecución:
```
1. Registrar función sum
2. Declarar x = 5
3. Declarar y = 3
4. Declarar result (sin inicializar)
5. Evaluar FUNC_CALL sum(x, y):
   - push_scope() → crear scope de función
   - Vincular a = 5, b = 3
   - Evaluar c = a + b = 8
   - Evaluar return c → devuelve 8
   - pop_scope() → eliminar scope de función
6. result = 8
7. print result → 8
```

---

## 5. Ejemplo con Operaciones Binarias

### Código:
```ws
a int => 10;
b int => 3;
result int => a + b * 2;
print result;
```

### AST (mostrando precedencia):
```
PROGRAM:
  VAR_DECL: a int
    LITERAL: int = 10
  VAR_DECL: b int
    LITERAL: int = 3
  VAR_DECL: result int
    BINOP: PLUS
      IDENTIFIER: a
      BINOP: MUL              ← Se evalúa primero (precedencia)
        IDENTIFIER: b
        LITERAL: int = 2
  PRINT:
    IDENTIFIER: result
```

### Evaluación:
```
1. a = 10
2. b = 3
3. Evaluar: a + (b * 2)
   - Evaluar b * 2 = 6
   - Evaluar a + 6 = 16
4. result = 16
5. print result → 16
```

---

## 6. Estructura de un Nodo de Declaración de Variable

### En Código:
```ws
suma int => 10 + 5;
```

### En Memoria (Estructura AST):
```c
ASTNode {
    node_type: NODE_VAR_DECL
    line_number: 1
    data: {
        var_decl: {
            name: "suma"
            type: TYPE_INT
            initializer: ASTNode {
                node_type: NODE_BINOP
                data: {
                    binop: {
                        op: BINOP_PLUS
                        left: ASTNode { NODE_LITERAL, value: 10 }
                        right: ASTNode { NODE_LITERAL, value: 5 }
                    }
                }
            }
        }
    }
}
```

### Tabla de Símbolos (después de la ejecución):
```
┌─────────────┬──────┬──────┬───────┐
│ Name        │ Type │ Line │ Value │
├─────────────┼──────┼──────┼───────┤
│ suma        │ int  │  1   │  15   │
└─────────────┴──────┴──────┴───────┘
```

---

## 7. Búsqueda de Variables en Shadowing

### Código y Búsqueda:
```ws
x int => 100;           // GLOBAL: x = 100
{
    x int => 200;       // SCOPE1: x = 200
    {
        x int => 300;   // SCOPE2: x = 300
        print x;        // ← Búsqueda: SCOPE2 → SCOPE1 → GLOBAL
    }
}
```

### Algoritmo de Búsqueda:
```
find_entry("x"):
    current_scope = scope_stack (SCOPE2)
    
    Buscar en SCOPE2:
        ✓ Encontrado: x = 300
        Retorna 300
    
    // Si no estuviera en SCOPE2:
    // current_scope = scope_stack->next (SCOPE1)
    // Buscar en SCOPE1:
    //     ✓ Encontrado: x = 200
    //     Retorna 200
    //
    // Si no estuviera en SCOPE1:
    // current_scope = scope_stack->next (GLOBAL)
    // Buscar en GLOBAL:
    //     ✓ Encontrado: x = 100
    //     Retorna 100
```

Output: `300`

---

## 8. Comparación: Sin Shadowing vs Con Shadowing

### Sin Shadowing (no permitir redeclaración):
```
Error: Variable 'x' already declared
```

### Con Shadowing (implementado):
```
x = 100 (global)
x = 200 (local) ← oculta la global
x = 100 (vuelve a global)
```

**Nuestro compilador usa SHADOWING correcto.**

---

## 9. Flujo Completo: De Código a Ejecución

```
┌──────────────────────┐
│  test_shadowing.ws   │
│  x int => 100;       │
│  print x;            │
│  {                   │
│    x int => 200;     │
│    print x;          │
│  }                   │
│  print x;            │
└──────────────────────┘
         ↓
    [LEXER]
    Tokeniza el código
         ↓
    Tokens:
    IDENTIFIER(x), INT_TYPE, ARROW, NUMBER(100), SEMICOLON
    PRINT, IDENTIFIER(x), SEMICOLON
    LBRACE, IDENTIFIER(x), INT_TYPE, ...
         ↓
    [PARSER]
    Construye el AST
         ↓
    AST:
    PROGRAM[
        VAR_DECL(x, 100),
        PRINT(x),
        BLOCK[
            VAR_DECL(x, 200),
            PRINT(x)
        ],
        PRINT(x)
    ]
         ↓
    [INTERPRETER]
    Ejecuta el AST
         ↓
    Ejecución paso a paso:
    1. Scope global: x = 100
    2. print x → 100
    3. push_scope() → Scope local
    4. x = 200 (shadowing)
    5. print x → 200
    6. pop_scope() → Volver a global
    7. print x → 100
         ↓
    OUTPUT:
    100
    200
    100
```

---

## 10. Ejemplo de Conversión de Tipos

### Código:
```ws
x int => 5;
y double => 2.5;
resultado double => x + y;
print resultado;
```

### Proceso de Evaluación:
```
binop PLUS:
    left = IDENTIFIER(x) → valor: 5 (int)
    right = IDENTIFIER(y) → valor: 2.5 (double)
    
    Convertir a double:
        left_double = 5.0
        right_double = 2.5
    
    Resultado: 5.0 + 2.5 = 7.5
```

Output: `7.500000`

---

## Visualización de Tipos de Nodos

```
┌─────────────────────────────────────────────────┐
│             TIPOS DE NODOS AST                  │
├─────────────────────────────────────────────────┤
│ CONTROL          DATOS          OPERACIONES     │
│ ─────────        ─────           ────────       │
│ NODE_IF          NODE_LITERAL    NODE_BINOP    │
│ NODE_WHILE       NODE_IDENTIFIER NODE_UNARY    │
│ NODE_BLOCK       NODE_PARAM      NODE_EXPR_STMT│
│ NODE_RETURN      NODE_VAR_DECL                 │
│ NODE_FUNC_DECL   NODE_VAR_ASSIGN               │
│ NODE_FUNC_CALL   NODE_PRINT                    │
│                  NODE_PROGRAM                  │
└─────────────────────────────────────────────────┘
```

---

Este documento muestra visualmente cómo funciona el AST y el intérprete en diferentes escenarios.
