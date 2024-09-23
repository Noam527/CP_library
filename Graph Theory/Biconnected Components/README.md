### Problem Statement
Compute edge-biconnected components / vertex-biconnected components of a (not necessarily connected) graph.<br>
A split to edge-biconnected components satisfies the following properties:
- Each vertex belongs to exactly one component.
- Every pair of vertices in the same component, have 2 *edge*-disjoint paths connecting them.
- An edge is called a **bridge** if its removal disconnects the graph. The bridges are precisely the edges connecting two different components.
- If each component is contracted to a single vertex, the resulting graph is a tree (or forest). For any pair of vertices, the number of edges whose removal disconnects these two vertices, is the distance between the vertices in the tree.

A split to vertex-biconnected components satisfies the following properties:
- Each edge belongs to exactly one component.
- Each vertex belongs to at least one component.
- A component contains a single vertex iff this vertex has no neighbors.
- Every pair of vertices in the same component, are either neighbors, or have 2 *vertex*-disjoint paths connecting them.
- A vertex is called a **cut / critical / articulation** vertex, if its removal disconnects the graph. The cut vertices are precisely the vertices that appear in more than 1 component.
- The following graph is a tree:
  - For each component, create a *white* node.
  - For each vertex in the original graph, create a *black* node.
  - Connect every white node to the black nodes belonging to its component.


### Complexity
- **Time**: $O(V + E)$
- **Memory**: $O(V + E)$

### Core Ideas
The constructions are very similar, but are also a bit particular on the details. It is surprising to me that I found a piece of code that solves these two problems with a difference of a single line.

The basic idea is that a dfs spanning tree is found (from an arbitrary root). Then every other edge is a back edge.<br>
A bridge is necessarily an edge in the spanning tree, and it's found as an edge whose subtree cannot reach any vertex above the subtree (using the back edges).<br>
To find vertex-biconnected components, if a node $v$ has an outgoing edge to a child $u$, and the subtree of $u$ cannot reach anything *strictly* above $v$, then $v$ is in a vertex-biconnected component with $u$, along with other vertices in the subtree of $u$.

Now clearly, vertex biconnected components are more painful to compute. Refer to the code. The things used in the code are:
- A single dfs that computes the dfs tree and the components at the same time.
- For each vertex, a `link` is computed as the lowest depth it can reach in the tree, via a single back edge in its subtree.
- A list of nodes is carried, that helps computing the biconnected component whenever it is determined we've found one (as explained above). To do this, it carries vertices throughout the dfs, and places borders between them using the variable `b = -1`. This helps simulate a stack of lists, with less code.

### Tests and Benchmarks
- Edge biconnected (with handling parallel edges): https://judge.yosupo.jp/submission/237428
- Vertex biconnected: https://judge.yosupo.jp/submission/237427

### Source / Credit
Own