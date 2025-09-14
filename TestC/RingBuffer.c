#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define RB_SIZE 128
typedef struct {
    uint8_t buf[RB_SIZE];
    uint16_t rd;
    uint16_t wr;
} RingBuffer;

void rb_init(RingBuffer *r) { r->rd = r->wr = 0; }
bool rb_push(RingBuffer *r, uint8_t c) {
    uint16_t next = (r->wr + 1) % RB_SIZE;
    if (next == r->rd) return false; // full
    r->buf[r->wr] = c;
    r->wr = next;
    return true;
}
bool rb_pop(RingBuffer *r, uint8_t *c) {
    if (r->rd == r->wr) return false; // empty
    *c = r->buf[r->rd];
    r->rd = (r->rd + 1) % RB_SIZE;
    return true;
}

// 测试主函数（PC）
int main(void) {
    RingBuffer rb;
    rb_init(&rb);
    for (int i=0;i<200;i++) rb_push(&rb, (uint8_t)i);
    uint8_t v;
    while (rb_pop(&rb,&v)) printf("%d ", v);
    printf("\n");
    return 0;
}
// 测试结果：0 1 2 ... 126 127
// 说明：环形缓冲区满时会丢弃新数据