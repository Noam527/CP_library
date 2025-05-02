### Problem Statement
Segment tree...

### Complexity
- **Time**: $O(\log n)$
- **Memory**: $O(n)$

### Core Ideas
Just a segment tree. It does, however, use the iterative version on non-lazy segtrees *without* assuming commutativity.
Also has memory and time optimizations in the 2D versions.

### Tests and Benchmarks
- Classic segtree and lazy segtree, been used above 20 times it's all good.
- 2D sparse segtree: https://oj.uz/submission/1087910 (ran in 1.7s out of 13s!)
- 1D sparse segtree:
  - As is, forced sparsity (multiplied indicies by 777): https://judge.yosupo.jp/submission/237380
  - Without (2D)optimizations and `get`: https://judge.yosupo.jp/submission/237384

- Multidimensional sparse:
  - As is, forced sparsity (multiplied indicies by 777): https://judge.yosupo.jp/submission/249811
  - With 1D optimization, IOI13 Game: https://oj.uz/submission/1113071
  - SWERC21 (not necessary, but good benchmark): https://codeforces.com/contest/1662/submission/291669531

- Range affine range sum: https://judge.yosupo.jp/submission/283019

### Source / Credit
Own