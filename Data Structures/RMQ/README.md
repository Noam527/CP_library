### Problem Statement
RMQ, generic with an element type, same as segtree

### Complexity
- **Time**: O(n \log n) preprocess, O(1) query
- **Memory**: O(n \log n)

### Core Ideas
It is blocked which is nice; does the sparse table logic only on blocks of size 16, within them does prefix / suffix computations, and if a query is within a single block then does upto 16 operations

### Tests and Benchmarks
- Tested the constant; 8 and 16 are about the same in time, but 16 is less memory.
  - https://judge.yosupo.jp/submission/364864 (also look at submissions with a nearby ID)

### Source / Credit
Me