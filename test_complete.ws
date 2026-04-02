// Test 3: Combinación de funciones y shadowing
x int => 10;
print x;

{
    x int => 20;
    print x;
    
    {
        x int => 30;
        print x;
    }
    
    print x;
}

print x;
