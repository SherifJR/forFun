# forFun :)
---

## DFA — Strings Containing "01"

Was studying **ToC** for my final exam, then found a question about constructing a DFA that accepts all binary strings containing `01` as a substring — and said: why not code it
Maybe I will add NFA later. 
---

## DFA Diagram

![DFA for strings containing 01](https://github.com/SherifJR/forFun/blob/main/finite_automata/dfa_diagram.png)

---

## How it works

The DFA has **3 states**:

| State | Meaning |
|-------|---------|
| `q0 (1)` | Start state — no progress yet |
| `q1 (2)` | Seen a `0` — ready for `1` |
| `q2 (3)` | Accepted — `01` found! |

### Transition Table

| Current State | Input `0` | Input `1` |
|--------------|-----------|-----------|
| q0 | q1 | q0 |
| q1 | q1 | q2 |
| q2 | q2 | q2 |

### Transition logic:
- **q0** — On `1` stay at q0, on `0` move to q1.
- **q1** — Just saw a `0`. if the next is `0` stay at q1 (still waiting to see 1), on `1` move to q2 **accept state** 
- **q2** — `01` found! Stay here forever regardless of input.


## Example runs

```
Input:  100001      → accepted  
Input:  10          → rejected  
Input:  1110000     → rejected  
Input:  0000        → rejected  
Input:  01          → accepted 
```

## How to run

```bash
gcc dfa_acc_01.c -o dfa
./dfa
# enter your binary string and hit enter
```
