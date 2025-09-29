# Rules of Play

This repository is a **skills ledger**, not just another collection of code.  
Every module, test, and proof program exists to demonstrate real understanding of CS and systems programming concepts.  
To keep it **ledger-worthy**, these are the ground rules:

---

## 1. I Write the Code
- Every `.c` and `.h` file is typed and reasoned out by me.  
- No copy-pasting from ChatGPT, StackOverflow, or textbooks.  
- Reading, research, and notes are encouraged — but the final implementation is mine.

---

## 2. ChatGPT = Coach, Not Code Generator
- ChatGPT can explain concepts (e.g., “what is a vector?”).  
- ChatGPT can outline APIs, tradeoffs, and debugging approaches.  
- ChatGPT **does not** provide finished code for this repo.  
- Final implementations and fixes are on me.

---

## 3. Testing Is Proof
- Each module includes a basic test program under `/tests/`.  
- Tests demonstrate expected behavior and edge cases.  
- Passing tests = evidence that the concept is understood.

---

## 4. Compilation Discipline
- All code must compile with:

  ```bash
  gcc -Wall -Wextra -std=c11
  ```
- No warnings ignored — they must be fixed before committing.

## 5. Documentation Matters
- Each file begins with a short header comment explaining its purpose.
- Inline comments clarify tricky logic (e.g., realloc strategies).
- Clarity > cleverness.

---

## 6. Ledger-Worthy = Understood
- A task counts as **complete** only if I can explain the concept and the code without notes.  
- If I can’t explain it tomorrow, it’s not ready to check off in the roadmap.

---

### Why This Exists
This repo links directly to my [Skills Roadmap](https://matttwells.com/roadmap).  
It’s designed to be transparent evidence of progress and understanding — proof that I didn’t just “do a course,” but built foundations one concept at a time.
