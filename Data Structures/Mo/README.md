### Problem Statement
Given are a static array of objects and an *offline* list of range queries.
The required condition is that the answer to a set of elements can be updated quickly when a new element is inserted / old one is removed.

### Complexity
- **Time**: $O(N \cdot \sqrt{Q})$
- **Memory**: $O(N + Q)$
- (Optional) **Offline**

### Core Ideas
Considering the queries as $Q$ points in $[0, N)^2$, one can find an ordering of them with total distance $O(N \cdot \sqrt{Q})$.
If we reorder the queries in such a way, then we can transition from each query to the next by adding / removing elements from the beginning / end of the current held segment.

### Tests and Benchmarks
- Distinct values in range: https://cses.fi/problemset/result/10500267/

### Source / Credit
Own.