/*
Integer lichao tree.
Template variable:
- type: Use 1 for maximum, or -1 for minimum.
*/
template<int type>
struct LiChao {
	typedef long long ll;
	ll low, high;
	static constexpr ll NEG_INF = numeric_limits<ll>::min();
	struct node {
		ll lx, rx;
		int nl, nr;
		ll sl;
		ll c;
		node() {}
		node(ll lx, ll rx, int nl = -1, int nr = -1, ll sl = 0, ll c = NEG_INF) :
			lx(lx), rx(rx), nl(nl), nr(nr), sl(sl), c(c) {}
		inline ll operator () (ll x) const {
			return sl * x + c;
		}
	};
	vector<node> t;

	// lowerbound and upperbound on x-values of queries.
	LiChao(ll low, ll high) : low(low), high(high) {
		t.push_back(node(low, high));
	}
	void make_children(int i) {
		if (t[i].nl != -1 || t[i].lx == t[i].rx)
			return;
		ll midx = (t[i].lx + t[i].rx) / 2;

		t[i].nl = t.size();
		t.push_back(node(t[i].lx, midx));
		t[i].nr = t.size();
		t.push_back(node(midx + 1, t[i].rx));
	}
	void insert(ll slope, ll constant) {
		insert(0, type * slope, type * constant);
	}
	void insert(int node, ll slope, ll constant) {
		if (node == -1)
			return;
		ll lx = t[node].lx, rx = t[node].rx;
		ll midx = (lx + rx) / 2;
		bool win_l = t[node](lx) < slope * lx + constant;
		bool win_m = t[node](midx) < slope * midx + constant;
		bool win_r = t[node](rx) < slope * rx + constant;
		// is it even better at all
		if (!win_l && !win_r) return;
		// is it actually better everywhere?
		if (win_l && win_r) {
			t[node].sl = slope;
			t[node].c = constant;
			return;
		}
		// if new line mostly wins, swap everything
		if (win_m) {
			swap(t[node].sl, slope);
			swap(t[node].c, constant);
			win_l = !win_l, win_m = !win_m, win_r = !win_r;
		}
		make_children(node);
		insert(win_l ? t[node].nl : t[node].nr, slope, constant);
	}
	ll query(ll x) {
		int node = 0;
		ll result = t[node](x);
		while (1) {
			ll midx = (t[node].lx + t[node].rx) / 2;
			int child = x <= midx ? t[node].nl : t[node].nr;
			if (child == -1)
				break;
			node = child;
			result = max(result, t[node](x));
		}
		// multiply by type
		return type * result;
	}
};