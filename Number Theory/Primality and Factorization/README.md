### Problem Statement
Primality checking and factorization.

### Complexity
- **Time**: Primality - polylog deterministic. Factorization: expected $O(N^{1/4})$, better in practice
- **Memory**: $O(1)$ / $O(#factors)$

### Core Ideas
Primality: Miller rabin, with hardcoded values that work for upto $7\cdot 10^{18}$.

Factorization: pollard rho, with some constant optimizations

### Tests and Benchmarks
- Factorization (which also required primality testing): https://judge.yosupo.jp/submission/237394

### Source / Credit
KACTL's ICPC notebook.