CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./heap -I./stack -I./asm

# Executables
HEAP_DEMO = heap_demo
STACK_DEMO = stack_demo
ASM_DEMO = asm_demo
DUNGEON = memory_dungeon

# Default build: all
all: $(HEAP_DEMO) $(STACK_DEMO) $(ASM_DEMO) $(DUNGEON)

# ------------------------------
# Heap demo (standalone)
# ------------------------------
$(HEAP_DEMO): heap/heap.o heap/demo_heap_standalone.o
	$(CC) $(CFLAGS) -o $@ $^

heap/heap.o: heap/heap.c heap/heap.h
	$(CC) $(CFLAGS) -c $< -o $@

heap/demo_heap_standalone.o: heap/demo_heap.c heap/heap.h
	$(CC) $(CFLAGS) -DSTANDALONE -c $< -o $@

heap/demo_heap.o: heap/demo_heap.c heap/heap.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Stack demo (standalone)
# ------------------------------
$(STACK_DEMO): stack/stack.o stack/demo_stack_standalone.o
	$(CC) $(CFLAGS) -o $@ $^

stack/stack.o: stack/stack.c stack/stack.h
	$(CC) $(CFLAGS) -c $< -o $@

stack/demo_stack_standalone.o: stack/demo_stack.c stack/stack.h
	$(CC) $(CFLAGS) -DSTANDALONE -c $< -o $@

stack/demo_stack.o: stack/demo_stack.c stack/stack.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# ASM demo (standalone)
# ------------------------------
$(ASM_DEMO): asm/disassembler.o asm/demo_disassembler_standalone.o
	$(CC) $(CFLAGS) -o $@ $^

asm/disassembler.o: asm/disassembler.c asm/disassembler.h
	$(CC) $(CFLAGS) -c $< -o $@

asm/demo_disassembler_standalone.o: asm/demo_disassembler.c asm/disassembler.h
	$(CC) $(CFLAGS) -DSTANDALONE -c $< -o $@

asm/demo_disassembler.o: asm/demo_disassembler.c asm/disassembler.h
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Dungeon runner (menu)
# ------------------------------
$(DUNGEON): src/main.o heap/heap.o heap/demo_heap.o stack/stack.o stack/demo_stack.o asm/disassembler.o asm/demo_disassembler.o
	$(CC) $(CFLAGS) -o $@ $^

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Quality of life
# ------------------------------
.PHONY: clean run

clean:
	rm -f */*.o *.o $(HEAP_DEMO) $(STACK_DEMO) $(ASM_DEMO) $(DUNGEON)

run: $(DUNGEON)
	./$(DUNGEON)
