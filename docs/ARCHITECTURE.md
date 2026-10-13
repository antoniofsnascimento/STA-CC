# Technical Architecture: STA-CC

## 1. Component Decoupling
The project is strictly separated into two deployment targets:
* **`stacc_core` (Static Library):** The pure mathematical and structural engine. Contains the memory arena, the topological sorter, and the graph algorithms. Zero knowledge of I/O or CLI commands.
* **`stacc_cli` (Executable):** The execution wrapper that parses user arguments and invokes the core engine. Designed to be easily replaceable by an RPC/gRPC server wrapper in future iterations.

## 2. Execution Flow
1. **Ingestion:** C++20 `std::string_view` pipelines parse the `.bench` file with zero heap allocations. Edges are pushed to a contiguous temporary buffer.
2. **Compilation (Freeze):** The engine compresses the temporary edges into the Flat CSR representation.
3. **Topological Sorter:** Kahn's Algorithm ($O(V + E)$) validates the Directed Acyclic Graph (DAG) constraints and outputs a linear processing schedule.
4. **Timing Passes:** Sequential execution over contiguous arrays for L1 cache-friendly delay propagation.

## 3. Strict Systems Engineering Constraints
* **Memory Management:** RAII exclusively. Raw `new`/`delete` or naked pointers are forbidden.
* **Security & Auditing:** The engine must compile cleanly under `-Wall -Wextra -Werror` and pass continuous integration under AddressSanitizer and UndefinedBehaviorSanitizer to guarantee zero memory leaks or data races.
