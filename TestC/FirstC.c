// #include <stdio.h>

// int main() {
//     printf("Hello, VS Code!\n");
//     return 0;
// }
// // End of code.

// variables.c


// #include <stdio.h>

// int main() {
//     int a = 10;
//     float b = 3.14;
//     printf("a=%d, b=%.2f\n", a, b);
//     return 0;
// }

#include <stdio.h>

int main() {
    int num;
    printf("Please enter a number: ");
    scanf("%d", &num);

    if (num % 2 == 0)
        printf("Even\n");
    else
        printf("Odd\n");

    return 0;
}
