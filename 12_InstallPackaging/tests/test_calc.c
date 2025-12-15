/**
 * @file test_calc.c
 * @brief Unit tests for calculator library
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "../src/libcalc.h"

#define EPSILON 0.0001

int test_add() {
    assert(fabs(calc_add(2.0, 3.0) - 5.0) < EPSILON);
    assert(fabs(calc_add(-2.0, 3.0) - 1.0) < EPSILON);
    assert(fabs(calc_add(0.0, 0.0) - 0.0) < EPSILON);
    printf("test_add: PASSED\n");
    return 0;
}

int test_subtract() {
    assert(fabs(calc_subtract(5.0, 3.0) - 2.0) < EPSILON);
    assert(fabs(calc_subtract(3.0, 5.0) - (-2.0)) < EPSILON);
    assert(fabs(calc_subtract(0.0, 0.0) - 0.0) < EPSILON);
    printf("test_subtract: PASSED\n");
    return 0;
}

int test_multiply() {
    assert(fabs(calc_multiply(2.0, 3.0) - 6.0) < EPSILON);
    assert(fabs(calc_multiply(-2.0, 3.0) - (-6.0)) < EPSILON);
    assert(fabs(calc_multiply(0.0, 5.0) - 0.0) < EPSILON);
    printf("test_multiply: PASSED\n");
    return 0;
}

int test_divide() {
    assert(fabs(calc_divide(6.0, 3.0) - 2.0) < EPSILON);
    assert(fabs(calc_divide(5.0, 2.0) - 2.5) < EPSILON);
    assert(fabs(calc_divide(1.0, 0.0) - 0.0) < EPSILON); // division by zero
    printf("test_divide: PASSED\n");
    return 0;
}

int test_power() {
    assert(fabs(calc_power(2.0, 3.0) - 8.0) < EPSILON);
    assert(fabs(calc_power(5.0, 0.0) - 1.0) < EPSILON);
    assert(fabs(calc_power(2.0, -1.0) - 0.5) < EPSILON);
    printf("test_power: PASSED\n");
    return 0;
}

int main() {
    printf("Running unit tests...\n");
    
    test_add();
    test_subtract();
    test_multiply();
    test_divide();
    test_power();
    
    printf("\nAll tests passed!\n");
    return 0;
}
