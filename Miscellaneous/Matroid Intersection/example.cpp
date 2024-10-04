#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <time.h>
#include <string>
#include <map>
#include <set>
#include <cmath>
#include <functional>
#include <utility>
#include <sstream>
#include <array>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
constexpr int OO = 1;
const int md = (int)1e9 + 7; // (int)1e9 + 7, 998244353
const ll inf = 2e18;

namespace {
	template <class T>
	std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
		out << "[ ";
		for (int i = 0; i < vec.size(); ++i) {
			out << (i ? ", " : "") << vec[i];
		}
		out << " ]";
		return out;
	}

#define PRINT_VARS(...) if constexpr (OO) print_vars(#__VA_ARGS__, __VA_ARGS__)

	template <class T, class... Args>
	void print_vars(std::vector<std::string> labels, T arg, Args... args) {
		std::string label = labels[labels.size() - sizeof...(args) - 1];
		std::cout << label << " = " << arg;
		if constexpr (sizeof...(args) > 0) {
			std::cout << ",";
			print_vars(labels, args...);
		}
		else {
			std::cout << std::endl;
		}
	}

	template <class... Args>
	void print_vars(std::string labels, Args... args) {
		std::stringstream input_labels(labels);
		std::string label;
		std::vector<std::string> vectorized_lables;
		while (std::getline(input_labels, label, ',')) {
			vectorized_lables.push_back(label);
		}
		print_vars(vectorized_lables, args...);
	}
}

struct dsu {
	int n;
	vector<int> p, r;
	dsu() {}
	dsu(int n) : n(n), p(n), r(n) {
		for (int i = 0; i < n; i++) p[i] = i;
	}
	void clear() {
		for (int i = 0; i < n; i++)
			r[i] = 0, p[i] = i;
	}
	int find(int x) {
		return x == p[x] ? x : p[x] = find(p[x]);
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	void unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (r[x] > r[y]) swap(x, y);
		p[x] = y;
		if (r[x] == r[y]) r[y]++;
	}
};

struct graphic_matroid {
	int n;
	vector<int> s;
	vector<pair<int, int>> e;
	dsu D, tmp;
	graphic_matroid(const vector<pair<int, int>>& e) : e(e), n(e.size()), s(n) {
		int v = -1;
		for (auto& i : e) v = max(max(v, i.first), i.second);
		v++;
		D = dsu(v), tmp = dsu(v);
	}
	void set(const vector<int>& newset) { // guaranteed to be independent
		s = newset;
		D.clear();
		for (int i = 0; i < n; i++)
			if (s[i]) D.unite(e[i].first, e[i].second);
	}
	bool can_add(int i) { // i not in s
		return !D.same(e[i].first, e[i].second);
	}
	void add(int i) { // i not in s and addition will be independent
		s[i] = 1;
		D.unite(e[i].first, e[i].second);
	}
	vector<int> neighbors(int v) { // v in s
		vector<int> res;
		tmp.clear();
		for (int i = 0; i < n; i++)
			if (i != v && s[i]) tmp.unite(e[i].first, e[i].second);
		for (int i = 0; i < n; i++)
			if (!s[i] && !tmp.same(e[i].first, e[i].second))
				res.push_back(i);
		return res;
	}
};

struct colorful_matroid {
	int n;
	vector<int> s;
	vector<int> color, freq;
	colorful_matroid(const vector<int>& c) : color(c) {
		n = color.size();
		s.resize(n);
		// compress
		vector<int> allcol = color;
		sort(allcol.begin(), allcol.end());
		allcol.resize(unique(allcol.begin(), allcol.end()) - allcol.begin());
		for (auto& i : color)
			i = lower_bound(allcol.begin(), allcol.end(), i) - allcol.begin();
		freq.resize(allcol.size()); 
	}
	void set(const vector<int>& newset) { // guaranteed to be independent
		s = newset;
		freq.assign(freq.size(), 0);
		for (int i = 0; i < n; i++)
			if (s[i]) freq[color[i]]++;
	}
	bool can_add(int i) {
		if (color[i] == 0) return false;
		return freq[color[i]] < 2;
	}
	void add(int i) {
		s[i] = 1;
		freq[color[i]]++;
	}
	vector<int> neighbors(int v) { // v not in s
		vector<int> res;
		if (color[v] == 0) return res;
		for (int i = 0; i < n; i++)
			if (s[i] && (freq[color[v]] < 2 || color[i] == color[v]))
				res.push_back(i);
		return res;
	}
};

