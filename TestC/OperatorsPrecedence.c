#include <stdio.h>

int main(void) {
    int a = 5, b = 3;
    printf("a + b = %d\n", a + b);
    printf("a & b = %d (按位与)\n", a & b);
    printf("a << 1 = %d (左移)\n", a << 1);
    //0101->1010
    printf("a > b = %d (大于)\n", a > b);
    return 0;
}
