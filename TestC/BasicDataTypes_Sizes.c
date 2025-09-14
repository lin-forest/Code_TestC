#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("sizeof(char) = %lu\n", sizeof(char));
    printf("sizeof(int) = %lu\n", sizeof(int));
    printf("sizeof(float) = %lu\n", sizeof(float));
    printf("sizeof(double) = %lu\n", sizeof(double));
    printf("uint32_t max = %u\n", UINT32_MAX);
    return 0;
}
// This program prints the sizes of basic data types and the maximum value of uint32_t.