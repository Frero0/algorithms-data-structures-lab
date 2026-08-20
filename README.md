# Algorithms and Data Structures Lab

Laboratory project developed for the **Algorithms and Data Structures** course at the University of Turin (academic year 2023/2024).

The repository contains four exercises written in C and Java. The project covers generic sorting algorithms, edit distance, a minimum-priority queue, sparse graphs and Prim's algorithm. Each implementation is accompanied by automated tests and a small input example that can be run without downloading the original course datasets.

## Contents

### Exercise 1 — Generic sorting algorithms

`ex1` contains generic implementations of **Merge Sort** and **Quick Sort** in C. Both algorithms operate on arrays of arbitrary element types through `void *` pointers, element sizes and comparator functions.

The command-line program reads records in the following CSV format:

```text
id,string_field,integer_field,float_field
```

It can sort them by any of the three data fields and write the result to a new CSV file.

- Merge Sort is stable and has `O(n log n)` time complexity, with `O(n)` auxiliary space.
- Quick Sort uses an in-place Hoare-style partition. Its average time complexity is `O(n log n)`, while the worst case is `O(n²)`.

A more detailed discussion of the two algorithms is available in [`ex1/REPORT.md`](ex1/REPORT.md).

### Exercise 2 — Edit distance

`ex2` implements an edit-distance variant based on insertion and deletion. Two versions are provided:

- a direct recursive implementation, useful for understanding the recurrence;
- a memoized implementation, which avoids recomputing the same subproblems and runs in `O(mn)` time and space.

The application loads a dictionary, reads a text file word by word and prints the closest dictionary entries together with their distance. Exact matches are found through binary search after sorting the dictionary.

### Exercise 3 — Minimum-priority queue

The `priorityqueue` package inside `ex3-4` provides a generic minimum-priority queue in Java. It combines:

- a binary heap, used to retrieve and remove the minimum in `O(log n)` time;
- a hash map from elements to heap positions, used for membership checks in expected `O(1)` time and arbitrary removals in `O(log n)` time.

Null values and duplicate elements are rejected so that the heap and position map remain consistent.

### Exercise 4 — Sparse graph and Prim's algorithm

The `graph` package implements a generic sparse graph through adjacency sets. Directed or undirected graphs and labelled or unlabelled edges are supported.

The `prim` package computes a **minimum spanning forest** for an undirected weighted graph. Using the priority queue from Exercise 3, it also handles disconnected inputs by starting Prim's algorithm from every unvisited component.

During verification with the complete Italian distance dataset, the program processed 18,640 nodes and produced a forest with 18,637 edges and a total weight of approximately 89,939.913 km. The original course datasets are not included in the repository; small reproducible examples are provided instead.

## Repository structure

```text
.
├── ex1/                 # Merge Sort and Quick Sort in C
├── ex2/                 # Edit distance and text correction in C
├── ex3-4/
│   ├── src/graph/       # Sparse graph
│   ├── src/prim/        # Prim's minimum spanning forest
│   └── src/priorityqueue/
├── .github/workflows/   # Automatic test workflow
└── Makefile             # Commands for the complete project
```

Generated binaries, build directories, editor settings and external datasets are excluded through `.gitignore`.

## Requirements

- `make`
- a C11 compiler (`clang` is used by default; `gcc` can also be selected)
- JDK 11 or newer

JUnit 4 and Hamcrest are already included in `ex3-4/lib`, so the test suite does not require a dependency download.

## Build and test the complete project

From the repository root:

```bash
make
make test
```

To remove generated build files:

```bash
make clean
```

To compile and run all the included examples:

```bash
make demo
```

The sorting demo also writes its result to `output/sorted-records.csv`.

If `clang` is not available, select another C compiler when invoking `make`:

```bash
make CC=gcc test
```

## Run one exercise at a time

All the following commands are executed from the repository root.

### Exercise 1

Compile and run the included example:

```bash
make -C ex1
./ex1/bin/sort_records ex1/examples/sample-records.csv sorted.csv 2 1
```

The arguments are:

```text
sort_records <input.csv> <output.csv> <field> <algorithm>
```

- `field`: `1` for the string, `2` for the integer, `3` for the floating-point value;
- `algorithm`: `1` for Merge Sort, `2` for Quick Sort.

Run only the Exercise 1 tests with:

```bash
make -C ex1 test
```

### Exercise 2

Compile and run the included spelling example:

```bash
make -C ex2
./ex2/bin/spell_checker \
  ex2/examples/sample-dictionary.txt \
  ex2/examples/sample-text.txt
```

The dictionary must contain one word per line. The second file can contain normal text; punctuation and whitespace are treated as separators.

Run only the Exercise 2 tests with:

```bash
make -C ex2 test
```

### Exercises 3 and 4

Compile the Java sources and run Prim's algorithm on the included graph:

```bash
make -C ex3-4
make -C ex3-4 run-prim
```

Each graph row must have this format:

```text
start_node,end_node,weight
```

To use another graph, pass its path through `GRAPH`:

```bash
make -C ex3-4 run-prim GRAPH=/path/to/graph.csv
```

Run the complete Java test suite or a single group of tests with:

```bash
make -C ex3-4 test
make -C ex3-4 test-priorityqueue
make -C ex3-4 test-graph
make -C ex3-4 test-prim
```

## Author

Federico Santorsola
