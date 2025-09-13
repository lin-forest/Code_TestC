#include <stdio.h>

// struct Student {
//     char name[20];
//     int age;
// };

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char name[20];
    int age;
    struct Date birthday;  // 嵌套结构体
};

int main() {
//     struct Student s1 = {"Alice", 20};
//     struct Student s2 = {"Bob", 22};

//     printf("Student 1: %s, Age: %d\n", s1.name, s1.age);
//     printf("Student 2: %s, Age: %d\n", s2.name, s2.age);

//     // Array of structs
//     struct Student class[2] = {s1, s2};
//     for(int i=0; i<2; i++) {
//         printf("Class[%d]: %s, %d\n", i, class[i].name, class[i].age);
//     }


struct Student s = {"Alice", 20, {5, 9, 2005}};
printf("%s's birthday: %d-%d-%d\n",
       s.name, s.birthday.day, s.birthday.month, s.birthday.year);

    return 0;
}
