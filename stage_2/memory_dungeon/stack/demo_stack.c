#include <stdio.h>
#include <string.h>
#include "stack.h"

void run_stack_demo() {
    char buf[16];

    printf("Welcome to Stack Playground!  It's Bloodsport rules: Two frames enter, one frame leaves...\n\n");
    printf("If you want to see your typed characters, type less than 16 characters. If you want to see the overflow, type more than 16 characters.\n\n");
    printf("Enter a string to add to the stack:\n\n");
    
    // We are going to trigger a buffer overflow using a deliberate command with no bounds checking.
    scanf("%s", buf);

    printf("You entered: %s\n", buf);
    
    // Time to visualize what happened!
    stack_dump(buf, sizeof(buf), strlen(buf));

};

#if defined(STANDALONE)
int main(void) {
    run_stack_demo();
    return 0;
}
#endif
