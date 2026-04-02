#!/bin/bash

# Test runner for WS Compiler
# Runs all .ws test files and reports results

COMPILER="./ws_compiler"
TEST_DIR="."

if [ ! -f "$COMPILER" ]; then
    echo "Error: Compiler not found at $COMPILER"
    exit 1
fi

if [ ! -d "$TEST_DIR" ]; then
    echo "Error: Test directory not found at $TEST_DIR"
    exit 1
fi

echo "================================"
echo "WS Compiler Test Suite"
echo "================================"
echo ""

passed=0
failed=0
total=0

for test_file in "$TEST_DIR"/test_*.ws; do
    if [ -f "$test_file" ]; then
        test_name=$(basename "$test_file")
        total=$((total + 1))
        
        echo -n "Running $test_name ... "
        
        # Run the compiler and capture output
        output=$("$COMPILER" "$test_file" 2>&1)
        exit_code=$?
        
        # Check if it succeeded (exit code 0)
        if [ $exit_code -eq 0 ]; then
            echo "✓ PASS"
            passed=$((passed + 1))
            # Uncomment to see output:
            # echo "  Output:"
            # echo "$output" | sed 's/^/    /'
        else
            echo "✗ FAIL"
            failed=$((failed + 1))
            echo "  Output:"
            echo "$output" | sed 's/^/    /'
        fi
    fi
done

echo ""
echo "================================"
echo "Test Results: $passed/$total passed"
echo "================================"

if [ $failed -eq 0 ]; then
    exit 0
else
    exit 1
fi
