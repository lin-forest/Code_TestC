// #include <stdio.h>

// int main() {
//     int a = 10;
//     float b = 3.14;
//     double c = 2.71828;
//     char d = 'X';

//     printf("Integer a = %d\n", a);
//     printf("Float b = %.2f\n", b);
//     printf("Double c = %.5lf\n", c);
//     printf("Char d = %c\n", d);

//     return 0;
// }


#include <stdio.h>

int main() {
    char name1[] = "Alice";      // 字符数组方式
    char name2[6] = {'A','l','i','c','e','\0'}; // 显式写出 '\0'

    printf("Name1: %s\n", name1);
    printf("Name2: %s\n", name2);

    return 0;
}
