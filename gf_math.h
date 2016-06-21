#pragma once

/*  Unsigned byte typdef */
typedef unsigned char ubyte_t;

/* Field polynomial = x^8 + x^4 + x^3 + x  + 1 */
#define FIELD_POLY (0x1b)

/**
 * Print a number in binary representation to stdout
 */
void printf_bin(ubyte_t dec);

/**
 * Add two polynomials in GF(2^8)
 */
ubyte_t gf_add(ubyte_t a, ubyte_t b);

/**
 * Multiply two polynomials in GF(2^8), using the
 * LSB first algorithm
 */
ubyte_t gf_multiply(ubyte_t a, ubyte_t b);

/*
 * Divide two polynomials (b / a) in GF(2^8)
 **/
void gf_divide(ubyte_t a, ubyte_t b, ubyte_t *q, ubyte_t *r, ubyte_t field_poly);

/*
 * Find multiplicative inverse of a number in GF(2^8)
 * using the Extended Euclid Algorithm. That is, given:
 *   A(x), B(X)
 * Find u(x), w(x) such that:
 *   GCD( A(x), B(x) ) = u(x)A(x) + w(x)B(x)
 * Returns only the multiplicative inverse of A(x)
 */
ubyte_t gf_inverse(ubyte_t a, ubyte_t b);

