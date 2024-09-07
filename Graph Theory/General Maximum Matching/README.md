### Problem Statement
Given an undirected graph, compute the maximum matching in it.

### Complexity
- **Time**: $O(VE)$
- **Memory**: $O(V + E)$

### Core Ideas
The following explanation is a reduced version of the excellent blogpost below.<br>
We will call a vertex that is unmatched "exposed". A correct algorithm to find a maximum matching is to repeatedly find augmenting paths: paths that begin and end at exposed vertices, and along the path the edges alternate between current matched and unmatched edges.<br>
The elegant proof: take a non-maximum matching $M_1$ and a maximum matching $M_2$. Consider the graph $M_1 \oplus M_2$ - created by edges existing in exactly one of the 2 matchings. In this graph, all degrees are at most 2, so it consists of cycles and paths, and the cycles are even due to matching property. This graph also contains more edges from $M_2$ than $M_1$, so it must contain a component that is a path beginning and ending with edges from $M_2$ - an augmenting path for $M_1$.

While it may seem that the problem is over, and we can actually just repeatedly begin searches from exposed vertices (while keeping in mind if the last edge taken was matched or not), this approach could lead us to find augmenting paths that are not **simple**. This happens because of cycles of size $2k + 1$, containing $k$ matched edges - these are named "blossoms".

The blossom algorithm contract each blossom into a single vertex, under the observation that a graph has an augmenting path before contraction iff it has one afterwards - an augmenting path that passes through a blossom can be lifted into a proper path in the original graph.

The implementation details are quite complex to make it run in $O(V^3)$ or $O(VE)$.

### Tests and Benchmarks
- Library Checker: https://judge.yosupo.jp/submission/233767

### Source / Credit
For reading up on it and about implementation details, read at https://codeforces.com/blog/entry/92339.<br>
However, this particularly elegant implementation is stolen from bicsi at https://codeforces.com/blog/entry/92339?#comment-810242.