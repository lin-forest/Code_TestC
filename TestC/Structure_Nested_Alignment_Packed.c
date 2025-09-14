#include <stdio.h>
#include <stdint.h>

// 紧凑结构，去掉填充（慎用）
#pragma pack(push,1)
typedef struct {
    uint8_t a;  // 1字节
    uint32_t b; // 4字节
} Packed;
#pragma pack(pop)

typedef struct {
    uint8_t a;  // 1字节
    // 这里编译器会自动插入3字节填充
    uint32_t b; // 4字节
} Normal;

int main(void) {
    Packed p;
    Normal n;

    printf("结构体大小对比：\n");
    printf("Packed结构体（紧凑）= %zu 字节\n", sizeof(Packed));
    printf("Normal结构体（对齐）= %zu 字节\n", sizeof(Normal));

    // 打印成员偏移量
    printf("\n成员偏移量：\n");
    printf("Packed.a 偏移 = %zu\n", (size_t)&((Packed*)0)->a);
    printf("Packed.b 偏移 = %zu\n", (size_t)&((Packed*)0)->b);
    printf("Normal.a 偏移 = %zu\n", (size_t)&((Normal*)0)->a);
    printf("Normal.b 偏移 = %zu\n", (size_t)&((Normal*)0)->b);

    return 0;
}
