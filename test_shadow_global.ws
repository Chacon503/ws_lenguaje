// Test shadowing global variables - simulated
x int => 5;
global int => 5;
local int => 100;
print global;
print local;
