// Test scopes with 3 levels of nesting
x int => x;
{
    x int => x;
    {
        x int => x;
        print x; 
    }
    print x; 
} 
print x; 