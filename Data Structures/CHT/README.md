### Problem Statement
A data structure that handles insertions of linear functions `y = slope * x + constant`, and can answer the query: given `x`, find the linear function minimizing / maximizing evaluation at `x`.

### Complexity
- **Time**: $O(\log n)$
- **Memory**: $O(n)$
- **Amortized**

### Core Ideas
W.L.O.G consider the maximum case. We maintain the upper convex hull of the lines, sorted by their increasing slopes.<br>
Each line also holds its intersection `x`-coordinate with the next line (or $\infty$ otherwise).<br>
Insertion is amortized as we may need to do a lot of deletions.

In practice, an `std::set` is used to maintain the lines sorted by slope, but lines also carry their intersection with the following line, so that queries can be implemented using `std::set` operations, and a comparator is defined that handles differently real lines and queries (lines carrying the `x` query).

### Tests and Benchmarks
- https://codeforces.com/contest/319/submission/280101417

### Source / Credit
- Own.
