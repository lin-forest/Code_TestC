#include <stdio.h>
#include <stdint.h>

// 定义系统所有可能的状态
typedef enum {
    STATE_IDLE,         // 空闲状态
    STATE_LED_ON,       // LED亮状态
    STATE_LED_OFF,      // LED灭状态
    STATE_LED_BLINK,    // LED闪烁状态
    STATE_ERROR         // 错误状态
} SystemState_t;

// 定义系统可能的事件
typedef enum {
    EVENT_NONE,         // 无事件
    EVENT_BUTTON_PRESS, // 按键按下
    EVENT_TIMER_TICK,   // 定时器触发
    EVENT_ERROR         // 错误发生
} SystemEvent_t;

// LED控制结构体
typedef struct {
    uint8_t isOn;           // LED当前是否亮起
    uint16_t blinkCount;    // 闪烁计数
    uint16_t errorCode;     // 错误代码
} LED_Control_t;

// 系统控制块
typedef struct {
    SystemState_t currentState;     // 当前状态
    LED_Control_t led;             // LED控制结构体
    uint32_t stateEnterTime;       // 进入当前状态的时间
} System_Control_t;

// 函数声明
void LED_TurnOn(void);
void LED_TurnOff(void);
void LED_Toggle(void);
void System_EnterErrorState(uint16_t errorCode);

// 状态处理函数
void HandleState_Idle(System_Control_t* sys, SystemEvent_t event) {
    switch(event) {
        case EVENT_BUTTON_PRESS:
            // 按键按下，转换到LED开启状态
            sys->currentState = STATE_LED_ON;
            LED_TurnOn();
            printf("状态转换: IDLE -> LED_ON\n");
            break;
            
        case EVENT_ERROR:
            // 发生错误，转换到错误状态
            sys->currentState = STATE_ERROR;
            System_EnterErrorState(0x01);
            printf("状态转换: IDLE -> ERROR\n");
            break;
            
        default:
            // 其他事件忽略
            break;
    }
}

void HandleState_LedOn(System_Control_t* sys, SystemEvent_t event) {
    switch(event) {
        case EVENT_BUTTON_PRESS:
            // 按键按下，转换到LED闪烁状态
            sys->currentState = STATE_LED_BLINK;
            sys->led.blinkCount = 0;
            printf("状态转换: LED_ON -> LED_BLINK\n");
            break;
            
        case EVENT_TIMER_TICK:
            // 可以在这里添加超时处理
            break;
            
        default:
            break;
    }
}

void HandleState_LedBlink(System_Control_t* sys, SystemEvent_t event) {
    switch(event) {
        case EVENT_TIMER_TICK:
            // 定时器触发，执行闪烁
            LED_Toggle();
            sys->led.blinkCount++;
            
            // 闪烁10次后关闭
            if(sys->led.blinkCount >= 10) {
                sys->currentState = STATE_LED_OFF;
                LED_TurnOff();
                printf("状态转换: LED_BLINK -> LED_OFF\n");
            }
            break;
            
        case EVENT_BUTTON_PRESS:
            // 按键按下，直接关闭
            sys->currentState = STATE_LED_OFF;
            LED_TurnOff();
            printf("状态转换: LED_BLINK -> LED_OFF\n");
            break;
            
        default:
            break;
    }
}

// 状态机主处理函数
void StateMachine_Process(System_Control_t* sys, SystemEvent_t event) {
    // 根据当前状态调用相应的处理函数
    switch(sys->currentState) {
        case STATE_IDLE:
            HandleState_Idle(sys, event);
            break;
            
        case STATE_LED_ON:
            HandleState_LedOn(sys, event);
            break;
            
        case STATE_LED_BLINK:
            HandleState_LedBlink(sys, event);
            break;
            
        case STATE_LED_OFF:
            // 在关闭状态下，按键按下返回空闲状态
            if(event == EVENT_BUTTON_PRESS) {
                sys->currentState = STATE_IDLE;
                printf("状态转换: LED_OFF -> IDLE\n");
            }
            break;
            
        case STATE_ERROR:
            // 错误状态下忽略所有事件，需要系统复位才能退出
            break;
            
        default:
            // 未知状态，进入错误状态
            sys->currentState = STATE_ERROR;
            System_EnterErrorState(0xFF);
            break;
    }
}

// 模拟硬件控制函数
void LED_TurnOn(void) {
    printf("LED 打开\n");
}

void LED_TurnOff(void) {
    printf("LED 关闭\n");
}

void LED_Toggle(void) {
    static uint8_t ledState = 0;
    ledState = !ledState;
    printf("LED 翻转: %s\n", ledState ? "开" : "关");
}

void System_EnterErrorState(uint16_t errorCode) {
    printf("系统进入错误状态，错误代码: 0x%04X\n", errorCode);
}

// 主函数：演示状态机的使用
int main(void) {
    // 初始化系统控制块
    System_Control_t sysControl = {
        .currentState = STATE_IDLE,
        .led = {0},
        .stateEnterTime = 0
    };
    
    // 模拟一系列事件
    printf("=== 状态机演示开始 ===\n\n");
    
    // 模拟按键按下，从IDLE转到LED_ON
    StateMachine_Process(&sysControl, EVENT_BUTTON_PRESS);
    
    // 模拟按键按下，从LED_ON转到LED_BLINK
    StateMachine_Process(&sysControl, EVENT_BUTTON_PRESS);
    
    // 模拟几次定时器事件，触发LED闪烁
    for(int i = 0; i < 5; i++) {
        StateMachine_Process(&sysControl, EVENT_TIMER_TICK);
    }
    
    // 模拟按键按下，强制转到LED_OFF
    StateMachine_Process(&sysControl, EVENT_BUTTON_PRESS);
    
    // 模拟按键按下，从LED_OFF返回IDLE
    StateMachine_Process(&sysControl, EVENT_BUTTON_PRESS);
    
    // 模拟错误发生
    StateMachine_Process(&sysControl, EVENT_ERROR);
    
    printf("\n=== 状态机演示结束 ===\n");
    
    return 0;
}