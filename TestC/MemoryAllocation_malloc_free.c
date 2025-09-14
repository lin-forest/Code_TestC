#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int) * 3);
    if (p) {
        for (int i = 0; i < 3; i++) p[i] = i * 10;
        for (int i = 0; i < 3; i++) printf("%d ", p[i]);
        free(p);
    }
    return 0;
}
// GitHub Copilot: 这是一个简单的C语言程序，演示了如何使用动态内存分配函数malloc和free。让我为您解释每一部分：

// 1. `#include <stdio.h>` - 这是一个预处理指令，引入标准输入输出库，使我们可以使用`printf`等函数。

// 2. `#include <stdlib.h>` - 这是一个预处理指令，引入标准库，使我们可以使用`malloc`和`free`等函数。

// 3. `int main(void)` - 程序的主函数，程序从这里开始执行。

// 4. `int *p = malloc(sizeof(int) * 3);` - 使用`malloc`动态分配内存，分配足够存储3个整数的空间，并将其首地址赋值给指针`p`。

// 5. `if (p) {` - 检查内存分配是否成功。

// 6. `for (int i = 0; i < 3; i++) p[i] = i * 10;` - 初始化动态分配的内存，将0、10、20分别赋值给`p[0]`、`p[1]`、`p[2]`。

// 7. `for (int i = 0; i < 3; i++) printf("%d ", p[i]);` - 打印动态分配内存中的值。

// 8. `free(p);` - 释放动态分配的内存。

// 这个程序展示了如何使用动态内存分配来管理内存，并在不再需要时释放它。