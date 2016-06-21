#include "gf_math.h"

#include <stdio.h>

/*
 * Run tests on gf_math lib
 */
int main() {

    ubyte_t a, b, z;

    printf("\n\n--- a^5 ---\n");
    a = 0x0C;
    z = gf_multiply(a, a); // a^2
    z = gf_multiply(z, a); // a^3
    z = gf_multiply(z, a); // a^4
    z = gf_multiply(z, a); // a^5

    printf("\n\nz = ");
    printf_bin(z);

    printf("\n\n--- inv(x^2) ---\n");
    b = 0x04;
    ubyte_t poly = FIELD_POLY;
    ubyte_t b_inv = gf_inverse(b, poly);

    printf("\n\ninv(x^2) = ");
    printf_bin(b_inv);

    printf("\n\ninv(inv(x^2)) = ");
    printf_bin(gf_inverse(b_inv, poly));

    printf("\n\n--- FINAL ---\n");
    z = gf_multiply(a, b_inv);

    printf("\n\na * inv(x^2) = ");
    printf_bin(z);
    printf("\n");
}
