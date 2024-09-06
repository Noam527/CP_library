### Problem Statement
Given a tree, the heavy light decomposition groups vertices into vertical chains (possibly containing a single vertex), so that any path from a vertex to the root contains at most $\log n$ chains.
When combined with a segment tree, allows handling complex updates and queries on trees.

### Complexity
- **Time**: $O(n)$ preprocessing, decomposing paths in $O(\log n)$.
- **Memory**: $O(n)$ without LCA, $O(n \log n)$ with LCA, due to binary lifting (can be improved with segtree).

### Core Ideas
We reorder the children of every node so that the heaviest child is the first. Then we perform dfs and maintain for each vertex, its index in the preorder traversal.<br>
This way, the preorder traversal makes it so subtrees are contiguous ranges, and any vertical path is of at most $\log n$ ranges.

The data structure does not contain a segment tree - it only receives a tree and handles decomposition queries.<br>
In addition, it also contains an LCA component, so that it can decompose not only vertical paths but any path.

This is to be used with an outer segment tree. This choice was because HLD has versatile usages, not only updating points and querying paths - sometimes on an update we would like to iterate over the chain to the root and do a more complex update (see for example, cat-dog from JOI18).<br>
Since it is hard to generalize these usages, and this code would be shorter, I prefer this approach better.

### Tests and Benchmarks
- Path queries: https://cses.fi/problemset/result/10429655/
- Subtree queries (without LCA): https://cses.fi/problemset/result/10429678/

### Source / Credit
Own