#include <stdio.h>
#include <stdint.h>

// CAN消息帧结构体定义（标准帧）
#pragma pack(push, 1)  // 确保字节对齐为1，避免填充
typedef struct {
    // 标识符 11位（标准帧）或29位（扩展帧）
    union {
        uint32_t id;           // 完整ID
        struct {
            uint32_t std_id:11;    // 标准帧ID
            uint32_t rtr:1;        // 远程帧标志
            uint32_t ide:1;        // 扩展帧标志
            uint32_t reserved:19;   // 保留位
        } bits;
    } identifier;
    
    uint8_t dlc;          // 数据长度（0-8字节）
    uint8_t data[8];      // 数据字段
} CAN_Frame_t;

// 实际业务数据结构体示例（温度传感器）
typedef struct {
    uint16_t temperature;  // 温度值，放大100倍传输
    uint16_t humidity;     // 湿度值，放大100倍传输
    uint8_t status;       // 状态标志位
} __attribute__((packed)) Sensor_Data_t;

// CAN消息ID定义
#define CAN_ID_TEMP_SENSOR    0x123
#define CAN_ID_MOTOR_CONTROL  0x456

// 函数：打包传感器数据到CAN帧
void packSensorDataToCANFrame(const Sensor_Data_t* sensorData, CAN_Frame_t* canFrame) {
    // 清空CAN帧
    memset(canFrame, 0, sizeof(CAN_Frame_t));
    
    // 设置帧ID和控制位
    canFrame->identifier.bits.std_id = CAN_ID_TEMP_SENSOR;
    canFrame->identifier.bits.rtr = 0;    // 数据帧
    canFrame->identifier.bits.ide = 0;    // 标准帧
    
    // 设置数据长度
    canFrame->dlc = sizeof(Sensor_Data_t);
    
    // 复制数据到CAN帧的数据字段
    memcpy(canFrame->data, sensorData, sizeof(Sensor_Data_t));
}

// 函数：从CAN帧解包传感器数据
void unpackCANFrameToSensorData(const CAN_Frame_t* canFrame, Sensor_Data_t* sensorData) {
    // 检查ID是否匹配
    if (canFrame->identifier.bits.std_id != CAN_ID_TEMP_SENSOR) {
        printf("错误：CAN ID不匹配\n");
        return;
    }
    
    // 检查数据长度
    if (canFrame->dlc != sizeof(Sensor_Data_t)) {
        printf("错误：数据长度不正确\n");
        return;
    }
    
    // 复制数据
    memcpy(sensorData, canFrame->data, sizeof(Sensor_Data_t));
}

// 模拟CAN发送函数（实际项目中需要替换为实际的CAN驱动函数）
void CAN_TransmitFrame(const CAN_Frame_t* frame) {
    printf("发送CAN帧：\n");
    printf("ID: 0x%X\n", frame->identifier.bits.std_id);
    printf("数据长度: %d\n", frame->dlc);
    printf("数据: ");
    for (int i = 0; i < frame->dlc; i++) {
        printf("0x%02X ", frame->data[i]);
    }
    printf("\n");
}

int main(void) {
    // 创建并初始化传感器数据
    Sensor_Data_t sensorData = {
        .temperature = 2560,    // 25.60℃
        .humidity = 6500,       // 65.00%
        .status = 0x01         // 正常状态
    };
    
    // 创建CAN帧
    CAN_Frame_t txFrame;
    
    // 打包数据到CAN帧
    packSensorDataToCANFrame(&sensorData, &txFrame);
    
    // 发送CAN帧
    CAN_TransmitFrame(&txFrame);
    
    // 模拟接收并解包
    Sensor_Data_t receivedData;
    unpackCANFrameToSensorData(&txFrame, &receivedData);
    
    // 打印接收到的数据
    printf("\n接收到的传感器数据：\n");
    printf("温度: %.2f℃\n", receivedData.temperature / 100.0f);
    printf("湿度: %.2f%%\n", receivedData.humidity / 100.0f);
    printf("状态: 0x%02X\n", receivedData.status);
    
    return 0;
}