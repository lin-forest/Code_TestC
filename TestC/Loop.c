#include <stdio.h>

int main() {
    int i;
    
    printf("For loop: ");
    for(i=1; i<=5; i++)
    {
      printf("%d ", i);
}
        
    printf("\n");

    printf("While loop: ");
    i = 1;
    while(i <= 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");

    printf("Do-while loop: ");
    i = 1;
    do {
        printf("%d ", i);
        i++;
    } while(i <= 5);
    printf("\n");

    return 0;
}

// why do-while always executes at least once?

// #include <stdio.h>

// int main() {
//     int i = 10;

//     printf("While loop:\n");
//     while(i <= 5) {
//         printf("%d ", i);  // 不会执行
//         i++;
//     }

//     i = 10;
//     printf("\nDo-while loop:\n");
//     do {
//         printf("%d ", i);  // 会执行一次
//         i++;
//     } while(i <= 5);

//     return 0;
// }
