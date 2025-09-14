#include <stdio.h>
#include <stdint.h>  // 使用标准整数类型

// 1. 枚举的优势应用场景
// 例子1：定义外设工作模式
enum ADC_Mode {
    ADC_MODE_SINGLE = 0,    // 单次转换模式
    ADC_MODE_CONTINUOUS,    // 连续转换模式
    ADC_MODE_SCAN          // 扫描模式
};

// 例子2：定义GPIO引脚状态
enum GPIO_State {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
};

// 例子3：定义错误码
enum Error_Code {
    ERR_NONE = 0,
    ERR_TIMEOUT = 1,
    ERR_PARAMETER = 2,
    ERR_COMMUNICATION = 3
};

// 2. 结构体的优势应用场景
// 例子1：外设寄存器映射
struct UART_Registers {
    volatile uint32_t DATA;      // 数据寄存器
    volatile uint32_t STATE;     // 状态寄存器
    volatile uint32_t CONTROL;   // 控制寄存器
    volatile uint32_t BAUD;      // 波特率寄存器
};

// 例子2：传感器数据封装
struct Sensor_Data {
    float temperature;    // 温度值
    float humidity;       // 湿度值
    uint32_t timestamp;  // 时间戳
    uint8_t status;      // 状态标志
};

// 例子3：通信协议数据帧
struct Protocol_Frame {
    uint8_t header;      // 帧头 (0xAA)
    uint8_t command;     // 命令字
    uint16_t length;     // 数据长度
    uint8_t data[32];    // 数据缓冲区
    uint8_t checksum;    // 校验和
};

// 模拟设备初始化函数
void initDevice(struct UART_Registers* uart, enum ADC_Mode mode) {
    // 模拟设备初始化
    uart->CONTROL = 0x01;    // 使能UART
    uart->BAUD = 115200;     // 设置波特率
    
    // 使用枚举作为配置参数
    switch(mode) {
        case ADC_MODE_SINGLE:
            printf("配置为单次转换模式\n");
            break;
        case ADC_MODE_CONTINUOUS:
            printf("配置为连续转换模式\n");
            break;
        case ADC_MODE_SCAN:
            printf("配置为扫描模式\n");
            break;
    }
}

int main(void) {
    // 演示结构体用法
    struct Sensor_Data sensor1;
    sensor1.temperature = 25.6f;
    sensor1.humidity = 65.3f;
    sensor1.timestamp = 1234567890;
    sensor1.status = 0x01;
    
    printf("传感器数据：\n");
    printf("温度: %.1f°C\n", sensor1.temperature);
    printf("湿度: %.1f%%\n", sensor1.humidity);
    
    // 演示枚举用法
    enum ADC_Mode currentMode = ADC_MODE_CONTINUOUS;
    struct UART_Registers uart1 = {0};  // 初始化为0
    
    initDevice(&uart1, currentMode);
    
    return 0;
}