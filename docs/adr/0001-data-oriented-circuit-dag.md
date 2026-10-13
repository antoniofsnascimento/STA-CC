# ADR 0001: Data-Oriented Circuit Graph Representation

## Status
Accepted

## Context
EDA timing engines must traverse graphs containing millions of logic gates. The conventional OOP representation allocates `Node` objects on the heap, linking them via smart pointers. This triggers severe hardware penalties: pointer metadata overhead, amortized destruction latency, and catastrophic CPU L1/L2 cache misses (Cache Thrashing) during traversal due to memory fragmentation.

## Decision
We represent the circuit Directed Acyclic Graph (DAG) using **Data-Oriented Design (DOD)**:
* Vertices are assigned sequential 32-bit integer identifiers (`uint32_t NodeId`).
* Node properties (Gate Type, Delay, Arrival Time) are isolated into contiguous `std::vector` containers (Structure of Arrays - SoA).
* Adjacency relationships are flattened into a Compressed Sparse Row (CSR) format post-ingestion.

## Consequences
* **Positive:** CPU hardware prefetchers can load sequential timing data directly into L1 cache. Graph destruction is $O(1)$ amortized time.
* **Negative:** Node references require array index indirection instead of direct pointer dereferencing.
