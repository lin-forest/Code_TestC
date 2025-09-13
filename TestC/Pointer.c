#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;

    printf("Value of a = %d\n", a);
    printf("Address of a = %p\n", &a);
    printf("Pointer p points to = %d\n", *p);

    *p = 20; // change value using pointer
    printf("New value of a = %d\n", a);

    return 0;
}
