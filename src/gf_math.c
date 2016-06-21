#include "gf_math.h"

#include <stdio.h>

void printf_bin(ubyte_t dec)
{
    ubyte_t i;
    for (i = 0; i <= 7; ++i)
    {
        if ((dec & 0x80) == 0x80)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        dec <<= 1;
    }
}

ubyte_t gf_add(ubyte_t a, ubyte_t b)
{
    return a ^ b;
}

ubyte_t gf_multiply(ubyte_t a, ubyte_t b)
{
    ubyte_t i;
    ubyte_t acc = 0x00; // Accumulator
    ubyte_t msb; // Current MSB of a

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
        if (1 == msb)
        {
            a ^= FIELD_POLY;
        }

        // Advance to next bit of b
        b >>= 1;
    }

    return acc;
}

void gf_divide(ubyte_t a, ubyte_t b, ubyte_t *q, ubyte_t *r, ubyte_t field_poly)
{
    ubyte_t i = 0;
    ubyte_t j;
    ubyte_t quotient = 0x00; // Quotient
    ubyte_t rem = b; // Remainder
    ubyte_t msb_a; // Current MSB of a

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

ubyte_t gf_inverse(ubyte_t a, ubyte_t b)
{
    // Map 0x00 to 0x00
    if (a == 0x00)
    {
        return 0x00;
    }

    ubyte_t rem[8];
    ubyte_t aux[8];
    ubyte_t q, r;
    ubyte_t i;

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

