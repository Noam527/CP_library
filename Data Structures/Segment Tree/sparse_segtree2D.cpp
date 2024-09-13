/*
* note the "using T = int". this is the range of indicies we allow.
* note the static constant LIM. used for efficiency of both time and memory. practice shows that 64 or 128 are the best.
* ASSUMES COMMUTATIVITY - to fix, make `query` call the recursive version immediately (i.e no use of `big`).
*/
template<typename element>
struct segtree {
	using T = int;
	struct node {
		element val;
		int c[2];
		node(element v = element()) : c({ 0,0 }), val(v) {}
		int& operator [](int i) {
			return c[i];
		}
	};
	T L, R;
	vector<node> t;
	static const int LIM = 64;
	vector<pair<T, element>> last;
	bool big;
	T cache_i;
	element cache_v;

	segtree() {}
	segtree(T LL, T RR) : L(LL), R(RR) {
		t.push_back(node()); // dummy
		t.push_back(node()); // root
		big = 0;
		cache_i = L;
		cache_v = element();
	}
	int add_node() {
		t.push_back(node());
		return (int)t.size() - 1;
	}
	int go(int v, int dir) {
		if (!t[v][dir]) {
			int x = add_node(); // prevents bug from reallocation
			t[v][dir] = x;
		}
		return t[v][dir];
	}
	void fix(int v) {
		t[v].val = t[t[v][0]].val * t[t[v][1]].val;
	}
	void update(T pos, element val) {
		cache_i = pos, cache_v = val;
		if (big) {
			update(pos, val, 1, L, R);
			return;
		}
		bool found = false;
		for (auto& i : last) {
			if (i.first == pos) {
				i.second = val;
				found = true;
				break;
			}
		}
		if (!found) last.emplace_back(pos, val);
		if (last.size() < LIM) return;
		for (const auto& i : last)
			update(i.first, i.second, 1, L, R);
		last.clear();
		big = 1;
	}
	void update(T pos, element val, int node, T nl, T nr) {
		if (nl == nr) {
			t[node].val = val;
			return;
		}
		T mid = (nl + nr) / 2;
		if (pos <= mid) update(pos, val, go(node, 0), nl, mid);
		else update(pos, val, go(node, 1), mid + 1, nr);
		fix(node);
	}
	// implement only if you need quick access to a single index (instead of range)
	element get(T i) {
		if (i == cache_i) return cache_v;
		if (!big) {
			for (const auto& j : last)
				if (j.first == i) return j.second;
			return element();
		}
		int node = 1;
		T l = L, r = R;
		while (l < r) {
			T mid = (l + r) / 2;
			if (i <= mid) {
				if (!t[node][0]) return element();
				node = t[node][0];
				r = mid;
			}
			else {
				if (!t[node][1]) return element();
				node = t[node][1];
				l = mid + 1;
			}
		}
		return t[node].val;
	}
	element query(T l, T r) {
		if (l > r) return element();
		if (!big) {
			element res;
			for (const auto& i : last)
				if (l <= i.first && i.first <= r)
					res = res * i.second;
			return res;
		}
		return query(l, r, 1, L, R);
	}
	element query(T l, T r, int node, T nl, T nr) {
		if (r < nl || nr < l) return element();
		if (l <= nl && nr <= r) return t[node].val;
		T mid = (nl + nr) / 2;
		if (r <= mid || !t[node][1]) {
			if (!t[node][0]) return element();
			return query(l, r, t[node][0], nl, mid);
		}
		if (mid < l || !t[node][0])
			return query(l, r, t[node][1], mid + 1, nr);
		return query(l, r, t[node][0], nl, mid) * query(l, r, t[node][1], mid + 1, nr);
	}
};

template<typename element>
struct segtree2D {
	using T = int;
	struct node {
		segtree<element> val;
		int c[2];
		node() {}
		node(T L, T R) : c({0, 0}), val(L, R) {}
		int& operator [](int i) {
			return c[i];
		}
	};
	T L0, R0, L1, R1;
	vector<node> t;
	segtree2D() {}
	segtree2D(T l0, T r0, T l1, T r1) : L0(l0), R0(r0), L1(l1), R1(r1) {
		t.push_back(node()); // dummy
		t.push_back(node(L1, R1)); // root
	}
	int add_node() {
		t.push_back(node(L1, R1));
		return (int)t.size() - 1;
	}
	int go(int v, int dir) {
		if (!t[v][dir]) {
			int x = add_node(); // prevents bug from reallocation
			t[v][dir] = x;
		}
		return t[v][dir];
	}
	void fix(int node, T pos1) {
		// assumes node has at least 1 child
		element val;
		if (!t[node][0]) val = t[t[node][1]].val.get(pos1);
		else if (!t[node][1]) val = t[t[node][0]].val.get(pos1);
		else val = t[t[node][0]].val.get(pos1) * t[t[node][1]].val.get(pos1);
		t[node].val.update(pos1, val);
	}
	void update(T pos0, T pos1, element val) {
		update(pos0, pos1, val, 1, L0, R0);
	}
	void update(T pos0, T pos1, element val, int node, T nl, T nr) {
		if (nl == nr) {
			t[node].val.update(pos1, val);
			return;
		}
		T mid = (nl + nr) / 2;
		if (pos0 <= mid) update(pos0, pos1, val, go(node, 0), nl, mid);
		else update(pos0, pos1, val, go(node, 1), mid + 1, nr);
		fix(node, pos1);
	}
	element query(T l0, T r0, T l1, T r1) {
		if (l0 > r0 || l1 > r1) return element();
		return query(l0, r0, l1, r1, 1, L0, R0);
	}
	element query(T l0, T r0, T l1, T r1, int node, T nl, T nr) {
		if (r0 < nl || nr < l0) return element();
		if (l0 <= nl && nr <= r0) {
			return t[node].val.query(l1, r1);
		}
		T mid = (nl + nr) / 2;
		if (r0 <= mid || !t[node][1]) {
			if (!t[node][0]) return element();
			return query(l0, r0, l1, r1, t[node][0], nl, mid);
		}
		if (mid < l0 || !t[node][0])
			return query(l0, r0, l1, r1, t[node][1], mid + 1, nr);
		return query(l0, r0, l1, r1, t[node][0], nl, mid) * query(l0, r0, l1, r1, t[node][1], mid + 1, nr);
	}
};