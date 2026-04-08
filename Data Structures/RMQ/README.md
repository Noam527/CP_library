### Problem Statement
RMQ, generic with an element type, same as segtree

### Complexity
- **Time**: O(n \log n) preprocess, O(1) query
- **Memory**: O(n \log n)
- **Low constant factor**: Due to blocking optimization, the memory usage is actually n / 16 * log(n / 16) + O(n), and the running time of preprocessing is also optimized.

### Core Ideas
It is blocked which is nice; does the sparse table logic only on blocks of size 16, within them does prefix / suffix computations, and if a query is within a single block then does upto 16 operations.

### Tests and Benchmarks
- Tested the constant; 16 is optimal in time complexity, and memory wise it is pretty good.
  - https://judge.yosupo.jp/submission/364934 (also look at nearby submissions)

### Source / Credit
Me