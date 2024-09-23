### Problem Statement
Compute delaunay triangulation of a set of points.

### Complexity
- **Time**: $O(n \log n)$
- **Memory**: $O(n)$

### Core Ideas
Black magic.<br>
Interesting properties:
- Dual of voronoi diagram.
- Every point has an edge in the triangulation to its closest point.
- Maximizes the minimum angle in the triangles.
- The edges of the triangulation contain the edges of the euclidean MST.

### Tests and Benchmarks
- Euclidean MST (with removal of duplicates and adding dummy points): https://judge.yosupo.jp/submission/237491

### Source / Credit
KACTL's ICPC notebook.