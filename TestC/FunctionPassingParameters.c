#include <stdio.h>

void setValue(int *p, int val) {
    *p = val; // 改变主函数变量
}

int main(void) {
    int data = 0;
    setValue(&data, 42);
    printf("data=%d\n", data);
    return 0;
}
// GitHub Copilot: 这是一个演示如何通过指针传递参数并修改主函数中变量值的C语言程序。让我为您解释每一部分：

// 1. `#include <stdio.h>` - 这是一个预处理指令，引入标准输入输出库，使我们可以使用`printf`等函数。

// 2. `void setValue(int *p, int val)` - 这是一个函数定义，接受一个整型指针和一个整型值作为参数。

// 3. `*p = val;` - 通过指针修改主函数中的变量值。

// 4. `int main(void)` - 程序的主函数，程序从这里开始执行。

// 5. `int data = 0;` - 定义一个整型变量`data`并初始化为0。

// 6. `setValue(&data, 42);` - 调用`setValue`函数，传递`data`的地址和新值42。

// 7. `printf("data=%d\n", data);` - 打印修改后的`data`值。

// 这个程序展示了如何通过指针参数来修改主函数中的变量值。当程序运行时，会输出`data=42`，表明变量`data`的值已经被成功修改。