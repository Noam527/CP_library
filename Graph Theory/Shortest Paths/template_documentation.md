### Problem Statement
Single source / all pairs, positive / negative weights, you got them all:
- Bellman Ford with negative cycle detection and `prev` function.
- Dijkstra with `prev` function.
- Floyd Warshall (no negative cycle detection or `prev`).

### Complexity
- **Time**: $O(nm)$ for bellman ford, $O(m \log n)$ for dijkstra, $O(n^3)$ for floyd warshall
- **Memory**: Linear for single source, $O(n^2)$ for floyd warshall

### Core Ideas
In bellman ford, we do $n$ iterations to detect at least one vertex in every negative cycle, and then we do another phase to spread to the entire cycle.

In dijkstra, implement the `<` operator of `edge` in reverse order to use with priority queue.

### Tests and Benchmarks
- Dijkstra with path construction: https://judge.yosupo.jp/submission/237020
- Bellman ford with checking if there exists negative cycle on path: https://cses.fi/problemset/result/10581727/
- Floyd warshall: https://cses.fi/problemset/result/10581814/

### Source / Credit
Own