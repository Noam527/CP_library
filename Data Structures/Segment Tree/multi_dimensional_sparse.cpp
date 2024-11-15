template<int D, typename element, ll N>
struct segtree {
	template<int d> using sdim = segtree<d, element, N>;
#define mid (nl + (nr - nl) / 2) // IMP: undef in the end
#define templatic template<class... T> // IMP: undef in the end
	struct node {
		int c[2];
		sdim<D - 1> val;
		node() { c[0] = c[1] = 0; }
		int& operator[](int i) { return c[i]; };
	};
	vector<node> t;
	static constexpr int LIM = (D == 1) * 64; // 64 or 128
	vector<pair<ll, element>> cache;

	segtree() : t(1) {}
	int add_node() {
		t.push_back(node());
		return (int)t.size() - 1;
	}
	int go(int n, int d) {
		if (!t[n][d]) {
			int x = add_node();
			t[n][d] = x;
		}
		return t[n][d];
	}
	templatic element get(ll i, T... nxt) {
		if (t.size() == 1) {
			element res;
			for (auto& x : cache)
				if (x.first == i) res = x.second;
			return res;
		}
		int n = 0; ll l = 0, r = N, m;
		do {
			m = l + (r - l) / 2;
			if (i < m) n = t[n][0], r = m;
			else n = t[n][1], l = m;
		} while (n && l + 1 < r);
		if (!n) return element();
		return t[n].val.get(nxt...);
	}
	templatic element update(element x, ll i, T... nxt) {
		if (t.size() == 1) {
			bool found = false;
			for (auto& v : cache)
				if (v.first == i) v.second = x, found = true;
			if (!found) cache.emplace_back(i, x);
			if (cache.size() < LIM) return x;
			for (auto& v : cache)
				upd(v.second, 0, 0, N, v.first, nxt...);
			return cache.clear(), x;
		}
		return upd(x, 0, 0, N, i, nxt...);
	}
	templatic element upd(element x, ll n, ll nl, ll nr, ll i, T... nxt) {
		if (nl + 1 == nr) return t[n].val.update(x, nxt...) , x;
		int d = i >= mid;
		(i < mid ? nr : nl) = mid;
		element lx = upd(x, go(n, d), nl, nr, i, nxt...), rx;
		if (t[n][!d]) rx = t[t[n][!d]].val.get(nxt...);
		return t[n].val.update(lx * rx, nxt...) , lx * rx;
	}
	templatic element query(ll l, ll r, T... nxt) {
		if (t.size() == 1) {
			element res;
			for (auto& x : cache)
				if (l <= x.first && x.first < r)
					res = res * x.second;
			return res;
		}
		return que(0, 0, N, l, r, nxt...);
	}
	templatic element que(ll n, ll nl, ll nr, ll l, ll r, T... nxt) {
		if (nr <= l || r <= nl) return element();
		if (l <= nl && nr <= r) return t[n].val.query(nxt...);
		return (t[n][0] ? que(t[n][0], nl, mid, l, r, nxt...) : element()) *
			(t[n][1] ? que(t[n][1], mid, nr, l, r, nxt...) : element());
	}
};
template<typename element, ll N>
struct segtree<0, element, N> {
	element val;
	segtree() {}
	element get() { return val; }
	element query() { return val; }
	element update(element x) {
		return val = x;
	}
};