/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
*/
template<typename element>
struct segtree {
	int n;
	vector<element> t;
	segtree() {}
	segtree(int sz) {
		n = max(2, sz);
		while (n != (n & -n)) n += (n & -n);
		t.resize(2 * n, element());
	}
	template<typename T>
	segtree(const vector<T> &a) {
		n = max(2, (int)a.size());
		while (n != (n & -n)) n += (n & -n);
		t.resize(2 * n);
		for (int i = 0; i < (int)a.size(); i++)
			t[i + n - 1] = element(a[i]);
		for (int i = n - 2; i >= 0; i--)
			t[i] = t[2 * i + 1] * t[2 * i + 2];
	}
	void update(int pos, element val) {
		pos += n - 1;
		t[pos] = val;
		while (pos) {
			pos = (pos - 1) / 2;
			t[pos] = t[2 * pos + 1] * t[2 * pos + 2];
		}
	}
	// iterative, without assuming commutativity.
	element query(int l, int r) {
		if (l > r) return element();
		element L = element(), R = element();
		for (l += n - 1, r += n - 1; l < r; l = (l - 1) / 2, r = (r - 1) / 2) {
			if (!(l & 1)) L = L * t[l++];
			if (r & 1) R = t[r--] * R;
		}
		if (l == r) L = L * t[l];
		return L * R;
	}
	// returns (j, e) for first j such that e = [st, j] satisfies the given condition,
	// or (>=n, element()) if none
	template<class F>
	pair<int, element> first_from(int st, const F &good) {
		element bef;
		int j = first_from(st, good, bef, 0, 0, n - 1);
		if (j == n) bef = element();
		return {j, bef};
	}
	template<class F>
	int first_from(int st, const F &good, element &bef, int node, int nl, int nr) {
		if (st <= nl) {
			element nxt = bef * t[node];
			if (!good(nxt)) {
				bef = nxt;
				return n;
			}
			if (nl == nr) return bef = nxt, nl;
		}
		int mid = (nl + nr) / 2;
		if (st <= mid) {
			int j = first_from(st, good, bef, 2 * node + 1, nl, mid);
			if (j < n) return j;
		}
		return first_from(st, good, bef, 2 * node + 2, mid + 1, nr);
	}

	// returns (j, e) for last j such that e = [j, end] satisfies the given condition,
	// or (-1, element()) if none
	template<class F>
	pair<int, element> last_from(int end, const F &good) {
		element aft;
		int j = last_from(end, good, aft, 0, 0, n - 1);
		if (j == -1) aft = element();
		return {j, aft};
	}
	template<class F>
	int last_from(int end, const F &good, element &aft, int node, int nl, int nr) {
		if (nr <= end) {
			element nxt = t[node] * aft;
			if (!good(nxt)) {
				aft = nxt;
				return -1;
			}
			if (nl == nr) return aft = nxt, nl;
		}
		int mid = (nl + nr) / 2;
		if (mid < end) {
			int j = last_from(end, good, aft, 2 * node + 2, mid + 1, nr);
			if (j != -1) return j;
		}
		return last_from(end, good, aft, 2 * node + 1, nl, mid);
	}
};