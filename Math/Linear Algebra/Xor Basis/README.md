### Problem Statement
Maintain a xor basis. Supports multiple convenient functions (like minimizing / maximizing subset xor, maintaining dimensions and which xor is representable).

### Complexity
- **Time**: All operations work in $O(dim)$.
- **Memory**: $O(dim)$.

### Core Ideas
Maintaining the basis like in gaussian elimination. In practice, each vector is an integer and the basis is sorted in decreasing order (represents the fact that the leading bits in each "row" are "increasing").

### Tests and Benchmarks
- Maximize subset xor: https://www.spoj.com/status/XMAX,noam527/

### Source / Credit
Own.