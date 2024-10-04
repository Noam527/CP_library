### Problem Statement
Compute longest increasing subsequence (both strictly increasing and non-decreasing).

### Complexity
- **Time**: $O(n \log n)$.
- **Memory**: $O(n)$.

### Core Ideas
Uses short `map` implementation.<br>
Note that to compute non-decreasing of array $a_i$, you can compute strictly increasing of pairs: $b_i = (a_i, i)$.

### Tests and Benchmarks
- Direct problem: https://judge.yosupo.jp/submission/239831

### Source / Credit
Own