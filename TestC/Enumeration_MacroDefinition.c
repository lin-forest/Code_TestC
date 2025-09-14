#include <stdio.h>

#define LED_ON  1
#define LED_OFF 0

typedef enum { FORWARD, BACKWARD } MotorDir;

int main(void) {
    int led = LED_ON;
    MotorDir dir = FORWARD;
    printf("led=%d, dir=%d\n", led, dir);
    return 0;
}
// GitHub Copilot: 这是一个简单的C语言程序，演示了如何使用宏定义和枚举类型。让我为您解释每一部分：

// 1. `#include <stdio.h>` - 这是一个预处理指令，引入标准输入输出库，使我们可以使用`printf`等函数。

// 2. `#define LED_ON  1` 和 `#define LED_OFF 0` - 这两个宏定义了LED灯的开关状态。

// 3. `typedef enum { FORWARD, BACKWARD } MotorDir;` - 这是一个枚举类型定义，表示电动机的运动方向。

// 4. `int main(void)` - 程序的主函数，程序从这里开始执行。

// 5. `int led = LED_ON;` - 定义一个整型变量`led`并初始化为`LED_ON`。

// 6. `MotorDir dir = FORWARD;` - 定义一个枚举类型变量`dir`并初始化为`FORWARD`。

// 7. `printf("led=%d, dir=%d\n", led, dir);` - 打印LED状态和电动机方向。

// 这个程序展示了如何使用宏和枚举来提高代码的可读性和可维护性。