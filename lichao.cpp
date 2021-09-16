// use the constant to choose min / max.
// also define L and R as the range of the queries.
struct lichao {
	static const int MIN = 1;
	static const int L = 0, R = (int)1e9;
	static const ll INF = (ll)9e18;

	struct node {
		int l, r;
		int m, c;
		ll optl, optr;
		int nl, nr;
		bool push;
		node() {}
		node(int left, int right, int mm, int cc) {
			l = left;
			r = right;
			m = mm;
			c = cc;
			if (MIN) optl = optr = INF;
			else optl = optr = -INF;
			nl = nr = -1;
			push = false;
		}
		inline ll operator () (ll x) const {
			return m * x + c;
		}
	};
	int C;
	vector<node> t;

	lichao() {
		C = 0;
		if (MIN) t.push_back(node(L, R, 0, INF));
		else t.push_back(node(L, R, 0, -INF));
	}
	void make_children(int i) {
		if (t[i].nl != -1) return;
		ll mid = (t[i].l + t[i].r) / 2;
		int cur = (int)t.size();
		t[i].nl = cur, t[i].nr = cur + 1;

		t.push_back(node(t[i].l, mid, t[i].m, t[i].c));
		t.back().optl = t[i].optl;
		t.back().optr = t[i](mid);

		t.push_back(node(mid + 1, t[i].r, t[i].m, t[i].c));
		t.back().optl = t[i](mid + 1);
		t.back().optr = t[i].optr;
	}
	void lazy_push(int i, int to) {
		t[to].m = t[i].m, t[to].c = t[i].c;
		t[to].optl = t[to](t[to].l), t[to].optr = t[to](t[to].r);
		t[to].push = true;
	}
	void addline(ll m, ll c) {
		addline(0, m, c);
	}
	void addline(int i, ll m, ll c) {
		if (i == -1) return;
		ll mid = (t[i].l + t[i].r) / 2;
		if (MIN) {
			if (m * t[i].l + c <= t[i].optl && m * t[i].r + c <= t[i].optr) {
				t[i].m = m, t[i].c = c;
				t[i].optl = m * t[i].l + c, t[i].optr = m * t[i].r + c;
				t[i].push = true;
				return;
			}
			if (t[i].nl == -1) {
				make_children(i);
				t[i].push = false;
			}
			else if (t[i].push) {
				lazy_push(i, t[i].nl);
				lazy_push(i, t[i].nr);
				t[i].push = false;
			}
			if (m * mid + c < t[i](mid)) {
				t[i].m = m, t[i].c = c;
				addline(t[i].nl, m, c);
				addline(t[i].nr, m, c);
				return;
			}

			if (m > t[i].m)
				addline(t[i].nl, m, c);
			else if (m < t[i].m)
				addline(t[i].nr, m, c);
		}
		else {
			if (m * t[i].l + c >= t[i].optl && m * t[i].r + c >= t[i].optr) {
				t[i].m = m, t[i].c = c;
				t[i].optl = m * t[i].l + c, t[i].optr = m * t[i].r + c;
				t[i].push = true;
				return;
			}
			if (t[i].nl == -1) {
				make_children(i);
				t[i].push = false;
			}
			else if (t[i].push) {
				lazy_push(i, t[i].nl);
				lazy_push(i, t[i].nr);
				t[i].push = false;
			}
			if (m * mid + c > t[i](mid)) {
				t[i].m = m, t[i].c = c;
				addline(t[i].nl, m, c);
				addline(t[i].nr, m, c);
				return;
			}

			if (m < t[i].m)
				addline(t[i].nl, m, c);
			else if (m > t[i].m)
				addline(t[i].nr, m, c);
		}
	}
	ll query(ll x) {
		return query(0, x);
	}
	ll query(int i, ll x) {
		if (t[i].nl == -1) return t[i](x);
		if (t[i].push) {
			lazy_push(i, t[i].nl);
			lazy_push(i, t[i].nr);
			t[i].push = false;
		}
		ll mid = (t[i].l + t[i].r) / 2;
		if (x <= mid) return query(t[i].nl, x);
		return query(t[i].nr, x);
	}
};
