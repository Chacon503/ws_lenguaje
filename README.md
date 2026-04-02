# WS Compiler Test Suite

This directory contains comprehensive tests for the WS Compiler, covering function definitions, function calls, and various operators.

## Running Tests

To run all tests at once, use the test runner script:

```bash
bash test/run_tests.sh
```

To run a single test:

```bash
./ws_compiler test/test_name.ws
```

## Test Files

### Basic Functionality

- **test_basic_arithmetic.ws** - Tests all arithmetic operators (+, -, *, /)
- **test_no_params.ws** - Tests function with no parameters
- **test_single_param.ws** - Tests function with one parameter
- **test_two_params.ws** - Tests function with two parameters
- **test_multiple_params.ws** - Tests functions with 3+ parameters

### Advanced Features

- **test_nested_calls.ws** - Tests nested function calls with multiple functions
- **test_complex_expr.ws** - Tests complex expressions with multiple nested operations
- **test_vars_as_args.ws** - Tests passing variables as function arguments
- **test_function_order.ws** - Tests that functions can be defined in any order

### Type Support

- **test_double_functions.ws** - Tests functions with double precision numbers
- **test_mixed_types.ws** - Tests type coercion between int and double
- **test_int_division.ws** - Tests integer division with truncation

## Example Test

```ws
func add([int]x, [int]y) -> [int] {
    return x + y;
}

var: [int] result = add(3, 5);
print result;
```

This test:
1. Defines a function `add` with two integer parameters
2. Creates a variable `result` that calls the function with arguments 3 and 5
3. Prints the result (should output 8)

## Test Results

All 12 tests pass successfully, verifying:
- ✓ Function definitions with various parameter counts
- ✓ Function calls with proper argument passing
- ✓ Parameter binding and scope management
- ✓ Nested function calls
- ✓ Type coercion in function arguments
- ✓ All arithmetic operators (+, -, *, /)
- ✓ Functions defined in any order
