# 🏰 Memory Dungeon

An interactive C learning project that turns scary memory concepts into a dungeon crawl.

## Quests

### 1. Heap Hallway (Many Rooms, Which One is Next?)
- Simulates a heap with a bump allocator.
- ASCII hallway shows allocated vs free rooms.
- Teaches why `size_t` is unsigned and how allocation works.

### 2. Stack Playground (Tower of Frames)
- Local buffer on the stack (`buf[16]`).
- Unsafe input leads to buffer overflow.
- ASCII tower shows buf, saved frame pointer, return address.
- Crashes authentically when smashed (`0x41414141`).

### 3. Magic Scrolls (Disassembler)
- Demonstrates how bytes in memory are interpreted as CPU instructions.
- Maps opcodes like `0x90` (NOP), `0xC3` (RET), `0xCC` (INT3).
- ASCII scroll output explains each instruction.

## Build

```bash
make            # builds memory_dungeon and standalone demos
make run        # runs the dungeon runner
make clean      # removes objects and binaries
