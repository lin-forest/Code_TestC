#include <stdio.h>

struct Motor {
    int speed;
    int direction;
};

int main(void) {
    struct Motor m1 = {100, 1};
    printf("Motor speed=%d dir=%d\n", m1.speed, m1.direction);
    return 0;
}
// GitHub Copilot: 这是一个简单的C语言程序，定义了一个名为`Motor`的结构体，并在`main`函数中创建了该结构体的一个实例。让我为您解释每一部分：

// 1. `#include <stdio.h>` - 这是一个预处理指令，引入标准输入输出库，使我们可以使用`printf`等函数。

// 2. `struct Motor` - 这是一个结构体定义，表示一个电动机的属性。

// 3. `int speed;` 和 `int direction;` - 这两个成员变量分别表示电动机的速度和方向。

// 4. `int main(void)` - 程序的主函数，程序从这里开始执行。

// 5. `struct Motor m1 = {100, 1};` - 创建一个名为`m1`的`Motor`结构体实例，并初始化其成员变量。

// 6. `printf("Motor speed=%d dir=%d\n", m1.speed, m1.direction);` - 打印电动机的速度和方向。

// 这个程序展示了如何定义和使用结构体来组织相关数据。