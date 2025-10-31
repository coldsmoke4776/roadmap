#include "stack.h"
#include <stdio.h>
#include <string.h>

void stack_dump(const char *buf, size_t buf_size, size_t input_length) {
    printf("=== The Tower of Frames ===\n");

    // Draw the Return Address
    printf("| Return Address | ");
    if (input_length > buf_size + sizeof(void *)){
        printf("BUF.OVERFLOW! \n");
        printf("  ↳ The CPU will try to return to this address.\n");
        printf("  ↳ Since it's overwritten with your input, the program will crash.\n");
    } else {
        printf("SAFE! \n");
        printf("  ↳ This is where the CPU expects to resume execution after this function.\n");
    }

    // Draw Saved Frame Pointer
    printf("| Saved Frame Pointer | ");
    if (input_length > buf_size){
        printf("BUF.OVERFLOW! \n");
        printf("  ↳ This normally links one stack frame to the previous.\n");
        printf("  ↳ Overwriting it corrupts the call stack.\n");
    } else {
        printf("SAFE! \n");
        printf("  ↳ Keeps track of where the last stack frame began.\n");
    }

    // Draw Local Buffer
    printf("| buf [%zu]  | ", buf_size);
    for (size_t i=0; i<buf_size; i++){
        if (i < input_length){
            putchar(buf[i]);
        } else {
            putchar('.');
        }  
    }
    putchar('\n');

    printf("=======================\n");
}