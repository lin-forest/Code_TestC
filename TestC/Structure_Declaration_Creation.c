#include <stdio.h>
#include <string.h>

// 1. 最基本的结构体声明方式
struct Student {
    char name[50];
    int age;
    float score;
};

// 2. 使用typedef定义结构体（推荐使用，可以省略struct关键字）
typedef struct {
    char name[50];
    int age;
    float score;
} Student2;

// 3. 结构体标签和typedef结合使用
typedef struct Teacher {
    char name[50];
    int age;
    char subject[50];
} Teacher;

int main(void) {
    // 1. 使用struct关键字创建
    struct Student student1;
    strcpy(student1.name, "张三");
    student1.age = 18;
    student1.score = 85.5;
    
    // 2. 使用struct关键字 + 初始化列表创建
    struct Student student2 = {"李四", 19, 90.5};
    
    // 3. 使用typedef后的类型创建
    Student2 student3;
    strcpy(student3.name, "王五");
    student3.age = 20;
    student3.score = 88.5;
    
    // 4. typedef + 初始化列表创建
    Student2 student4 = {"赵六", 21, 92.5};
    
    // 5. designated initializer（C99特性）
    Teacher teacher1 = {
        .name = "陈老师",
        .age = 35,
        .subject = "数学"
    };
    
    // 6. 结构体指针
    Student2 *pStudent;
    pStudent = &student3;
    
    // 打印结果
    printf("1. 基本声明和赋值:\n");
    printf("   姓名：%s, 年龄：%d, 分数：%.1f\n\n", 
           student1.name, student1.age, student1.score);
           
    printf("2. 使用初始化列表:\n");
    printf("   姓名：%s, 年龄：%d, 分数：%.1f\n\n", 
           student2.name, student2.age, student2.score);
           
    printf("3. 使用typedef:\n");
    printf("   姓名：%s, 年龄：%d, 分数：%.1f\n\n", 
           student3.name, student3.age, student3.score);
           
    printf("4. typedef + 初始化列表:\n");
    printf("   姓名：%s, 年龄：%d, 分数：%.1f\n\n", 
           student4.name, student4.age, student4.score);
           
    printf("5. designated initializer:\n");
    printf("   姓名：%s, 年龄：%d, 科目：%s\n\n", 
           teacher1.name, teacher1.age, teacher1.subject);
           
    printf("6. 通过指针访问:\n");
    printf("   姓名：%s, 年龄：%d, 分数：%.1f\n", 
           pStudent->name, pStudent->age, pStudent->score);
    
    return 0;
}