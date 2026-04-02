// Test 2: Variable shadowing - misma variable en diferentes scopes
x int => 100;
print x;

{
    x int => 200;
    print x;
    
    {
        x int => 300;
        print x;
    }
    
    print x;
}

print x;