vector<int> matroid_intersection(graphic_matroid& m1, colorful_matroid& m2) {
	int n = m1.n, i;
	vector<int> s(n), vis, prev, right, adj;
	while (1) { // keep augmenting
		right.assign(n, 0);
		int total = 0;
		for (i = 0; i < n; i++) {
			if (s[i]) continue;
			if (m1.can_add(i)) right[i] |= 1;
			if (m2.can_add(i)) right[i] |= 2;
			if (right[i] == 3) break;
			total |= right[i];
		}
		if (i < n) { // easy take
			s[i] = 1;
			m1.set(s), m2.set(s);
			continue;
		}
		if (total != 3) break; // easy maximum
		vis.assign(n, 0), prev.assign(n, -1);
		queue<int> q;
		for (int i = 0; i < n; i++)
			if (right[i] & 1) q.push(i), vis[i] = 1;
		int found = -1;
		while (q.size() && found == -1) {
			int v = q.front(); q.pop();
			if (s[v]) adj = m1.neighbors(v);
			else adj = m2.neighbors(v);
			for (auto& i : adj) {
				if (vis[i]) continue;
				vis[i] = 1, prev[i] = v;
				if (right[i] & 2) {
					found = i;
					break;
				}
				q.push(i);
			}
		}
		if (found == -1) break; // no augmenting path
		while (found != -1)
			s[found] ^= 1, found = prev[found];
		m1.set(s), m2.set(s); // apply new
	}
	return s;
}

int n, m;
int fr[20][20];

int encode(int i, int j) {
	return m * i + j;
}
void decode(int cell, int& i, int& j) {
	i = cell / m, j = cell % m;
}

const int dx[4] = { 0, 1, 0, -1 }, dy[4] = { 1, 0, -1, 0 };
bool ok(int i, int j) {
	return 0 <= i && i < n && 0 <= j && j < m && fr[i][j];
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++)
			fr[i][j] = (s[j] == 'O');
	}
	vector<pair<int, int>> e;
	vector<int> col;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if ((i + j) % 2 == 1) continue;
		if (!ok(i, j)) continue;
		int v = encode(i, j);
		for (int k = 0; k < 4; k++) {
			if (ok(i + dx[k], j + dy[k])) {
				e.emplace_back(v, encode(i + dx[k], j + dy[k]));
				col.push_back(v);
			}
		}
	}
	graphic_matroid m1(e);
	colorful_matroid m2(col);
	vector<int> s = matroid_intersection(m1, m2);
	// check if all degrees are 2
	bool found = false;
	int nxtind = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if ((i + j) % 2 == 1) continue;
		if (!ok(i, j)) continue;
		int v = encode(i, j);
		int cnt = 0;
		for (int k = 0; k < 4; k++) {
			if (ok(i + dx[k], j + dy[k])) {
				cnt += s[nxtind++];
			}
		}
		if (i == 0 && j == 0) continue;
		if (cnt < 2) found = true;
	}
	if (found) {
		// no answer
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	// add edges to make it a spanning tree
	for (int i = 0; i < s.size(); i++)
		if (!s[i] && m1.can_add(i)) {
			m1.add(i);
			s[i] = 1;
		}
	// construct answer
	char ans[40][40];
	for (int i = 0; i < 2 * n; i++) for (int j = 0; j < 2 * m; j++)
		ans[i][j] = ' ';
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
		ans[2 * i][2 * j] = (fr[i][j] ? 'O' : 'X');
	for (int i = 0; i < s.size(); i++) {
		if (!s[i]) continue;
		int u = e[i].first, v = e[i].second;
		int uc[2], vc[2];
		decode(u, uc[0], uc[1]);
		decode(v, vc[0], vc[1]);
		ans[uc[0] + vc[0]][uc[1] + vc[1]] = 'P';
	}
	for (int i = 0; i < 2 * n - 1; i++) {
		for (int j = 0; j < 2 * m - 1; j++) cout << ans[i][j];
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cout.precision(10);
	int tests = 1;
	cin >> tests;
	while (tests--) solve();
}