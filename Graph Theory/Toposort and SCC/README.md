### Problem Statement
Compute strongly connected components and topological order.

### Complexity
- **Time**: Linear
- **Memory**: Linear

### Core Ideas
Find semi-topological order in the graph, then iterate on it and compute reachability in the transpose of the graph.

### Tests and Benchmarks
- Computing SCC: https://judge.yosupo.jp/submission/237048

### Source / Credit
Own