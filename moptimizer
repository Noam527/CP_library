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

const int N = 10000, K = 100, L = 10;
int dp[1 << L][L], from[1 << L][L];

void reorder(vector<pair<int, int>> &a, int l, int r) {
	int LL = r - l + 1;
	if (LL > L) {
		cout << "too long... " << l << " " << r << '\n';
		return;
	}
	for (int mask = 1; mask < (1 << LL); mask++) {
		for (int j = 0; j < LL; j++) {
			if (mask & (1 << j)) {
				if (mask == (1 << j)) {
					if (l == 0) dp[mask][j] = 0;
					else dp[mask][j] = dist(a[l - 1], a[l + j]);
					break;
				}
				dp[mask][j] = (int)1e9;
				for (int k = 0; k < LL; k++) {
					if (k != j && (mask & (1 << k)) != 0) {
						if (dp[mask][j] > dp[mask ^ (1 << j)][k] + dist(a[l + j], a[l + k])) {
							dp[mask][j] = dp[mask ^ (1 << j)][k] + dist(a[l + j], a[l + k]);
							from[mask][j] = k;
						}
					}
				}
			}
		}
	}
	int left = (1 << LL) - 1;
	vector<int> order;
	int best = (int)1e9, start = -1;
	for (int i = 0; i < LL; i++) {
		int cand = dp[left][i];
		if (r + 1 < a.size())
			cand += dist(a[l + i], a[r + 1]);
		if (best > cand) {
			best = cand;
			start = i;
		}
	}
	while (left) {
		order.push_back(start);
		int nxt = from[left][start];
		left ^= (1 << start);
		start = nxt;
	}
	// order is reversed though
	vector<pair<int, int>> tmp(LL);
	for (int i = 0; i < LL; i++) {
		tmp[LL - 1 - i] = a[l + order[i]];
	}
	for (int i = 0; i < LL; i++) {
		a[l + i] = tmp[i];
	}
}

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
	sort(a.begin(), a.end(), [&](const pair<int, int> &aa, const pair<int, int> &bb) {
		if (aa.first / K != bb.first / K) return aa.first < bb.first;
		if ((aa.first / K) & 1)
			return aa.second < bb.second;
		return aa.second > bb.second;
	});
	cout << "mo says: " << calculate(a) << '\n';
	for (int i = 0; i < a.size(); i += L / 2) {
		int l = i, r = min((int)a.size() - 1, i + L - 1);
		if (l == r) break;
		reorder(a, l, r);
		if (i % 1000 == 0) cout << i << '\n';
	}
	cout << "result: " << calculate(a) << '\n';
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tst = 1;
	//cin >> tst;
	while (tst--) solve();
}
