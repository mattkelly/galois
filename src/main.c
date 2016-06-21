#include "gf_math.h"

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

/*
 * Run tests on gf_math lib
 */
int main()
{
    uint8_t z;

    z = gf_pow(0x0C, 0x05);
    printf("pow(0xC, 10) = 0x%02" PRIX8 " = ", z);
    printf_bin(z);
    printf("\n");

    z = gf_multiply(0x53, 0xCA);
    printf("0x53 * 0xCA = 0x%02" PRIX8 " = ", z);
    printf_bin(z);
    printf("\n");

    z = gf_inverse(0x53, FIELD_POLY);
    printf("inv(0x53, 0x1b) = 0x%02" PRIX8 " = ", z);
    printf_bin(z);
    printf("\n");
}

