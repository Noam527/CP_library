/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
also note the "using T = ll". this is the range of indicies we allow. can change to int for efficiency.
*/
template<typename element>
struct segtree {
	using T = int;
	struct node {
		element val;
		T l, r;
		node(element v = element()) {
			l = -1, r = -1, val = v;
		}
	};
	T L, R;
	vector<node> t;
	segtree() {}
	segtree(T LL, T RR) {
		L = LL, R = RR;
		t.push_back(node());
	}
	int add_node() {
		t.push_back(node());
		return (int)t.size() - 1;
	}
	int go_left(int v) {
		if (t[v].l == -1) {
			// this prevents a bug that might occur when t.push_back provokes reallocation
			int x = add_node();
			t[v].l = x;
		}
		return t[v].l;
	}
	int go_right(int v) {
		if (t[v].r == -1) {
			// this prevents a bug that might occur when t.push_back provokes reallocation
			int x = add_node();
			t[v].r = x;
		}
		return t[v].r;
	}
	void fix(int v) {
		// assumes v has at least 1 child
		if (t[v].l == -1) t[v].val = t[t[v].r].val;
		else if (t[v].r == -1) t[v].val = t[t[v].l].val;
		else t[v].val = t[t[v].l].val * t[t[v].r].val;
	}
	void update(T pos, element val) {
		update(pos, val, 0, L, R);
	}
	void update(T pos, element val, int node, T nl, T nr) {
		if (nl == nr) {
			t[node].val = val;
			return;
		}
		T mid = (nl + nr) / 2;
		if (pos <= mid) update(pos, val, go_left(node), nl, mid);
		else update(pos, val, go_right(node), mid + 1, nr);
		fix(node);
	}
	element query(T l, T r) {
		if (l > r) return element();
		return query(l, r, 0, L, R);
	}
	element query(T l, T r, int node, T nl, T nr) {
		if (r < nl || nr < l) return element();
		if (l <= nl && nr <= r) return t[node].val;
		T mid = (nl + nr) / 2;
		if (r <= mid || t[node].r == -1) {
			if (t[node].l == -1) return element();
			return query(l, r, go_left(node), nl, mid);
		}
		if (mid < l || t[node].l == -1)
			return query(l, r, go_right(node), mid + 1, nr);
		return query(l, r, t[node].l , nl, mid) * query(l, r, t[node].r, mid + 1, nr);
	}
};
