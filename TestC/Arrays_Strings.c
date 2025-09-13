// #include <stdio.h>

// int main() {
//     int numbers[5] = {1,2,3,4,5};      // 数组
//     char word[] = "Hello";             // 字符数组 = 字符串

//     printf("numbers[2] = %d\n", numbers[2]); // 输出 3
//     printf("word[1] = %c\n", word[1]);       // 输出 'e'
//     printf("Full word: %s\n", word);         // 输出 Hello

//     return 0;
// }


#include <stdio.h>

int main() {
    int arr[5] = {3, 7, 2, 9, 5};
    int sum = 0, max = arr[0], i;

    for(i=0; i<5; i++) {
        printf("%d ", arr[i]);
        sum += arr[i];
        if(arr[i] > max)
            max = arr[i];
    }

    printf("\nSum = %d\n", sum);
    printf("Max = %d\n", max);

    return 0;
}
