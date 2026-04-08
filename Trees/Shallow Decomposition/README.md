### Problem Statement
Provided a tree (by reference) and a root to begin from, performs a shallow decomposition:
  1. Every vertex is assigned a non-negative label, so that a path between two vertices of equal label goes through a larger label
  2. The largest used label is minimized, and is at most floor(log2(n)).

### Complexity
- **Time**: $O(n)$ preprocess, at most $\log n$ parent iterations.
- **Memory**: $O(n)$

### Core Ideas
Greedy labelling in dfs + clever way to build the parent relationships from it.

### Tests and Benchmarks
- https://codeforces.com/contest/342/submission/370306705
- https://cses.fi/problemset/result/16845580/

### Source / Credit
Own