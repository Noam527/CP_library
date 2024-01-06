/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator * with another element, to combine with a right operand and return the result
* operator * with a tag, to apply the tag on the element

the struct 'tag' must have:
* neutral element (as default constructor)
* operator * with another tag: the right operand is the later update
*/
template<typename element, typename tag>
struct segtree {
	int n;
	vector<tag> lazy;
	vector<element> t;
	segtree() {}
	segtree(int sz) {
		n = max(2, sz);
		while (n != (n & -n)) n += (n & -n);
		lazy.resize(2 * n, tag());
		t.resize(2 * n, element());
	}
	segtree(const vector<element> &a) {
		n = max(2, (int)a.size());
		while (n != (n & -n)) n += (n & -n);
		lazy.resize(2 * n, tag());
		t.resize(2 * n);
		for (int i = 0; i < a.size(); i++)
			t[i + n - 1] = a[i];
		for (int i = n - 2; i >= 0; i--)
			t[i] = t[2 * i + 1] * t[2 * i + 2];
	}
	void push(int x) {
		t[x] = t[x] * lazy[x];
		if (x < n - 1) {
			lazy[x + x + 1] = lazy[x + x + 1] * lazy[x];
			lazy[x + x + 2] = lazy[x + x + 2] * lazy[x];
		}
		lazy[x] = tag();
	}
	void fix(int x) {
		t[x] = (t[x + x + 1] * lazy[x + x + 1]) * (t[x + x + 2] * lazy[x + x + 2]);
	}
	void update(int l, int r, tag v) {
		if (l > r) return;
		update(l, r, v, 0, 0, n - 1);
	}
	void update(int l, int r, const tag &v, int node, int nl, int nr) {
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[node] = lazy[node] * v;
			return;
		}
		push(node);
		int mid = (nl + nr) / 2;
		update(l, r, v, 2 * node + 1, nl, mid);
		update(l, r, v, 2 * node + 2, mid + 1, nr);
		fix(node);
	}
	element query(int l, int r) {
		if (l > r) return element();
		return query(l, r, 0, 0, n - 1);
	}
	element query(int l, int r, int node, int nl, int nr) {
		if (r < nl || nr < l) return element();
		if (l <= nl && nr <= r)
			return t[node] * lazy[node];
		int mid = (nl + nr) / 2;
		return (query(l, r, 2 * node + 1, nl, mid) * query(l, r, 2 * node + 2, mid + 1, nr)) * lazy[node];
	}
};
