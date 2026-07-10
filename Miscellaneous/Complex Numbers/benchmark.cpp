#include <bits/stdc++.h>
using ll = long long;
using ldb = long double;
constexpr int OO = 1;
const int intinf = (int)1e9 + 7;
const ll inf = 2e18;
using namespace std;

#ifdef DEBUG
#include "debug.h"
#else
#define PRINT_VARS(...) do { (void)sizeof(__VA_ARGS__); } while (0)
#define PRINT_ARR(...) do { (void)sizeof(__VA_ARGS__); } while (0)
#define PRINT_ARR_CNT(...) do { (void)sizeof(__VA_ARGS__); } while (0)
#endif

#ifdef COLOR
#include "custom_cout.h"
#endif

/* --------------------- BEGIN REAL SOLUTION --------------------- */

template<typename T>
struct Comp {
	T x, y;
	Comp(T real = 0, T imag = 0) : x(real), y(imag) {}
	T real() const { return x; }
	T imag() const { return y; }
	bool is_zero() const {
		return x == 0 && y == 0;
	}
	Comp operator -() const {
		return Comp(-x, -y);
	}
	Comp conj() const {
		return Comp(x, -y);
	}
	void operator += (const Comp &other) {
		x += other.x, y += other.y;
	}
	Comp operator + (const Comp &other) const {
		return Comp(x + other.x, y + other.y);
	}
	void operator -= (const Comp &other) {
		x -= other.x, y -= other.y;
	}
	Comp operator - (const Comp &other) const {
		return Comp(x - other.x, y - other.y);
	}
	void operator *= (const Comp &other) {
		T tmp = x * other.x - y * other.y;
		y = x * other.y + y * other.x;
		x = tmp;
	}
	Comp operator * (const Comp &other) const {
		return Comp(x + other.x - y * other.y, x * other.y + y * other.x);
	}
	void operator /= (const Comp &other) {
		Comp other_conj = other.conj();
		*this *= other_conj;
		T div = other.x * other.x + other.y * other.y;
		x /= div, y /= div;
	}
	Comp operator / (const Comp &other) const {
		Comp tmp = *this * other.conj();
		T div = other.x * other.x + other.y * other.y;
		tmp.x /= div, tmp.y /= div;
		return tmp;
	}
	friend ostream& operator<<(ostream& os, Comp n) {
		return os << '(' << n.x << ", " << n.y << ')';
	}
	friend istream& operator>>(istream &is, Comp &n) {
		T first, second;
		is >> first >> second;
		n = Comp(first, second);
		return is;
	}
};
using comp = Comp<long double>;

const int ITER = 2000;

comp mine() {
	comp p(0.5, 0.8);
	comp cur(1);
	for (int i = 0; i < ITER; i++) {
		cur /= p;
		if (cur.x > 10) cur.x = 1;
		if (cur.x < -10) cur.x = -1;
		if (cur.y > 10) cur.y = 1;
		if (cur.y < -10) cur.y = -1;
	}
	return cur;
}
complex<long double> theirs() {
	complex<long double> p(0.5, 0.8);
	complex<long double> cur(1);
	for (int i = 0; i < ITER; i++) {
		cur /= p;
		if (cur.real() > 10) cur.real(1);
		if (cur.real() < -10) cur.real(-1);
		if (cur.imag() > 10) cur.imag(1);
		if (cur.imag() < -10) cur.imag(-1);
	}
	return cur;
}

inline int64_t getime() {
	return chrono::steady_clock::now().time_since_epoch().count();
}

void solve() {
	auto x = getime();
	comp out1 = mine();
	cout << out1 << endl;
	auto y = getime();
	cout << (y - x) / 1e9 << endl;

	x = getime();
	complex<long double> out2 = theirs();
	cout << out2 << endl;
	y = getime();
	cout << (y - x) / 1e9 << endl;
}

/* --------------------- BEGIN MAIN SETUP --------------------- */

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	// multitest?
	int tests = 1;
	// cin >> tests;
	// for floating point problems
	cout.precision(10), cout << fixed;
#ifdef COLOR
	colored_cout.init(cout);
	for (int testnum = 0; testnum < tests; testnum++) {
		hook_before_test(testnum);
		solve();
		hook_after_test(testnum);
	}
#else
	while (tests--) solve();
#endif
}