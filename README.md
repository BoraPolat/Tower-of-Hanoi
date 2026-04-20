# Tower of Hanoi — Iterative & Recursive (C++)

Two complete C++ implementations of the classic **Tower of Hanoi** puzzle, built with array-based tower simulation, real-time state display, move validation, and automatic file logging.

---

## Files

| File | Description |
|---|---|
| `hanoi_iterative.cpp` | Solves the puzzle using the cyclic iterative algorithm |
| `hanoi_recursive.cpp` | Solves the puzzle using the classic recursive algorithm |

---

## How It Works

Both implementations share the same tower simulation layer:

- **Three towers** (`A`, `B`, `C`) are represented as dynamic integer arrays.
- Tower `A` starts loaded with disks `1` through `n` (top to bottom), while `B` and `C` are empty (`-1`).
- A **sentinel value of `999`** at index `n` acts as a boundary guard during comparisons.
- After every move, `check()` validates that no Hanoi rule has been violated (no larger disk on top of a smaller one).
- Every step is printed to the terminal **and** written to a log file.

### Iterative (`hanoi_iterative.cpp`)
Uses the standard **cyclic move pattern** over `2ⁿ − 1` iterations:
- **Odd n** → cycle order: `A↔C`, `A↔B`, `B↔C`
- **Even n** → cycle order: `A↔B`, `A↔C`, `B↔C`

### Recursive (`hanoi_recursive.cpp`)
Uses the classic **divide-and-conquer** recursion:
1. Move `n−1` disks from source to auxiliary.
2. Move the largest disk from source to destination.
3. Move `n−1` disks from auxiliary to destination.

---

## Compilation & Usage

```bash
# Iterative
g++ -o hanoi_iterative hanoi_iterative.cpp
./hanoi_iterative

# Recursive
g++ -o hanoi_recursive hanoi_recursive.cpp
./hanoi_recursive
```

Both programs prompt for the number of disks at startup:

```
Enter the number of disks: 3
```

---

## Output

Each run produces:
- **Live terminal output** showing every move and tower state.
- **A log file** (`hanoi_iterative_output.txt` or `hanoi_recursive_output.txt`) with the full run transcript.

Example display for 3 disks:

```
  A             B             C  
| 1 |         |   |         |   |
| 2 |         |   |         |   |
| 3 |         |   |         |   |
---------------------------------
A --> C
...  //Every step will be shown in here.
  A             B             C  
|   |         |   |         | 1 |
|   |         |   |         | 2 |
|   |         |   |         | 3 |
---------------------------------
A --> C
Hanoi is solved! Total Moves: 7
```

---

## Complexity

| n | Minimum Moves |
|---|---|
| 1 | 1 |
| 3 | 7 |
| 5 | 31 |
| 10 | 1,023 |
| n | 2ⁿ − 1 |

> ! Large values of `n` will produce a very large number of moves and output lines. Use with caution above `n = 20`.

---

## Requirements

- C++11 or later
- Standard library only (no external dependencies)
