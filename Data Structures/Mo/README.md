### Problem Statement
Given are a static array of objects and an *offline* list of range queries.
The required condition is that the answer to a set of elements can be updated quickly when a new element is inserted / old one is removed.

For the tree variant, values are either on vertices or on edges, and queries are on paths.

### Complexity
- **Time**: $O(N \cdot \sqrt{Q})$
- **Memory**: $O(N + Q)$
- **Offline**

### Core Ideas
Considering the queries as $Q$ points in $[0, N)^2$, one can find an ordering of them with total distance $O(N \cdot \sqrt{Q})$.
If we reorder the queries in such a way, then we can transition from each query to the next by adding / removing elements from the beginning / end of the current held segment.

For the tree variant, we do a DFS order where every node appears exactly twice, on entry and on exit.<br>
A query on a range, regards only the values of vertices that are seen exactly once in the range (instead of 0 or 2 times).<br>
- If the nodes are on a vertical chain, the subarray is from the 1st occurrence of the ancestor to the 1st occurrence of the lower vertex.
- Otherwise, It is from the 2nd occurrence of the first to appear, to the 1st occurrence of the second to appear, together with their LCA. This implementation asks for their LCA.

To support values on edges, you can set the node values to be the values on the edges to their parents - then it is the same as excluding their LCA, so you can send LCA = -1 in the implementation.

### Tests and Benchmarks
- Distinct values in range: https://cses.fi/problemset/result/10500267/
- Distinct vertex values on path (last submission): https://www.spoj.com/status/COT2,noam527/
- Mex of edge values on path: https://codeforces.com/gym/100962/my

### Source / Credit
Own.