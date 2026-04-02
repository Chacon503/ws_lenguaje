// ============================================
// EJEMPLO COMPLETO: AST con Funciones y Shadowing
// ============================================

// Variables globales
suma int => 0;
multiplicacion int => 0;
print suma;
print multiplicacion;

// Bloques con shadowing
{
    // Shadowing: suma local oculta la global
    suma int => 50;
    print suma;
    
    {
        // Shadowing: suma local oculta la anterior
        suma int => 100;
        print suma;
        
        // multiplicacion sigue siendo global (no fue redeclarada)
        multiplicacion = 200;
        print multiplicacion;
    }
    
    // Volvemos al nivel anterior de shadowing
    print suma;
}

// Volvemos a las variables globales
print suma;
print multiplicacion;
