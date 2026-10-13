# Functional Specification: STA-CC

## 1. Core Objective
The Static Timing Analyzer & Circuit Compiler (`STA-CC`) validates the timing constraints of combinatorial digital circuits without requiring functional vector simulation.

## 2. Input Contracts
* **Netlist Format:** The system exclusively ingests the standard **ISCAS85 benchmark format (`.bench`)**.
  * Example syntax: `INPUT(A)`, `OUTPUT(Z)`, `G1 = AND(A, B)`.
* **Delay Rules:** A supplementary plain-text file maps logic gate types to their intrinsic propagation delays in picoseconds (ps).

## 3. Mathematical Boundary Constraints
To evaluate circuit performance, the engine calculates:
1. **Arrival Time (AT - Forward Pass):** Propagates delays from Primary Inputs (PIs) to internal gates.
   * $AT(v) = \max_{u \in \text{pred}(v)} \big(AT(u) + \text{delay}(u \to v)\big)$
2. **Required Time (RT - Backward Pass):** Anchored to a Virtual Clock period at the Primary Outputs (POs).
   * $RT(u) = \min_{v \in \text{succ}(u)} \big(RT(v) - \text{delay}(u \to v)\big)$
3. **Slack Calculation:** $\text{Slack}(v) = RT(v) - AT(v)$. Negative slack denotes a setup timing violation.

## 4. Output Deliverables
The CLI will output:
* Topological validity confirmation (absence of combinatorial loops).
* Total propagation delay.
* The critical path trace (the chain of gates causing the worst-case delay).
