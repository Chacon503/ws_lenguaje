// ============================================
// PRUEBA 3: PRUEBA DE FUEGO - 3 NIVELES DE ANIDAMIENTO
// Procesa código con 3 niveles de anidamiento y demuestra que
// el compilador siempre elige el valor correcto.
// ============================================

x int => 111;
print x;

{
    x int => 222;
    print x;
    
    {
        x int => 333;
        print x;
        
        {
            x int => 444;
            print x;
        }
        
        print x;
    }
    
    print x;
}

print x;
