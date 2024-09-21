### Problem Statement
Find maximum flow in a graph using dinitz.

### Complexity
- **Time**: $O(VE \log U)$ in general graphs, $O(E \sqrt E)$ in unit capacity graphs, $O(E \sqrt V)$ in maximum matching graphs.
- **Memory**: Linear.

### Core Ideas
Uses dinitz with capacity scaling - first does scaling, then performs the entire dinitz. Thus at every iteration of scaling, the maximum flow is bounded by $E$, and so dinitz runs in $O(V\cdot f) = O(VE)$, for a total of $O(VE \log U)$.<br>
In unit capacity graphs, $O(E \sqrt E)$ since there are $O(\sqrt E)$ phases of blocking flow, and each blocking flow takes $O(E)$.<br>
In graphs where each vertex allows at most one path, $O(E \sqrt V)$, since there are $O(\sqrt V)$ phases of blocking flow.

### Tests and Benchmarks
My implementation:
- Maximum flow: https://www.spoj.com/status/FASTFLOW,noam527/
- Maximum matching: https://www.spoj.com/status/MATCHING,noam527/

KACTL's implementation: I used it in bipartite matching.

### Source / Credit
https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/Dinic.h, but also rewritten to my style.