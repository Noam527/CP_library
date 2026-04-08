/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
*/
template<typename element>
struct RMQ {
	static const int B = 16;
	int n, h;
	vector<element> val;
	vector<element> pref, suf;
	vector<vector<element>> t;
	RMQ() {}
	template<typename T>
	RMQ(const vector<T> &a) {
		n = (int)a.size();
		h = n >= B ? 32 - __builtin_clz(n / B) : 0;
		val.resize(n);
		pref.resize(n);
		suf.resize(n);
		t.resize(h, vector<element>(n / B));
		for (int i = 0; i < n; i++) {
			val[i] = element(a[i]);
			if (i % B == 0) pref[i] = val[i];
			else pref[i] = pref[i - 1] * val[i];
		}
		for (int i = n / B * B - 1; i >= 0; i--) {
			if (i % B == B - 1) suf[i] = val[i];
			else suf[i] = val[i] * suf[i + 1];
		}
		for (int i = 0; i < n / B; i++) {
			t[0][i] = suf[i * B];
		}
		for (int layer = 1; layer < h; layer++) {
			for (int i = 0; i + (1 << layer) <= n / B; i++) {
				t[layer][i] = t[layer - 1][i] * t[layer - 1][i + (1 << layer) / 2];
			}
		}
	}
	// inclusive [l, r]
	element query(int l, int r) const {
		if (l > r) return element();
		if (l / B == r / B) {
			element res = val[l];
			for (int i = l + 1; i <= r; i++) {
				res = res * val[i];
			}
			return res;
		}
		element resl, resr;
		if (l % B != 0) resl = suf[l], l += B - l % B;
		if (r % B != B - 1) resr = pref[r], r -= r % B + 1;
		if (l > r) return resl * resr;
		l /= B, r /= B;
		int layer = 31 - __builtin_clz(r - l + 1);
		return resl * t[layer][l] * t[layer][r - (1 << layer) + 1] * resr;
	}
};

struct elem {
	pair<int, int> x;
	elem() : x({intinf, 0}) {}
	elem(pair<int, int> x) : x(x) {}
	elem operator * (const elem &other) const {
		return elem(min(x, other.x));
	}
};

struct LCA {
	const vector<vector<int>> &g;
	int n;
	vector<pair<int, int>> ord;
	vector<int> tim;
	RMQ<elem> R;
	LCA(const vector<vector<int>> &graph, int root = 0) : g(graph), n((int)graph.size()) {
		ord.reserve(2 * n);
		tim.resize(n);
		dfs(root, root, 0);
		R = RMQ<elem>(ord);
	}
	void dfs(int v, int par, int d) {
		tim[v] = (int)ord.size();
		ord.emplace_back(d, v);
		for (auto &i : g[v]) {
			if (i == par) continue;
			dfs(i, v, d + 1);
			ord.emplace_back(d, v);
		}
	}
	int depthof(int v) const {
		return ord[tim[v]].first;
	}
	int lca(int u, int v) const {
		int l = tim[u], r = tim[v];
		if (l > r) swap(l, r);
		return R.query(l, r).x.second;
	}
	int dist(int u, int v) const {
		int l = lca(u, v);
		return depthof(u) + depthof(v) - 2 * depthof(l);
	}
};