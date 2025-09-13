#include <stdio.h>

// 函数声明
int add(int x, int y);
void printHello();

// 主函数
int main() {
    int c = 5, d = 10;
    printHello();
    printf("Sum = %d\n", add(c, d));
    return 0;
}

// 函数定义
int add(int a, int b) {
    return a + b;
}
void printHello() {
    printf("Hello from function!\n");
}
