# Stage 1 — Data Structures & Utilities

This stage focuses on building core data structures and small utilities from scratch in C.  
The goal is to master **pointers, structs, and memory management basics** before moving on to custom allocators and concurrency.

---

## 📌 Modules in Stage 1

### 🔹 Vector
- **File:** [`vector/vector.c`](./vector/vector.c) / [`vector/vector.h`](./vector/vector.h)  
- **Goal:** Implement a dynamic array with support for `push`, `pop`, resizing, and freeing.  
- **Proof of Concept:** [`tests/test_vector.c`](./tests/test_vector.c)  

### 🔹 Linked List
- **File:** [`linked_list/list.c`](./linked_list/list.c) / [`linked_list/list.h`](./linked_list/list.h)  
- **Goal:** Implement a singly linked list with insert, delete, and traversal.  
- **Proof of Concept:** [`tests/test_list.c`](./tests/test_list.c)  

### 🔹 CLI Parser
- **File:** [`cli_parser/cli_parser.c`](./cli_parser/cli_parser.c) / [`cli_parser/cli_parser.h`](./cli_parser/cli_parser.h)  
- **Goal:** Custom argument/flag parser (mini `getopt`).  
- **Proof of Concept:** [`tests/test_cli_parser.c`](./tests/test_cli_parser.c)  

### 🔹 String Library
- **File:** [`stringlib/stringlib.c`](./stringlib/stringlib.c) / [`stringlib/stringlib.h`](./stringlib/stringlib.h)  
- **Goal:** Build minimal string utilities (`concat`, `split`, `reverse`, `substring`).  
- **Proof of Concept:** [`tests/test_stringlib.c`](./tests/test_stringlib.c)  

---

## 🎯 Proof Program

- **File:** [`proofs/stage1_cli.c`](./proofs/stage1_cli.c)  
- **Description:** A small CLI tool that ties everything together.  
  - Uses `cli_parser` to handle arguments  
  - Stores input data in a `vector`  
  - Manipulates strings with `stringlib`  
  - Traverses data with `linked_list`  

This is the **capstone program** for Stage 1 — proof that the modules work together in a real utility.

---

## ⚡ Build & Run

From repo root:

```bash
# Build all Stage 1 modules + proof program
make stage1

# Run tests individually
make vector
make list
make cli_parser
make stringlib

# Run proof program
make stage1_proof
./bin/stage1_cli
