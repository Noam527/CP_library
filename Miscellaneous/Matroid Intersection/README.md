### Problem Statement
Given two matroids over the same ground set, find the maximum-sized set that is independent in both of them.<br>
This is the unweighted version - for weighted, use bellman ford instead of bfs.

### Complexity
- **Time**: $O(r(rC_1 + nC_2 + n(A_1 + A_2)))$, where:
  - $n = |X|$, size of ground set
  - $r$ is the rank (=size) of the solution set
  - $C_1, C_2$ are the running times of `neigh` calls on $M_1$ and $M_2$. Note the asymmetry - you will prefer to have $C_1 \geq C_2$.
  - $A_1, A_2$ are the running times of `can_add` calls on $M_1$ and $M_2$.
- **Memory**: $O(n)$ + memory consumed by inner implementation (probably also $O(n)$).

### Core Ideas
All the theory is explained in the blogpost attached below.<br>
I want to mention a few important things:
1. The answer doesn't depend on the order of $M_1, M_2$, but the complexity does. Notice that `neigh` in both matroids needs to compute slightly different things - neighbors outside $S$ and neighbors inside $S$ in the bipartite graph. The rule of thumb - $M_1$ needs to support insertions / `can_add`s easily, while $M_2$ needs to support deletions easily.
2. I perform lazy BFS, which according to the blogpost below should improve running time asymptotics by $O(\sqrt{r})$ - but it doesn't explain how exactly. So until I know for sure I won't state a better complexity.
3. For the weighted version, use bellman ford instead of BFS. In particular, this won't be lazy.

### Tests and Benchmarks
- Intersection of graphic and colorful ($r,n = 800$ in ~100ms): https://codeforces.com/contest/1284/submission/284318032

### Source / Credit
The implementation is my own, but the entire theory is from here: https://codeforces.com/blog/entry/69287