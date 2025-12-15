/**
 * @file libcalc.h
 * @brief Simple calculator library
 * @author Mikhail
 * @version 1.0
 * 
 * This library provides basic arithmetic operations.
 */

#ifndef LIBCALC_H
#define LIBCALC_H

/**
 * @brief Add two numbers
 * @param a First operand
 * @param b Second operand
 * @return Sum of a and b
 */
double calc_add(double a, double b);

/**
 * @brief Subtract two numbers
 * @param a First operand
 * @param b Second operand
 * @return Difference (a - b)
 */
double calc_subtract(double a, double b);

/**
 * @brief Multiply two numbers
 * @param a First operand
 * @param b Second operand
 * @return Product of a and b
 */
double calc_multiply(double a, double b);

/**
 * @brief Divide two numbers
 * @param a Numerator
 * @param b Denominator
 * @return Result of a / b
 * @note Returns 0 if b is zero
 */
double calc_divide(double a, double b);

/**
 * @brief Calculate power
 * @param base Base number
 * @param exponent Exponent
 * @return base raised to the power of exponent
 */
double calc_power(double base, double exponent);

#endif /* LIBCALC_H */
