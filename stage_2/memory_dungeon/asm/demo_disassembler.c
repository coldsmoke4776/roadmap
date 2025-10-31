#include <stdio.h>
#include "disassembler.h"

void run_disassembler_demo();

#if defined(STANDALONE)
int main() {
    run_disassembler_demo();
    return 0;
}
#endif