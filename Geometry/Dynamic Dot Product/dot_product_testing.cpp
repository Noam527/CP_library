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
#include <cstring>
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

typedef long double ldb;
const ldb EPS = 1e-10;
const ldb PI = atan2l(0, -1);
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> int epssgn(T x) { return (x > EPS) - (x < -EPS); }

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")";
	}
};

struct dynamic_hull {
	typedef Point<ll> pll;
	struct node {
		int i, j, l, size;
		node() : i(-1), j(-1), l(-1), size(0) {}
		node(int x) : i(x), j(x), l(x), size(1) {}
	};
	int n;
	vector<pll> p;
	vector<node> t;
	dynamic_hull(vector<pll>& a) : p(a) { // needs sorted (x,y)!
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
};

// testing
const int M = 1000000, C = 1000000000;
int rnd() {
	return ((rand() % (1 << 15)) << 15) | (rand() % (1 << 15));
}
int rnd_range(int lo, int hi) {
	return rnd() % (hi - lo + 1) + lo;
}
vector<ll> bruteforce(vector<Point<ll>> a, vector<array<int, 3>> Q) {
	int n = a.size();
	vector<int> state(n, 1);
	vector<ll> ans;
	for (auto& i : Q) {
		if (i[0] == 0) {
			// flip
			int j = i[1];
			state[j] ^= 1;
		}
		else {
			// query
			Point<ll> dot(i[1], i[2]);
			ll mx = -inf;
			for (int i = 0; i < n; i++)
				if (state[i])
					mx = max(mx, dot.dot(a[i]));
			ans.push_back(mx);
		}
	}
	return ans;
}
vector<ll> smartforce(vector<Point<ll>> a, vector<array<int, 3>> Q) {
	int n = a.size();
	vector<int> state(n, 1);
	int totalcnt = n;
	vector<ll> ans;
	dynamic_hull hull(a);
	for (auto& i : Q) {
		if (i[0] == 0) {
			// flip
			int j = i[1];
			totalcnt -= state[j];
			state[j] ^= 1;
			totalcnt += state[j];
			hull.update(j, state[j]);
		}
		else {
			// query
			if (totalcnt == 0) {
				ans.push_back(-inf);
				continue;
			}
			int j = hull.maximize(i[1], i[2]);
			ans.push_back(i[1] * a[j].x + i[2] * a[j].y);
		}
	}
	return ans;
}
void generate(int n, int q, vector<Point<ll>>& a, vector<array<int, 3>>& Q) {
	// no duplicates + sorted
	set<Point<ll>> exist;
	a.resize(n);
	for (auto& i : a) {
		do {
			i = Point<ll>(rnd_range(-M, M), rnd_range(-M, M));
		} while (exist.count(i));
		exist.insert(i);
	}
	sort(a.begin(), a.end());
	Q.resize(q);
	for (auto& i : Q) {
		i[0] = rnd_range(0, 1);
		if (i[0] == 0) {
			// flip
			i[1] = rnd_range(0, n - 1);
		}
		else {
			// query
			i[1] = rnd_range(-C, C);
			i[2] = rnd_range(0, C); // just not negative y, since we only test upper hull
		}
	}
}
bool test_once(int n, int q) {
	vector<Point<ll>> a;
	vector<array<int, 3>> Q;
	generate(n, q, a, Q);
	auto bruteans = bruteforce(a, Q);
	auto smartans = smartforce(a, Q);
	bool verdict = true;
	if (bruteans.size() != smartans.size())
		verdict = false;
	for (int i = 0; verdict && i < bruteans.size(); i++) {
		if (bruteans[i] != smartans[i])
			verdict = false;
	}
	if (!verdict && OO) {
		cout << "failed on the following test:\n";
		PRINT_VARS(a);
		for (auto& i : Q) {
			cout << i[0] << " " << i[1] << " " << i[2] << '\n';
		}
		PRINT_VARS(bruteans);
		PRINT_VARS(smartans);
	}
	return verdict;
}
bool multitest(int n, int q, int test_count) {
	srand(734637); // TODO: change to time(NULL)
	for (int i = 0; i < test_count; i++) {
		if (i % 100 == 0 || i % ((test_count + 99) / 100) == 0) {
			cout << "Passed " << i << " tests\n";
		}
		if (!test_once(n, q)) {
			return false;
		}
	}
	return true;
}

void solve() {
	int n, q, test_count;
	cin >> n >> q >> test_count;
	if (!multitest(n, q, test_count)) {
		cout << "Failed :(\n";
	}
	else {
		cout << "Passed :)\n";
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cout.precision(10);
	int tests = 1;
	//cin >> tests;
	while (tests--) solve();
}