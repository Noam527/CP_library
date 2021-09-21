#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldb;
const int md = 1e9 + 7;
const ll inf = 3e18;
const int OO = 1;
using namespace std;

int rnd() {
	return ((rand() % (1 << 15)) << 15) + (rand() % (1 << 15));
}

int dist(const pair<int, int> &aa, const pair<int, int> &bb) {
	return abs(aa.first - bb.first) + abs(aa.second - bb.second);
}

ll calculate(const vector<pair<int, int>> &aa) {
	ll res = 0;
	for (int i = 0; i + 1 < aa.size(); i++)
		res += dist(aa[i], aa[i + 1]);
	return res;
}

const int N = 100000, K = 300, L = 10;

struct query {
	int l, r, i;
	query(int _l = 0, int _r = 0, int _i = 0) {
		l = _l;
		r = _r;
		i = _i;
	}
};

struct moptimizer {
	int dist(const query &a, const query &b) {
		return abs(a.l - b.l) + abs(a.r - b.r);
	}

	vector<int> p, r;
	vector<vector<int>> g;
	vector<int> order;
	int find(int x) {
		return x == p[x] ? x : p[x] = find(p[x]);
	}
	bool unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return false;
		if (r[x] < r[y]) p[x] = y;
		else {
			p[y] = x;
			if (r[x] == r[y]) r[x]++;
		}
		return true;
	}
	void dfs(int v, int prev) {
		order.push_back(v);
		for (const auto &i : g[v])
			if (i != prev)
				dfs(i, v);
	}

	// https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/ManhattanMST.h
	void manhattanMST(vector<query> ps) {
		vector<int> id(ps.size());
		for (int i = 0; i < id.size(); i++)
			id[i] = i;
		vector<pair<int, int>> edges;
		for (int k = 0; k < 4; k++) {
			sort(id.begin(), id.end(), [&](int i, int j) {
				return ps[i].l - ps[j].l < ps[j].r - ps[i].r; });
			map<int, int> sweep;
			for (int i : id) {
				for (auto it = sweep.lower_bound(-ps[i].r);
					it != sweep.end(); sweep.erase(it++)) {
					int j = it->second;
					if (ps[i].r - ps[j].r > ps[i].l - ps[j].l) break;
					edges.emplace_back(i, j);
				}
				sweep[-ps[i].r] = i;
			}
			for (query& p : ps) if (k & 1) p.l = -p.l; else swap(p.l, p.r);
		}
		sort(edges.begin(), edges.end(), [&](pair<int, int> &aa, pair<int, int> &bb) {
			return dist(ps[aa.first], ps[aa.second]) < dist(ps[bb.first], ps[bb.second]);
		});
		for (auto &i : edges) {
			if (unite(i.first, i.second)) {
				g[i.first].push_back(i.second);
				g[i.second].push_back(i.first);
			}
		}
	}
	void optimize(vector<query> &Q) {
		g.clear(), order.clear();
		int n = Q.size();
		p.resize(n), r.resize(n), g.resize(n);
		for (int i = 0; i < n; i++) {
			p[i] = i;
			r[i] = 0;
		}
		manhattanMST(Q);
		dfs(0, 0);
		vector<query> result(n);
		for (int i = 0; i < n; i++)
			result[i] = Q[order[i]];
		Q = result;
	}
};

vector<pair<int, int>> gen(int n, int q) {
	set<pair<int, int>> S;
	while (S.size() < q) {
		int x = rnd() % n, y = rnd() % n;
		S.insert(make_pair(x, y));
	}
	vector<pair<int, int>> res;
	res.reserve(q);
	for (auto &i : S)
		res.push_back(i);
	return res;
}

void solve() {
	srand(time(NULL));
	vector<pair<int, int>> a = gen(N, N);
	vector<query> Q(N);
	for (int i = 0; i < N; i++)
		Q[i] = query(a[i].first, a[i].second, i);
	moptimizer M;
	M.optimize(Q);
	for (int i = 0; i < N; i++)
		a[i].first = Q[i].l, a[i].second = Q[i].r;
	cout << "result: " << calculate(a) << '\n';
	sort(a.begin(), a.end(), [&](const pair<int, int> &aa, const pair<int, int> &bb) {
		if (aa.first / K != bb.first / K) return aa.first < bb.first;
		if ((aa.first / K) & 1)
			return aa.second < bb.second;
		return aa.second > bb.second;
	});
	cout << "mo says: " << calculate(a) << '\n';
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tst = 1;
	//cin >> tst;
	while (tst--) solve();
}
