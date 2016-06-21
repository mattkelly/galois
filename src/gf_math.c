#include "gf_math.h"

#include <stdio.h>

void printf_bin(uint8_t dec)
{
    uint8_t i;
    for (i = 0; i < 8; ++i)
    {
        printf("%u", (dec & 0x80) == 0x80);
        dec <<= 1;
    }
}

uint8_t gf_add(uint8_t a, uint8_t b)
{
    return a ^ b;
}

uint8_t gf_multiply(uint8_t a, uint8_t b)
{
    uint8_t i;
    uint8_t acc = 0x00; // Accumulator
    uint8_t msb; // Current MSB of a

    for (i = 0; i < 8; ++i)
    {
        // If LSB of b is 1, add a to accumulator
        if (b & 0x01)
        {
            acc ^= a;
        }

        // Store MSB of a, then shift it off
        msb = a & 0x80;
        a <<= 1;

        // If MSB of a was 1, add field polynomial to a
        if (msb)
        {
            a = gf_add(a, FIELD_POLY);
        }

        // Advance to next bit of b
        b >>= 1;
    }

    return acc;
}

uint8_t gf_pow(uint8_t a, uint8_t b)
{
    if (0 == b)
    {
        return 1;
    }
    else if (1 == b)
    {
        return a;
    }

    uint8_t z = a;
    for (int i = 0; i < b - 1; ++i)
    {
        z = gf_multiply(z, a);
    }

    return z;
}

void gf_divide(uint8_t a, uint8_t b, uint8_t *q, uint8_t *r, uint8_t field_poly)
{
    uint8_t i = 0;
    uint8_t j;
    uint8_t quotient = 0x00; // Quotient
    uint8_t rem = b; // Remainder
    uint8_t msb_a; // Current MSB of a

    // Perform initial alignment
    msb_a = a & 0x80;
    while (0 == msb_a && i < 8 )
    {
        a <<= 1;
        msb_a = a & 0x80;
        i++;
    }

    // Take care of field polynomial MSB (bit 8)
    if (field_poly)
    {
        quotient |= (1 << (i+1));
        rem ^= (a << 1);
    }

    // Compute for remaining bits after alignment
    // From this point msb_a is always 1
    for (j = 0; j < i+1; ++j)
    {
        if ( (rem << j) & 0x80)
        {
            // Reduce if needed
            quotient |= (1 << (i-j));
            rem ^= a;
        }

        a >>= 1;

    }

    *q = quotient;
    *r = rem;
}

uint8_t gf_inverse(uint8_t a, uint8_t b)
{
    // Map 0x00 to 0x00
    if (a == 0x00)
    {
        return 0x00;
    }

    uint8_t rem[8];
    uint8_t aux[8];
    uint8_t q, r;
    uint8_t i;

    rem[0] = b;
    rem[1] = a;
    aux[0] = 0;
    aux[1] = 1;

    i = 1;
    while (rem[i] > 0x01)
    {
        i++;
        if (i == 2)
        {
            gf_divide(rem[i-1], rem[i-2], &q, &r, 1);
        }
        else
        {
            gf_divide(rem[i-1], rem[i-2], &q, &r, 0);
        }
        rem[i] = r;
        aux[i] = gf_multiply(q, aux[i-1]) ^ aux[i-2];
    }

    // Inverse of A(x) is in current index of aux
    return aux[i];
}

