#include <stdio.h>
#include <stdint.h>

// 任务状态（类似操作系统进程状态）
typedef enum {
    TASK_READY,         // 就绪状态（等待运行）
    TASK_RUNNING,       // 运行状态（正在执行）
    TASK_BLOCKED,       // 阻塞状态（等待资源或事件）
    TASK_SUSPENDED,     // 挂起状态（被暂停）
    TASK_TERMINATED     // 终止状态
} TaskState_t;

// 系统事件（类似操作系统中断）
typedef enum {
    EVT_NONE,
    EVT_TIMER_TICK,     // 时间片到期
    EVT_RESOURCE_READY, // 资源就绪
    EVT_SUSPEND,        // 挂起请求
    EVT_RESUME,         // 恢复请求
    EVT_TERMINATE       // 终止请求
} SystemEvent_t;

// 任务控制块（类似操作系统PCB-进程控制块）
typedef struct {
    uint8_t taskId;         // 任务ID
    TaskState_t state;      // 当前状态
    uint32_t timeSlice;     // 时间片
    uint32_t priority;      // 优先级
    uint32_t stackPtr;      // 栈指针（模拟）
    void* resources;        // 资源指针（模拟）
} Task_Control_Block_t;

// 系统控制块（类似操作系统内核数据结构）
typedef struct {
    Task_Control_Block_t* currentTask;    // 当前运行任务
    uint32_t systemTicks;                 // 系统时钟
    uint8_t resourceStatus;               // 资源状态
} System_Control_t;

// 模拟任务切换
void TaskSwitch(Task_Control_Block_t* oldTask, Task_Control_Block_t* newTask) {
    printf("任务切换: Task %d -> Task %d\n", 
           oldTask ? oldTask->taskId : 0, 
           newTask ? newTask->taskId : 0);
}

// 状态处理函数（类似操作系统调度器）
void HandleTaskState(System_Control_t* sys, Task_Control_Block_t* task, SystemEvent_t event) {
    switch(task->state) {
        case TASK_READY:
            if(event == EVT_TIMER_TICK && !sys->currentTask) {
                // 没有运行中的任务，切换到该任务
                task->state = TASK_RUNNING;
                sys->currentTask = task;
                printf("Task %d: READY -> RUNNING\n", task->taskId);
                TaskSwitch(NULL, task);
            }
            break;

        case TASK_RUNNING:
            if(event == EVT_TIMER_TICK) {
                // 时间片到期，切换回就绪状态
                task->state = TASK_READY;
                sys->currentTask = NULL;
                printf("Task %d: RUNNING -> READY (时间片用完)\n", task->taskId);
            }
            else if(event == EVT_SUSPEND) {
                // 任务被挂起
                task->state = TASK_SUSPENDED;
                sys->currentTask = NULL;
                printf("Task %d: RUNNING -> SUSPENDED\n", task->taskId);
            }
            break;

        case TASK_BLOCKED:
            if(event == EVT_RESOURCE_READY) {
                // 资源就绪，转为就绪状态
                task->state = TASK_READY;
                printf("Task %d: BLOCKED -> READY (资源就绪)\n", task->taskId);
            }
            break;

        case TASK_SUSPENDED:
            if(event == EVT_RESUME) {
                // 恢复任务
                task->state = TASK_READY;
                printf("Task %d: SUSPENDED -> READY\n", task->taskId);
            }
            break;

        default:
            break;
    }
}

// 模拟操作系统调度
void SchedulerTick(System_Control_t* sys, Task_Control_Block_t* tasks, int taskCount) {
    printf("\n--- 系统时钟节拍 %d ---\n", sys->systemTicks++);

    // 处理所有任务
    for(int i = 0; i < taskCount; i++) {
        HandleTaskState(sys, &tasks[i], EVT_TIMER_TICK);
    }
}

int main(void) {
    // 初始化系统
    System_Control_t system = {0};
    
    // 创建任务（模拟操作系统任务创建）
    Task_Control_Block_t tasks[] = {
        {.taskId = 1, .state = TASK_READY, .priority = 1},
        {.taskId = 2, .state = TASK_READY, .priority = 2},
        {.taskId = 3, .state = TASK_BLOCKED, .priority = 1}
    };
    
    printf("=== 模拟操作系统任务调度 ===\n");
    
    // 模拟几个时钟周期的调度
    for(int i = 0; i < 3; i++) {
        SchedulerTick(&system, tasks, 3);
    }
    
    // 模拟任务3获得资源
    printf("\n--- 任务3的资源就绪 ---\n");
    HandleTaskState(&system, &tasks[2], EVT_RESOURCE_READY);
    
    // 再次调度
    SchedulerTick(&system, tasks, 3);
    
    // 模拟挂起任务1
    printf("\n--- 挂起任务1 ---\n");
    if(tasks[0].state == TASK_RUNNING) {
        HandleTaskState(&system, &tasks[0], EVT_SUSPEND);
    }
    
    // 最后一次调度
    SchedulerTick(&system, tasks, 3);
    
    return 0;
}