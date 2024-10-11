### Problem Statement
Given a set of points, supports updates of deleting / re-inserting those points, and querying for given $(a, b)$ where $b \geq 0$, which of the current "active" points maximizes the value $ax + by$ (dot product).<br>
In particular, this allows querying data on the convex hull. For example, the convex hull can be found in $O(k \log n)$ where $k$ is the number of vertices on it.<br>

Note that the $b \geq 0$ requirement mentioned above is just saying that this can maintain the upper hull. For lower hull, rotate the points by 180 degrees (so that the order stays the same).

### Complexity
- **Time**: $O(n \log n)$ construction (unless points are sorted, then $O(n)$), $O(\log^2 n)$ for update, $O(\log n)$ for query.
- **Memory**: $O(n)$

### Core Ideas
(The idea is from the blogpost linked below)<br>
We maintain an upper convex hull using a segment tree. Regarding corner cases:
- The convex hull is strict, has no 180 degree vertices.
- The left vertical edge (if it exists) is considered, while the right one is not.

Maybe in the future I'll bother writing up the idea here, but for now the blogpost is short enough.

### Tests and Benchmarks
- Did local testing for correctness of the dot product queries, not of the convex hull (see file in this directory).
- Convex hull layers in $O(n \log^2 n)$: https://judge.yosupo.jp/submission/241577

### Source / Credit
Implementation is my own, idea is from: https://codeforces.com/blog/entry/75929