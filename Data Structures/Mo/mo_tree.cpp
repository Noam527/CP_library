// first add queries, then call solve
// for values on edges, keep lca = -1 and set node value as value of edge to parent
struct mo_tree {
	static const int K; // IMP: set about 2N / sqrt(Q)
	struct query {
		int l, r, p, ind;
		int ans; // IMP: field to hold query answer (change type?)
		query() {}
		query(int l, int r, int p, int ind) : l(l), r(r), p(p), ind(ind) {}
		bool operator < (const query& other) const {
			if (l / K != other.l / K) return l < other.l;
			if ((l / K) % 2 == 0) return r < other.r;
			return r > other.r;
		}
	};
	int n, tim;
	vector<int> ord, state;
	vector<array<int, 2>> ra;
	// IMP: inner DS fields
	mo_tree(vector<vector<int>> &g, vector<int> val) { // IMP: assuming values are int, change if needed
		n = g.size(), tim = 0;
		ord.resize(2 * n), ra.resize(n), state.resize(n);
		dfs(g, 0, 0);
		// IMP: set inner DS fields, using the provided `val`
	}
	void dfs(vector<vector<int>> &g, int v, int p) {
		ord[tim] = v, ra[v][0] = tim, tim++;
		for (auto &i : g[v])
			if (i != p) dfs(g, i, v);
		ord[tim] = v, ra[v][1] = tim, tim++;
	}
	void add(int v); // IMP: function to add node v to the DS
	void remove(int v); // IMP: function to remove node v from it
	int answer_query(); // IMP: query answer on the current state
	void set_state(int v, int b) {
		if (state[v] == b) return;
		b ? add(v) : remove(v);
		state[v] = b;
	}
	int exp_state(int l, int r, int v) { // expected state
		return ((ra[v][0] < l) + (ra[v][1] < l) + (ra[v][0] <= r) + (ra[v][1] <= r)) & 1;
	}
	vector<query> Q;
	void add_query(int u, int v, int lca = -1) {
		if (ra[u][0] > ra[v][0]) swap(u, v);
		if (ra[v][1] <= ra[u][1])
			Q.emplace_back(ra[u][0] + (lca == -1), ra[v][0], -1, Q.size());
		else
			Q.emplace_back(ra[u][1], ra[v][0], lca, Q.size());
	}
	vector<int> solve() { // IMP: change type of answer if needed
		sort(Q.begin(), Q.end());
		vector<int> ans(Q.size());
		int l = 0, r = -1, v;
		for (auto& q : Q) {
			while (1) {
				if (l > q.l) v = ord[--l];
				else if (r < q.r) v = ord[++r];
				else if (r > q.r) v = ord[r--];
				else if (l < q.l) v = ord[l++];
				else break;
				set_state(v, exp_state(q.l, q.r, v));
			}
			if (q.p != -1) set_state(q.p, 1);
			ans[q.ind] = answer_query();
			if (q.p != -1) set_state(q.p, 0);
		}
		return ans;
	}
};