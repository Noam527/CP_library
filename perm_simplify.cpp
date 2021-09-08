#include <bits/stdc++.h>
typedef long long ll;
typedef long double ldb;
const int md = 1e9 + 7;
const ll inf = 3e18;
const int OO = 1;
using namespace std;

int n;
const int DLIM = 20; // dist lim
const int NLIM = 100; // per rank
const int MAXRANK = 50;
const bool symmetric = true;

struct perm {
	vector<int> p;
	ll dist;
	vector<vector<int>> path;
	perm() {
		p.resize(n);
		for (int i = 0; i < n; i++) p[i] = i;
		dist = 0;
	}
	perm(vector<int> q) {
		p = q;
		dist = 1;
		path.push_back(p);
	}
	int operator [](int index) const {
		return p[index];
	}
	int& operator [](int index) {
		return p[index];
	}
	bool operator == (const perm &q) const {
		for (int i = 0; i < n; i++)
			if (p[i] != q[i]) return false;
		return true;
	}
	bool operator < (const perm &q) const {
		for (int i = 0; i < n; i++)
			if (p[i] != q[i])
				return p[i] < q[i];
		return false;
	}
	int rank() {
		int res = 0;
		for (int i = 0; i < n; i++)
			if (p[i] != i) res++;
		return res;
	}
	void resetpath() {
		dist = 1;
		path.clear();
		path.push_back(p);
	}
	void print() const {
		cout << "(" << p[0];
		for (int i = 1; i < n; i++)
			cout << ", " << p[i];
		cout << ")\n";
	}
	void printpath() const {
		cout << "distance: " << dist << '\n';
		for (const auto &p : path) {
			cout << "\t(" << p[0];
			for (int i = 1; i < n; i++)
				cout << ", " << p[i];
			cout << ")\n";
		}
	}
};

perm operator * (const perm &a, const perm &b) {
	perm c;
	for (int i = 0; i < n; i++)
		c[i] = a[b[i]];
	c.dist = a.dist + b.dist;
	c.path = b.path;
	for (const auto &x : a.path)
		c.path.push_back(x);
	return c;
}
perm inv(const perm &a) {
	perm b;
	for (int i = 0; i < n; i++)
		b[a[i]] = i;
	b.dist = a.dist; // assumes reversible operations.
	b.path = a.path;
	vector<int> tmp(n);
	for (auto &p : b.path) {
		for (int i = 0; i < n; i++) {
			tmp[p[i]] = i;
		}
		p = tmp;
	}
	reverse(b.path.begin(), b.path.end());
	return b;
}
perm operator & (const perm &a, const perm &b) {
	return a * b * inv(a) * inv(b);
}
perm cycle(vector<int> ind) {
	vector<int> p(n);
	for (int i = 0; i < n; i++) p[i] = i;
	for (int i = 0; i + 1 < ind.size(); i++)
		swap(p[ind[i]], p[ind[i + 1]]);
	return perm(p);
}

vector<perm> all[MAXRANK];
set<perm> have;
queue<perm> Q;

bool add(perm p) {
	if (p.dist <= DLIM && all[p.rank()].size() < NLIM && !have.count(p) && Q.size() < 100000) {
		Q.push(p);
		return true;
	}
	return false;
}

void solve() {
	n = 36;
	perm id;
	Q.push(id);

	vector<vector<int>> starts = {
		{1,19,22,4},
		{7,20,16,3},
		{13,21,10,2},
		{8,14,15,9}
	};
	for (auto &i : starts) for (auto &j : i) j--;
	for (int off : {0, 1, 2, 6, 7, 8, 12, 13, 14}) {
		for (auto &i : starts)
			for (auto &j : i) j += off;
		perm p;
		for (auto &i : starts)
			p = p * cycle(i);
		p.resetpath();
		Q.push(p);
		for (auto &i : starts)
			for (auto &j : i) j -= off;
	}
	cout << "starting\n";
	int iters = 20;
	int count = 0;
	while (Q.size()) {
		perm p = Q.front();
		Q.pop();
		/*
		if (iters == 0) exit(0);
		p.print();
		p.printpath();
		iters--;
		*/
		int currank = p.rank();
		if (have.count(p) || all[currank].size() == NLIM) {
			continue;
		}

		count++;
		if (count % 100 == 0) {
			cout << "count: " << count << '\n';
		}

		have.insert(p);
		all[currank].push_back(p);
		for (int r = 1; r < MAXRANK; r++) {
			for (const auto &q : all[r]) {
				add(p * q);
				add(q * p);
				if (symmetric)
					add(p & q);
			}
		}
	}
	for (int r = 0; r < MAXRANK; r++) {
		cout << r << ": " << all[r].size() << '\n';
	}
	while (1) {
		int r, a, b;
		cin >> r >> a >> b;
		if (a == -1 || b == -1) {
			cout << "we have " << all[r].size() << " of rank " << r << '\n';
			continue;
		}
		if (a > b || a < 0 || all[r].size() <= b) {
			cout << "invalid indicies:\n";
			continue;
		}
		for (int i = a; i <= b; i++) {
			cout << all[r][i].dist << '\n';
			all[r][i].print();
			all[r][i].printpath();
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int tst = 1;
	//cin >> tst;
	while (tst--) solve();
}
