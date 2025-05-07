# Data Structures and Algorithms Projects – CSE 101

This repository contains a collection of modular C and C++ projects that implement fundamental data structures and algorithms. Each subdirectory corresponds to a focused project exploring algorithmic efficiency, ADT design, and modular software development.

## Project Overview

### 📁 `linked-list-adt`

A doubly linked list implementation in C with cursor-based traversal. Supports dynamic insertion, deletion, and deep copying. Used as a foundational structure in later projects.

**Language**: C

---

### 📁 `bfs-graph-adt`

An undirected graph implementation using adjacency lists. Supports Breadth-First Search (BFS) to find shortest paths between nodes.

**Concepts**: Graph traversal, queue-based BFS, adjacency lists  
**Language**: C

---

### 📁 `graph-dfs-scc-adt`

A directed graph with Depth-First Search (DFS) and support for identifying Strongly Connected Components using Kosaraju’s algorithm.

**Concepts**: DFS, finish times, graph transpose, SCC extraction  
**Language**: C

---

### 📁 `sparse-matrix-calculator`

Efficient matrix operations using a sparse representation (array of lists). Supports scalar multiplication, addition, subtraction, transposition, and multiplication.

**Concepts**: Sparse data structures, matrix arithmetic, optimization  
**Language**: C

---

### 📁 `perfect-shuffle-simulator`

A C++ program that simulates perfect (riffle) shuffles using a custom List ADT with dummy nodes and a cursor. Determines how many shuffles are needed to restore a list to its original order.

**Concepts**: Permutations, doubly linked lists, pointer manipulation  
**Language**: C++

---

### 📁 `big-integer-arithmetic`

Arbitrary-precision integer arithmetic using a List of base-10⁹ digits. Implements addition, subtraction, and multiplication of large integers.

**Concepts**: Positional arithmetic, normalization, operator overloading  
**Language**: C++

---

### 📁 `bst-dictionary`

Dictionary ADT using an unbalanced Binary Search Tree (BST). Stores key–value pairs with in-order and pre-order traversal output.

**Concepts**: BST traversal, dictionary interface, C++ iterators  
**Language**: C++

---

### 📁 `rbt-dictionary`

A Red-Black Tree-based version of the Dictionary ADT. Includes a `WordFrequency` client that counts the frequency of each word in a text file, case-insensitive and punctuation-free.

**Concepts**: Self-balancing trees, frequency analysis, RBT invariants  
**Language**: C++

---

## How to Build

Each project includes a `Makefile`. Run:

```bash
make            # Compiles project executables
make clean      # Cleans object and binary files
```
