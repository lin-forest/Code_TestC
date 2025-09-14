#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>  // 为memcpy添加

// 配置部分
#define RB_SIZE 128        // 缓冲区大小
#define RB_MASK (RB_SIZE-1)  // 掩码，用于优化求模运算

// 确保RB_SIZE是2的幂
#if (RB_SIZE & (RB_SIZE - 1)) != 0
    #error "RB_SIZE must be power of 2"
#endif

typedef struct {
    uint8_t buf[RB_SIZE];    // 缓冲区数组
    uint16_t rd;             // 读指针
    uint16_t wr;             // 写指针
    uint16_t count;          // 当前数据计数
} RingBuffer;

// 初始化环形缓冲区
void rb_init(RingBuffer *rb) {
    if (rb) {
        rb->rd = 0;
        rb->wr = 0;
        rb->count = 0;
        memset(rb->buf, 0, RB_SIZE);
    }
}

// 获取缓冲区中的数据量
uint16_t rb_available(const RingBuffer *rb) {
    return rb ? rb->count : 0;
}

// 获取缓冲区剩余空间
uint16_t rb_free_space(const RingBuffer *rb) {
    return rb ? (RB_SIZE - rb->count) : 0;
}

// 检查缓冲区是否为空
bool rb_is_empty(const RingBuffer *rb) {
    return rb ? (rb->count == 0) : true;
}

// 检查缓冲区是否已满
bool rb_is_full(const RingBuffer *rb) {
    return rb ? (rb->count == RB_SIZE) : true;
}

// 写入单个字节
bool rb_push(RingBuffer *rb, uint8_t data) {
    if (!rb || rb_is_full(rb)) {
        return false;
    }

    rb->buf[rb->wr] = data;
    rb->wr = (rb->wr + 1) & RB_MASK;  // 使用位运算优化
    rb->count++;
    return true;
}

// 读取单个字节
bool rb_pop(RingBuffer *rb, uint8_t *data) {
    if (!rb || !data || rb_is_empty(rb)) {
        return false;
    }

    *data = rb->buf[rb->rd];
    rb->rd = (rb->rd + 1) & RB_MASK;  // 使用位运算优化
    rb->count--;
    return true;
}

// 批量写入数据
uint16_t rb_push_multi(RingBuffer *rb, const uint8_t *data, uint16_t len) {
    if (!rb || !data || len == 0) {
        return 0;
    }

    uint16_t free = rb_free_space(rb);
    uint16_t to_write = (len > free) ? free : len;
    
    for (uint16_t i = 0; i < to_write; i++) {
        rb_push(rb, data[i]);
    }
    
    return to_write;
}

// 批量读取数据
uint16_t rb_pop_multi(RingBuffer *rb, uint8_t *data, uint16_t len) {
    if (!rb || !data || len == 0) {
        return 0;
    }

    uint16_t available = rb_available(rb);
    uint16_t to_read = (len > available) ? available : len;
    
    for (uint16_t i = 0; i < to_read; i++) {
        rb_pop(rb, &data[i]);
    }
    
    return to_read;
}

// 清空缓冲区
void rb_clear(RingBuffer *rb) {
    if (rb) {
        rb->rd = 0;
        rb->wr = 0;
        rb->count = 0;
    }
}

// 查看数据但不取出
bool rb_peek(const RingBuffer *rb, uint8_t *data, uint16_t offset) {
    if (!rb || !data || offset >= rb->count) {
        return false;
    }
    
    uint16_t peek_index = (rb->rd + offset) & RB_MASK;
    *data = rb->buf[peek_index];
    return true;
}

// 测试主函数
int main(void) {
    RingBuffer rb;
    rb_init(&rb);
    
    printf("=== 环形缓冲区测试 ===\n");
    
    // 测试1：逐个写入和读取
    printf("\n1. 基本写入和读取测试：\n");
    for (uint8_t i = 0; i < 5; i++) {
        rb_push(&rb, i);
        printf("写入: %d\n", i);
    }
    
    uint8_t data;
    while (rb_pop(&rb, &data)) {
        printf("读出: %d\n", data);
    }
    
    // 测试2：批量操作
    printf("\n2. 批量操作测试：\n");
    uint8_t write_data[] = {10, 11, 12, 13, 14};
    uint8_t read_data[5];
    
    uint16_t written = rb_push_multi(&rb, write_data, sizeof(write_data));
    printf("批量写入: %d 字节\n", written);
    
    uint16_t read = rb_pop_multi(&rb, read_data, sizeof(read_data));
    printf("批量读出: %d 字节\n", read);
    for (int i = 0; i < read; i++) {
        printf("数据: %d\n", read_data[i]);
    }
    
    // 测试3：缓冲区状态
    printf("\n3. 缓冲区状态测试：\n");
    printf("是否为空: %s\n", rb_is_empty(&rb) ? "是" : "否");
    
    // 填满缓冲区
    for (int i = 0; i < RB_SIZE; i++) {
        rb_push(&rb, i);
    }
    printf("是否已满: %s\n", rb_is_full(&rb) ? "是" : "否");
    printf("可用数据量: %d\n", rb_available(&rb));
    printf("剩余空间: %d\n", rb_free_space(&rb));
    
    return 0;
}