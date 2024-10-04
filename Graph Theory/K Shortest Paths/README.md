### Problem Statement
Given a directed weighted graph, possibly with self loops and parallel edges, compute the $k$ shortest path distances from $s$ to $t$.

### Complexity
- **Time**: $O(E \log E + k \log k)$.
- **Memory**: $O(E \log E + k)$.

### Core Ideas
The following is a shortened version of the blogpost attached below. The steps are:
1. Compute $d_v$ and $p_v$ as the distance from $v$ to $t$ and the parent vertex.
2. For any edge that does not connect a node to its parent, call it a "sidewalk". Define the cost of the sidewalk $(u,v,w)$ as $d_v + w - d_u \geq 0$.
3. Define a new graph $G'$ in which the edges outgoing from $v$ are the sidewalks going out of $v, p_v, p_{p_v}, ...$, each with its cost defined above and leading to the vertex which is the destination of the sidewalk. There is a bijection between $s-t$ paths in $G$ and $s$ paths in $G'$ (paths starting from $s$) - we just need to do $k$ dijkstra iterations on $G'$.
4. The problem is that any vertex may have $O(E)$ neighbors in $G'$ - which affects running time of both construction and dijkstra. However, if we had the neighbors of each node ordered by weight, then it would solve the dijkstra running time issue, and if we made it persistent (each node inherits the data structure from its parent), then it would solve the construction time issue.
5. To do this, we use a simple heap that can handle insertions (+persistently), and iterations on minimums, efficiently. We can use the following heap:
  - Each heap node has at most 2 children, and its key is smaller than (or equal to) the keys of its children. Each node also maintains a "rank" - the distance to the closest leaf / closest non existent node.
  - The invariant to be held: The rank of the left child is always at least the rank of the right. With this in mind, the rank of the right is always at most $\log n$, and insertions are done easily - either the new key is the new root, or insert to the right, and if the right rank exceeds the left rank, swap them.
  - To support persistency, define the entire structure as a big set of nodes. Each heap points to a specific node, which is its root. **Never** change node values once created, always create new nodes upon insertion (along the entire path). This way, every node has at most 2 children, while it may have an arbitrary number of parents - but this structure doesn't care about the parents.
6. Build the heaps in a search-like manner from $t$ downwards the tree.
7. Perform a dijkstra, where in each iteration you pop a new distance and the current node, and insert its children, and the root of the heap corresponding to the sidewalk of this node.

An additional note - we do not delete heap elements because of self loops - we want to allow using the same sidewalk multiple times.

### Tests and Benchmarks
- By definition problem (with self loops and parallel edges): https://judge.yosupo.jp/submission/239667

### Source / Credit
The implementation is my own but inspired by the python implementation in this blogpost, which also covers the theory behind the topic: https://codeforces.com/blog/entry/102085