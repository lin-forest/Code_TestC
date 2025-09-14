#include <stdio.h>
#include <stdbool.h>

volatile bool flag = false; // set in ISR in embedded

// simulate ISR setting flag in another thread? here just set manually
int main(void) {
    // polling loop that must read real memory each time
    while (!flag) {
        // busy wait
        // in real code avoid busy wait，使用 low-power 或 RTOS sleep
    }
    printf("flag set\n");
    return 0;
}
// without volatile, compiler may optimize out the loop
// with volatile, compiler must read flag from memory each time