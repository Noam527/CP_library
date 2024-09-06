### Problem Statement
A data structure that handles insertion of linear functions and supports querying on the function maximizing / minimizing a given `x`-coordinate.<br>
Like CHT, but non-amortized.

### Complexity
- **Time**: $O(\log C)$, where $C$ is the number of supported `x`-coordinates.
- **Memory**: $O(n\log C)$

### Core Ideas
Maintain a segment tree where each node covers for an interval of `x` coordinates, and the invariant is that at any moment, the line that maximizes the given query is a line on the path from the root to the node of this `x` coordinate.
This way, an update is a recursive procedure so that if the new line intersects with the node's held line, then it may be switched (if the new line wins in the middle), and one of those lines is propagated downwards in exactly one direction in the segment tree.

### Tests and Benchmarks
- Minimum version: https://codeforces.com/contest/319/submission/280115350
- Maximum version: https://codeforces.com/contest/631/submission/280118184
- Minimum version (non-template version): https://codeforces.com/contest/319/submission/280115667
- Maximum version (non-template version): https://codeforces.com/contest/631/submission/280118109

### Source / Credit
- Own