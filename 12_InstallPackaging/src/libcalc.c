/**
 * @file libcalc.c
 * @brief Implementation of calculator library
 */

#include "libcalc.h"
#include <math.h>

double calc_add(double a, double b) {
    return a + b;
}

double calc_subtract(double a, double b) {
    return a - b;
}

double calc_multiply(double a, double b) {
    return a * b;
}

double calc_divide(double a, double b) {
    if (b == 0.0) {
        return 0.0;
    }
    return a / b;
}

double calc_power(double base, double exponent) {
    return pow(base, exponent);
}
