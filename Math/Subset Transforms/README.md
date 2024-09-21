### Problem Statement
Given an array $a$ of size $2^n$ (or two arrays $a, b$), compute the following functions:
- Zeta transform: $z(s) = \sum_{i \subseteq s} a(i)$
- Mobius transform: $\mu (s) = \sum_{i \ subseteq s} a(i) \cdot (-1)^{|s-i|}$
- Subset convolution: $c(s) = \sum_{i \cupdot j = s} a(i)b(j)$

### Complexity
- **Time**: $O(n2^n)$ for zeta and mobius transforms, $O(n^22^n)$ for subset convolution.
- **Memory**: $O(n)$ inplace for zeta and mobius, $O(n2^n)$ for subset convolution.

### Core Ideas
Zeta transform is surprisingly simple: for any bit in $b \in [0, n)$, take all $i \in [0, 2^n)$ with bit $b$ and do `a[i] += a[i - b]`.<br>
The next observation is that the mobius transform is the inverse of the zeta transform, so its code is just as simple: `a[i] -= a[i - b]`.<br>

For subset convolution of $a, b$ define the following:
- $a_i(s)$ as $a(s)$ if $s$ has exactly $i$ bits, otherwise 0. Define $b_i(s)$ similarly.
- $c_i = \sum_{0<=j<=i} z(a_j) \cdot z(b_{i-j})$.
- Then finally, for each $s$ with $b$ bits, $c(s) = \mu (c_b)(s)$.

### Tests and Benchmarks
- Subset convolution: https://judge.yosupo.jp/submission/237000

### Source / Credit
Own.