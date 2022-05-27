/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
note the "using T = ll". this is the range of indicies we allow. can change to int for efficiency.
note the static constant LIM. used for efficiency of both time and memory. practice shows that 64 or 128 are the best.
this entire thing assumes commutativity (which is acceptable since the order of operations is weird in 2D).
*/
template<typename element>
struct segtree {
	using T = int;
	struct node {
		element val;
		int l, r;
		node(element v = element()) {
			l = -1, r = -1, val = v;
		}
	};
	T L, R;
	vector<node> t;

	// constant optimizations
	static const int LIM = 64;
	vector<pair<T, element>> last;
	bool big;
	T cache_i;
	element cache_v;

	segtree() {}
	segtree(T LL, T RR) {
		L = LL, R = RR;
		t.push_back(node());
		
		big = 0;
		cache_i = L;
		cache_v = element();
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
		cache_i = pos;
		cache_v = val;
		if (big) {
			update(pos, val, 0, L, R);
			return;
		}
		bool found = false;
		for (auto &i : last) {
			if (i.first == pos) {
				i.second = val;
				found = true;
				break;
			}
		}
		if (!found) last.emplace_back(pos, val);
		if (last.size() < LIM) return;
		for (const auto &i : last)
			update(i.first, i.second, 0, L, R);
		last.clear();
		big = 1;
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
	element get(T i) {
		if (i == cache_i) return cache_v;
		if (!big) {
			for (const auto &j : last)
				if (j.first == i) return j.second;
			return element();
		}
		int node = 0;
		T l = L, r = R;
		while (l < r) {
			T mid = (l + r) / 2;
			if (i <= mid) {
				if (t[node].l == -1) return element();
				node = t[node].l;
				r = mid;
			}
			else {
				if (t[node].r == -1) return element();
				node = t[node].r;
				l = mid + 1;
			}
		}
		return t[node].val;
	}
	element query(T l, T r) {
		if (l > r) return element();
		if (!big) {
			element res;
			for (const auto &i : last)
				if (l <= i.first && i.first <= r)
					res = res * i.second;
			return res;
		}
		return query(l, r, 0, L, R);
	}
	element query(T l, T r, int node, T nl, T nr) {
		if (r < nl || nr < l) return element();
		if (l <= nl && nr <= r) return t[node].val;
		T mid = (nl + nr) / 2;
		if (r <= mid || t[node].r == -1) {
			if (t[node].l == -1) return element();
			return query(l, r, t[node].l, nl, mid);
		}
		if (mid < l || t[node].l == -1)
			return query(l, r, t[node].r, mid + 1, nr);
		return query(l, r, t[node].l, nl, mid) * query(l, r, t[node].r, mid + 1, nr);
	}
};

template<typename element>
struct segtree2D {
	int n;
	vector<segtree<element>> t;
	segtree2D() {}
	segtree2D(int nn, int l1, int r1) {
		n = nn;
		t.resize(2 * n, segtree<element>(l1, r1));
	}
	void fix(int node, int pos1) {
		element val = t[2 * node + 1].get(pos1) * t[2 * node + 2].get(pos1);
		t[node].update(pos1, val);
	}
	void update(int pos0, int pos1, element val) {
		pos0 += n - 1;
		t[pos0].update(pos1, val);
		while (pos0) {
			pos0 = (pos0 - 1) / 2;
			fix(pos0, pos1);
		}
	}
	element query(int l0, int r0, int l1, int r1) {
		element res;
		for (l0 += n - 1, r0 += n - 1; l0 < r0; l0 = (l0 - 1) / 2, r0 = (r0 - 1) / 2) {
			if (!(l0 & 1)) res = res * t[l0++].query(l1, r1);
			if (r0 & 1) res = res * t[r0--].query(l1, r1);
		}
		if (l0 == r0) res = res * t[l0].query(l1, r1);
		return res;
	}
};
