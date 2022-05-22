#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
typedef long long ll;
typedef long double ldb;
const int md = 998244353;
const int OO = 1;
using namespace std;

/*
To be combined with a segment tree.
This holds an element per vertex in the tree.
Element and tag restrictions must satisfy the ones of segment tree.
*/
template<typename element, typename tag>
struct hld {
	int n;
	vector<vector<int>> g;
	int sec;
	vector<int> in, out, root, dep;
	hld() {}
	hld(const vector<vector<int>> &G) {
		g = G;
		n = g.size();
		in.resize(n), out.resize(n), root.resize(n, -1), dep.resize(n);
		dfs0(0, 0, 0);
	}
	int dfs0(int v, int prev, int d) {
		dep[v] = d;
		int sz = 1, mx = 0;
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i] != prev) {
				int s = dfs0(g[v][i], v, d + 1);
				if (mx < s) {
					mx = s;
					swap(g[v][0], g[v][i]);
				}
			}
		}
	}
	void dfs1(int v, int prev) {
		in[v] = sec++;
		for (const auto &i : g[v])
			if (i != prev)
				dfs1(i, v);
		out[v] = sec;
	}
};

void solve() {

}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tst = 1;
	//cin >> tst;
	while (tst--) solve();
}
