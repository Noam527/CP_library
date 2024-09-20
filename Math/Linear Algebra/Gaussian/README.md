### Problem Statement
Perform gaussian elimination on a matrix, and also anything that can use it:
- Gaussian elimination
- Determinant, basis, rank computation
- Matrix inverse
- Solve linear equations
This implementation is a template! supports both doubles and integers in modulo $p$ (if used with the `mint` class).

### Complexity
- **Time**: Gaussian elimination in $O(nm \min(n, m))$ where $n$ is #rows and $m$ is #columns.<br>
            Everything else uses it directly, so same complexity.<br>
- **Memory**: $O(nm)$

### Core Ideas
Usual gaussian elimination. In terms of implementation, `gaussian` returns the determinant and inside also computes rank and basis (see inner comment).<br>
Everything is inplace! (the matrix is destroyed, copy beforehand if you need).

### Tests and Benchmarks
Under prime modulo:
- Determinant (basically calling `gaussian`): https://judge.yosupo.jp/submission/236890
- Inverse: https://judge.yosupo.jp/submission/236891
- Rank: https://judge.yosupo.jp/submission/236878
- Solving a linear system of equations, *all solution space*: https://judge.yosupo.jp/submission/236893

In reals, only did manual tests.

### Source / Credit
Own