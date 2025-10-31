#include <stdio.h>
#include "../heap/heap.h"
#include "../stack/stack.h"
#include "../asm/disassembler.h"


int main() {
    int choice;

    printf("=== Memory Dungeon ===\n");
    printf("Choose your quest, brave adventurer:\n");
    printf("1. Heap Hallway (Many Rooms, Which One is Next?)\n");
    printf("2. Stack Playground (Tower of Frames)\n");
    printf("3. Disassembler (Magic Scrolls)\n");
    printf("0. Exit\n");
    printf("> ");

    if (scanf("%d", &choice) != 1) return 1;

    switch (choice) {
        case 1:
            printf("You chose Heap Hallway!\n");
            run_heap_demo(); // Run the heap demo we built
            break;
        case 2:
            printf("You chose Stack Playground!\n");
            run_stack_demo();
            break;
        case 3:
            printf("You chose Disassembler!\n");
            run_disassembler_demo();
            break;
        case 0:
            printf("Goodbye, adventurer!\n");
            return 0;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
