#include <stdio.h>

// 结构体示例：描述一个学生
struct Student {
    char name[50];     // 姓名
    int age;           // 年龄
    float score;       // 分数
};

// 枚举示例：描述学生状态
enum StudentStatus {
    ENROLLED = 1,      // 已注册
    SUSPENDED,         // 已暂停（自动为2）
    GRADUATED          // 已毕业（自动为3）
};

int main(void) {
    // 使用结构体
    struct Student student1 = {"张三", 18, 85.5};
    printf("学生信息：\n");
    printf("姓名：%s\n", student1.name);
    printf("年龄：%d\n", student1.age);
    printf("分数：%.1f\n\n", student1.score);

    // 使用枚举
    enum StudentStatus status = ENROLLED;
    printf("学生状态：%d\n", status);
    
    // 打印各种类型的大小
    printf("\n内存占用大小：\n");
    printf("结构体Student大小：%zu 字节\n", sizeof(struct Student));
    printf("枚举StudentStatus大小：%zu 字节\n", sizeof(enum StudentStatus));

    return 0;
}