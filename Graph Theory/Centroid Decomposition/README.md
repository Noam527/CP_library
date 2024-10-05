### Problem Statement
Compute centroid decomposition of a tree.

### Complexity
- **Time**: $O(n \log n)$.
- **Memory**: $O(n)$.
- **High constant factor**

### Core Ideas
Computes the root, the levels and the parent connections of the centroid decomposition.<br>
Has a high constant factor because of many DFS's.

### Tests and Benchmarks
- Counting fixed length paths: https://codeforces.com/contest/161/submission/284487399

### Source / Credit
Own