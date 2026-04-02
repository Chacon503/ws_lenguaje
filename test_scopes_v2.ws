// Test de scopes mejorado: 3 niveles de anidamiento
// Cada nivel declara su propia variable x
x int => 111;
print x;

{
    x int => 222;
    print x;
    
    {
        x int => 333;
        print x;
    }
    
    print x;
}

print x;
