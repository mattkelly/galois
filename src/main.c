#include "gf_math.h"

#include <stdio.h>

/*
 * Run tests on gf_math lib
 */
int main()
{
    uint8_t z;

    z = gf_pow(0x0C, 10);
    printf("pow(0xC, 10) = ");
    printf_bin(z);
    printf("\n");

    z = gf_multiply(0x53, 0xCA);
    printf("0x53 * 0xCA = ");
    printf_bin(z);
    printf("\n");

    printf("z = ");
    printf_bin(z);
    printf("\n");
}

