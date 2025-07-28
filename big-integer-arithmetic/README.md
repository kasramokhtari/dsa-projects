# BigInteger Arithmetic Library

## Overview

This project implements an **arbitrary-precision integer arithmetic library** in C++ using a custom `BigInteger` Abstract Data Type (ADT). It supports operations on integers far beyond the size limitations of standard C++ types like `int` or `long`. The library stores numbers as lists of base-10ᵖ digits (where `p = 9` in this implementation) and supports addition, subtraction, and multiplication with full sign handling.

A command-line client (`Arithmetic.cpp`) is included to demonstrate the functionality of the `BigInteger` class by reading two large integers from a file, computing various expressions, and writing the results to an output file.

---

## Features

### ✅ BigInteger Class
- Arbitrary-length signed integer representation
- Supports:
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Comparison operators (`==`, `<`, `<=`, `>`, `>=`)
  - Negation and zeroing (`negate()`, `makeZero()`)
  - Conversion to string (`to_string()`)
- Internally uses a **doubly linked list** of base-10ᵖ digits
- Handles carry/borrow logic with a `normalizeList()` routine
- Robust error-checking for invalid input strings

### ✅ Arithmetic Driver (`Arithmetic.cpp`)
Reads input from a file and outputs the results of several expressions:
- `A + B`
- `A - B`
- `A - A`
- `3A - 2B`
- `A * B`
- `A²`, `B²`
- `9A⁴ + 16B⁵`

---

## File Structure

```
.
├── BigInteger.h        # Header for BigInteger ADT
├── BigInteger.cpp      # Implementation of BigInteger
├── List.h              # Header for custom doubly linked list class
├── List.cpp            # Implementation of List class
├── Arithmetic.cpp      # Main program for arithmetic expressions
```

---

## Usage

### ✅ Compiling

```bash
g++ -std=c++11 -o Arithmetic Arithmetic.cpp BigInteger.cpp List.cpp
```

### ✅ Running

```bash
./Arithmetic input.txt output.txt
```

**`input.txt` format:**
```
<big integer A>
(blank line)
<big integer B>
```

**Example `input.txt`:**
```
123456789012345678901234567890

987654321098765432109876543210
```

**Example `output.txt`:**
```
123456789012345678901234567890

987654321098765432109876543210

1111111110111111111011111111100

-864197532086419753208641975320

0

-1481481481481481481481481481500

121932631137021795226185032733622923332237463801111263526900

15241578780673678546105778281054720515622620750190521

97546105778997104178966750690210670038348422348419041

1683778265594004016041082021029068741033810814568030941222807031888908712936521
```

---

## Notes

- This implementation avoids the C++ STL for educational purposes.
- The project emphasizes **memory management**, **modular arithmetic**, and **custom data structures**.
- In this implementation, the internal digit base is `base = 10ᵖ` where `p = 9`, which allows efficient string parsing and integer normalization.
