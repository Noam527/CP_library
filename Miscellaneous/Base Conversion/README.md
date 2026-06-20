### Problem Statement
Converts a vector in some basis (or basis vector) to some other vector in another basis (or basis vector).
Useful for communication problems.

Does not preserve leading zeroes. To preserve, prepend a `1`.

### Complexity
- **Time**: $O(nm)$ if `n` is the current representation length and `m` is the new one.
- **Memory**: $O(n + m)$

### Core Ideas
Represents the given vector as a number with the provided basis, and does long division and modulo operations to get the new vector.

### Tests and Benchmarks
None, tested locally

### Source / Credit
Me