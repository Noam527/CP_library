### Problem Statement
Given an $n$ by $m$ matrix that satisfies the following property, uses at most $4(n + m)$ lookups into the matrix to find for each row, the index of the minimum value.
- For any submatrix (defined by a subset of rows and subset of columns), define $L(i)$ for $1 \leq i \leq n$ as the index of the leftmost minimum value in row $i$. Then $L(i) \leq L(i + 1)$.

This is equivalent to the following criteria:
- For any row $x$ and columns $y_1 < y_2$: if $a[x][y_1] >(=) a[x][y_2]$ then $a[x+1][y_1] >(>=) a[x+1][y_2]$.

Less formally, for any pair of columns, if you iterate over their entries from top to bottom and compare them, then the signs will first be `<`, then `=` and then `>`.

### Complexity
- **Time**: upto $4(n + m)$ accesses.
- **Memory**: $O(n + m)$.

### Core Ideas
Read the blog below.
Note that to recover the values themselves, you can cache entries which were looked up, and simply look them up again.

### Tests and Benchmarks
- Direct usage: https://codeforces.com/contest/1423/submission/284347931

### Source / Credit
Implementation by Catom
Blog: https://codeforces.com/blog/entry/110844