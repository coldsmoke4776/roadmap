#include <stdio.h>
#include "disassembler.h"

// Decode a single byte and return its meaning as a human-readable instruction.
const char* decode_byte(unsigned char byte) {
    switch (byte) {
        case 0x90: return "NOP: Do nothing for one cycle";
        case 0xC3: return "RET: Return from a function";
        case 0xCC: return "INT3: Breakpoint, used for debugging to pause execution";
        default: return "Unknown instruction";
    }
}

void run_disassembler_demo() {
    unsigned char scroll[] = {
        0x90,
        0x90,
        0xC3,
        0xC3,
        0x90,
        0xCC,
    };

    size_t len = sizeof(scroll) / sizeof(scroll[0]);

    printf("The Magic Scroll of Bytes hath been revealed as human-readable instructions!\n");
    printf("Each line is one byte from the scroll, and the instruction is decoded for you.\n");
    printf("Remember, in memory, these are just bytes, but they have meaning when interpreted as instructions.\n");

    for (size_t i =0; i < len; i++) {
        printf("0x%02X            -> %s\n", scroll[i], decode_byte(scroll[i]));
    }

    printf("\nThe scroll is now empty, for you to use again.\n");
    printf("=============================\n");
}