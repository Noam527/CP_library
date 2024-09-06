/*
Integer lichao tree.
For efficiency, there are multiple template variables:
- type: Use 1 for maximum, or -1 for minimum.
- slope_t: type for the slopes.
- const_t: type for the constants.
- eval_t: type for both the queries and the evaluation of lines on given queries.
*/
template<int type, typename slope_t = long long, typename const_t = long long, typename eval_t = long long>
struct LiChao {
	eval_t low, high;
	static constexpr const_t NEG_INF = numeric_limits<const_t>::min();
	struct node {
		eval_t lx, rx;
		int nl, nr;
		slope_t sl;
		const_t c;
		node() {}
		node(eval_t lx, eval_t rx, int nl = -1, int nr = -1, slope_t sl = 0, const_t c = NEG_INF) :
			lx(lx), rx(rx), nl(nl), nr(nr), sl(sl), c(c) {}
		inline eval_t operator () (eval_t x) const {
			return eval_t(sl) * x + eval_t(c);
		}
	};
	vector<node> t;

	// lowerbound and upperbound on x-values of queries.
	LiChao(eval_t low, eval_t high) : low(low), high(high) {
		t.push_back(node(low, high));
	}
	void make_children(int i) {
		if (t[i].nl != -1 || t[i].lx == t[i].rx)
			return;
		eval_t midx = (t[i].lx + t[i].rx) / 2;

		t[i].nl = t.size();
		t.push_back(node(t[i].lx, midx));
		t[i].nr = t.size();
		t.push_back(node(midx + 1, t[i].rx));
	}
	void insert(slope_t slope, const_t constant) {
		insert(0, type * slope, type * constant);
	}
	void insert(int node, slope_t slope, const_t constant) {
		if (node == -1)
			return;
		eval_t lx = t[node].lx, rx = t[node].rx;
		eval_t midx = (lx + rx) / 2;
		bool win_l = t[node](lx) < eval_t(slope) * lx + eval_t(constant);
		bool win_m = t[node](midx) < eval_t(slope) * midx + eval_t(constant);
		bool win_r = t[node](rx) < eval_t(slope) * rx + eval_t(constant);
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
	eval_t query(eval_t x) {
		int node = 0;
		eval_t result = t[node](x);
		while (1) {
			eval_t midx = (t[node].lx + t[node].rx) / 2;
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