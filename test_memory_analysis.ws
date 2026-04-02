// ============================================
// PRUEBA 2: ANÁLISIS DE MEMORIA
// ¿Qué sucede con la dirección de memoria (offset) de una variable cuando el ámbito se cierra?
// ============================================

x int => 100;
print x;

{
    // Scope 1: x = 200 (variable local con offset diferente)
    x int => 200;
    print x;
    // Cuando se cierra este scope, el x local (offset 1) se libera
}

// Volvemos al scope global: x = 100 (offset 0)
print x;
