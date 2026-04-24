### Problem Statement
Rolling hash.

### Complexity
- **Time**: $O(n)$ construction, $O(1)$ equality check, $O(\log n)$ lcp computation.
- **Memory**: $O(n)$

### Core Ideas
For the given MOD and N, a comparison between two different strings has probability 1 / MOD^N to report equality. So choose MOD and N properly

### Tests and Benchmarks
- Z algorithm: https://judge.yosupo.jp/submission/368483
  - Same but with double construction (to prove the bases are the same on different instances): https://judge.yosupo.jp/submission/368484

### Source / Credit
Me