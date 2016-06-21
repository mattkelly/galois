#pragma once

#include <stdint.h>

/* Field polynomial = x^8 + x^4 + x^3 + x  + 1 */
#define FIELD_POLY (0x1b)

/**
 * Print a number in binary representation to stdout
 */
void printf_bin(uint8_t dec);

/**
 * Add two polynomials in GF(2^8)
 */
uint8_t gf_add(uint8_t a, uint8_t b);

/**
 * Multiply two polynomials in GF(2^8), using the
 * LSB first algorithm
 */
uint8_t gf_multiply(uint8_t a, uint8_t b);

/**
 * Multiply polynomial a to the b-th power in GF(2^8)
 */
uint8_t gf_pow(uint8_t a, uint8_t b);

/*
 * Divide two polynomials (b / a) in GF(2^8)
 */
void gf_divide(uint8_t a, uint8_t b, uint8_t *q, uint8_t *r, uint8_t field_poly);

/*
 * Find multiplicative inverse of a number in GF(2^8)
 * using the Extended Euclid Algorithm. That is, given:
 *   A(x), B(X)
 * Find u(x), w(x) such that:
 *   GCD(A(x), B(x)) = u(x)A(x) + w(x)B(x)
 * Returns only the multiplicative inverse of A(x)
 */
uint8_t gf_inverse(uint8_t a, uint8_t b);

