struct dynamic_dot_product {
	typedef Point<ll> pll;
	struct node {
		int i, j, l, size;
		node() : i(-1), j(-1), l(-1), size(0) {}
		node(int x) : i(x), j(x), l(x), size(1) {}
	};
	int n;
	vector<pll> p;
	vector<node> t;
	dynamic_dot_product(vector<pll>& a) : p(a) { // needs sorted (x,y)!
		n = p.size();
		while (n != (n & -n)) n += (n & -n);
		t.resize(2 * n);
		for (int i = 0; i < a.size(); i++)
			t[i + n - 1] = node(i);
		for (int i = n - 2; i >= 0; i--) fix(i);
	}
#define lp(v) p[t[v].i]
#define rp(v) p[t[v].j]
#define nsz(v) t[v].size
	void fix(int v) {
		if (v >= n) return;
		int a = 2 * v + 1, b = a + 1;
		if (!nsz(a) || !nsz(b)) {
			if (!nsz(a)) t[v] = t[b];
			else t[v] = t[a];
			return;
		}
		ll x = p[t[b].l].x, lhs, rhs;
		t[v].l = t[a].l, t[v].size = 2;
		while (nsz(a) >= 2 || nsz(b) >= 2) {
			if (nsz(a) >= 2 && lp(a).cross(rp(a), lp(b)) >= 0)
				a = 2 * a + 1;
			else if (nsz(b) >= 2 && rp(a).cross(lp(b), rp(b)) >= 0)
				b = 2 * b + 2;
			else if (nsz(a) == 1) b = 2 * b + 1;
			else if (nsz(b) == 1) a = 2 * a + 2;
			else { // a could be vertical but not b (cross < 0)
				pll ad = rp(a) - lp(a), bd = rp(b) - lp(b);
				lhs = bd.x * (ad.x * lp(a).y + ad.y * (x - lp(a).x));
				rhs = ad.x * (bd.x * lp(b).y + bd.y * (x - lp(b).x));
				if (ad.x == 0 || lhs > rhs) // left win
					a = 2 * a + 2;
				else b = 2 * b + 1;
			}
			if (nsz(a) == 0) a = ((a - 1) ^ 1) + 1;
			if (nsz(b) == 0) b = ((b - 1) ^ 1) + 1;
		}
		t[v].i = t[a].i, t[v].j = t[b].j;
	}
	void update(int i, bool state) {
		i += n - 1;
		if (t[i].size == state) return; // correct state
		t[i] = state ? node(i - n + 1) : node();
		while (i) i = (i - 1) / 2, fix(i);
	}
	int maximize(ll a, ll b) { // point maximizing ax + by
		if (a < 0 && b == 0) return t[0].l;
		int v = 0, at = -1;
		ll mx = -inf, lopt, ropt;
		pll dir(a, b);
		while (t[v].size >= 2) {
			lopt = dir.dot(lp(v)), ropt = dir.dot(rp(v));
			if (lopt > ropt) {
				if (mx < lopt) mx = lopt, at = t[v].i;
				v = 2 * v + 1;
			}
			else {
				if (mx < ropt) mx = ropt, at = t[v].j;
				v = 2 * v + 2;
			}
			if (nsz(v) == 0) v = ((v - 1) ^ 1) + 1;
		}
		if (t[v].size == 1 && mx < dir.dot(lp(v)))
			at = t[v].i;
		return at;
	}
	void hull(vector<int> &res) {
		res.clear();
		int l = maximize(-1, 0), r = maximize(1, 0);
		if (l == -1) return;
		if (l == r) res.push_back(l);
		else hull(l, r, res), res.push_back(r);
	}
	void hull(int i, int j, vector<int>& res) {
		int k = maximize(p[i].y - p[j].y, p[j].x - p[i].x);
		if (k == i || k == j) res.push_back(i);
		else hull(i, k, res), hull(k, j, res);
	}
};