#include <bits/stdc++.h>
using ll = long long;
using ldb = long double;
constexpr int OO = 1;
const int intinf = (int)1e9 + 7;
const ll inf = 2e18;
using namespace std;

template<typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (auto& x : v) in >> x;
    return in;
}

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

// Assumes 2 * MOD fits in signed integer
const int md = 998244353;
template<int MOD>
struct Mint {
	static_assert(MOD < (1 << 30), "MOD >= 2**30");
	int x;
	Mint() : x(0) {}
	Mint(ll y) {
		if (0 <= y && y < MOD) x = y;
		else {
			x = y % MOD;
			if (x < 0) x += MOD;
		}
	}
	Mint(int y, bool safe) {
		(void)safe;
		x = y;
	}
	Mint operator - () const {
		if (x == 0) return Mint(0, true);
		return Mint(MOD - x, true);
	}
	Mint operator + (Mint a) const {
		if (x + a.x < MOD)
			return Mint(x + a.x, true);
		return Mint(x + a.x - MOD, true);
	}
	void operator += (Mint a) {
		x += a.x;
		if (x >= MOD) x -= MOD;
	}
	Mint operator - (Mint a) const {
		if (x >= a.x)
			return Mint(x - a.x, true);
		return Mint(x - a.x + MOD, true);
	}
	void operator -= (Mint a) {
		x -= a.x;
		if (x < 0) x += MOD;
	}
	Mint operator * (Mint a) const { return Mint((ll)x * a.x % MOD, true); }
	void operator *= (Mint a) {
		x = (ll)x * a.x % MOD;
	}
	Mint operator ^ (ll e) const {
		Mint b(x), res(1);
		while (e) {
			if (e & 1) res = res * b;
			e /= 2, b = b * b;
		}
		return res;
	}
	void operator ^= (ll e) {
		*this = *this ^ e;
	}
	static void euclid(int x, int y, int &a, int &b) {
		if (y == 0) {
			a = 1, b = 0;
			return;
		}
		euclid(y, x % y, b, a);
		b -= a * (x / y);
	}
	Mint inv() const {
		Mint a, b;
		euclid(MOD, x, a.x, b.x);
		if (b.x < 0) b.x += MOD;
		return b;
	}
	Mint operator / (Mint a) const { return *this * a.inv(); }
	void operator /= (Mint a) {
		*this *= a.inv();
	}
	bool operator == (Mint a) const { return x == a.x; }
	bool operator != (Mint a) const { return x != a.x; }
	friend ostream& operator<<(ostream& os, Mint n) {
		return os << n.x;
	}
	friend istream& operator>>(istream &is, Mint &n) {
		ll x;
		is >> x;
		n = Mint(x);
		return is;
	}
};
using mint = Mint<md>;

namespace {
	// T is the type of the coefficients
	template<typename T>
	struct mint_poly {
		using comp = complex<T>;
		vector<T> p;
		mint_poly() {}
		mint_poly(size_t sz, T values = T(0)) : p(sz, values) {}
		mint_poly(const vector<T> &values) : p(values) {}
		mint_poly(const mint_poly &other) : p(other.p) {}
		mint_poly& operator = (const mint_poly &other) {
			p = other.p;
			return *this;
		}
		// ************** BEGIN UTILITY **************
		// Removes all zero leading coefficients
		void truncate() {
			if (p.size() == 0) return;
			size_t ind = p.size() - 1;
			while (ind > 0 && p[ind] == 0) ind--;
			if (p[ind] != 0) {
				p.resize(ind + 1);
			}
			else {
				p.clear();
			}
		}
		void resize(size_t newsize) {
			p.resize(newsize, T(0));
		}
		size_t size() const {
			return p.size();
		}
		int degree() const {
			return (int)p.size() - 1;
		}
		inline T coeff(int k) const {
			return p[k];
		}
		inline T operator [] (int k) const {
			return p[k];
		}
		void pretty_print() const {
			auto output_val = [](T x) {
				cout << x;
			};
			mint_poly q(p);
			while (q.size() > 0 && q.p.back() == 0) q.p.pop_back();
			if (q.size() == 0) {
				cout << "0" << endl;
				return;
			}
			if (q.size() == 1) {
				output_val(q[0]);
				cout << endl;
				return;
			}
			// print most significant
			if (q.p.back() != T(1)) {
				output_val(q[q.size() - 1]);
				cout << "x";
			}
			else
				cout << "x";
			if (q.size() > 2) {
				cout << "^" << q.size() - 1;
			}
			for (int i = q.size() - 2; i >= 0; i--) {
				if (q[i] == 0) continue;
				cout << " + ";

				if (q[i] != 1 || i == 0) output_val(q[i]);
				if (i > 0) {
					cout << "x";
					if (i > 1) {
						cout << "^" << i;
					}
				}
			}
			cout << endl;
		}
		// *************** END UTILITY ***************

		// ************** BEGIN BASIC OPS **************
		T eval(T x) const {
			T result(0);
			for (int i = (int)p.size() - 1; i >= 0; i--)
				result = result * x + p[i];
			return result;
		}
		inline T operator () (T x) const {
			return eval(x);
		}
		
		void operator += (const mint_poly &other) {
			if (size() < other.size()) p.resize(other.size());
			size_t iter = other.size();
			for (size_t i = 0; i < iter; i++)
				p[i] += other[i];
		}
		mint_poly operator + (const mint_poly &other) const {
			mint_poly result(max(size(), other.size()));
			for (size_t i = 0; i < p.size(); i++) {
				result.p[i] = p[i];
			}
			for (size_t i = 0; i < other.size(); i++) {
				result.p[i] += other[i];
			}
			return result;
		}
		void operator -= (const mint_poly &other) {
			if (size() < other.size()) p.resize(other.size());
			size_t iter = other.size();
			for (size_t i = 0; i < iter; i++)
				p[i] -= other[i];
		}
		mint_poly operator - (const mint_poly &other) const {
			mint_poly result(max(size(), other.size()));
			for (size_t i = 0; i < p.size(); i++) {
				result.p[i] = p[i];
			}
			for (size_t i = 0; i < other.size(); i++) {
				result.p[i] -= other[i];
			}
			return result;
		}
		mint_poly derivative() const {
			if (p.size() <= 1) return mint_poly();
			mint_poly Q(p.size() - 1);
			for (size_t i = 0; i < Q.size(); i++)
				Q[i] = T(i + 1) * p[i + 1];
			return Q;
		}
		// with the free coefficient being 0
		mint_poly integral() const {
			if (p.size() == 0) return mint_poly();
			mint_poly Q(p.size() + 1);
			for (size_t i = 1; i < Q.size(); i++)
				Q[i] = p[i - 1] / T(i);
			return Q;
		}
		// *************** END BASIC OPS ***************

		// ************** BEGIN ADV. OPS **************
		// make sure to call with sizes power of 2
		static void ntt(vector<T> &a) {
			if (a.size() == 0) return;
			const T root = T(62); // primitive root of 998244353
			size_t n = a.size(), L = 31 - __builtin_clz(n);
			static vector<T> rt(2, 1);
			for (static size_t k = 2, s = 2; k < n; k *= 2, s++) {
				rt.resize(n);
				T z[] = { 1, root ^ (md >> s) };
				for (size_t i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1];
			}
			vector<size_t> rev(n);
			for (size_t i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
			for (size_t i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
			for (size_t k = 1; k < n; k *= 2)
				for (size_t i = 0; i < n; i += 2 * k) for (size_t j = 0; j < k; j++) {
					mint z = rt[j + k] * a[i + j + k], &ai = a[i + j];
					a[i + j + k] = ai - z;
					ai += z;
				}
		}

		mint_poly operator * (const mint_poly &other) const {
			if (size() == 0 || other.size() == 0) return mint_poly();
			int s = p.size() + other.size() - 1, B = 32 - __builtin_clz(s),
				n = 1 << B;
			T inv = T(n).inv();
			vector<T> L(p), R(other.p), out(n);
			L.resize(n), R.resize(n);
			ntt(L), ntt(R);
			for (int i = 0; i < n; i++)
				out[-i & (n - 1)] = L[i] * R[i] * inv;
			ntt(out);
			return mint_poly(vector<T>(out.begin(), out.begin() + s));
		}
		void operator *= (const mint_poly &other) {
			if (size() == 0 || other.size() == 0) {
				p.clear();
				return;
			}
			int s = p.size() + other.size() - 1, B = 32 - __builtin_clz(s),
				n = 1 << B;
			T inv = T(n).inv();
			vector<T> L(p), R(other.p), out(n);
			L.resize(n), R.resize(n);
			ntt(L), ntt(R);
			for (int i = 0; i < n; i++)
				out[-i & (n - 1)] = L[i] * R[i] * inv;
			ntt(out);
			p = vector<T>(out.begin(), out.begin() + s);
		}
		// Polynomial inverse, but only the first n coefficients (upto x^{n-1})
		mint_poly inv(size_t n) const {
			if (p.size() == 0 || p[0] == 0) {
				throw std::runtime_error("Cannot inverse a polynomial with 0 as the free coefficient.");
			}
			mint_poly B(1, T(1) / p[0]);
			// now inverse modulo x^1, we want inverse modulo x^n
			for (size_t k = 1; k < n; k *= 2) {
				// newB = B(2 - pB) (mod x^2k)
				// but first truncate p
				mint_poly truncated_p(min(2 * k, size()));
				for (size_t i = 0; i < truncated_p.p.size(); i++)
					truncated_p.p[i] = p[i];
				mint_poly rhs(1, 2);
				rhs -= truncated_p * B;
				B *= rhs;
				B.resize(2 * k);
			}
			B.resize(n);
			return B;
		}
		// returns (D, R) such that A = BD + R, and deg(R) < deg(B)
		static array<mint_poly, 2> divmod(const mint_poly &A, const mint_poly &B) {
			size_t n = A.size(), m = B.size();
			if (n < m) return {mint_poly(), A};
			if (m == 1) {
				mint_poly D(n);
				for (size_t i = 0; i < n; i++) {
					D.p[i] = A.p[i] / B[0];
				}
				return {D, mint_poly()};
			}
			// D is of degree n - m
			// DR = AR * inv(BR) (first n - m + 1 terms)
			mint_poly AR(n - m + 1), BR(n - m + 1);
			for (size_t i = 0; i <= n - m; i++) {
				AR.p[i] = A.p[A.size() - 1 - i];
				if (B.size() - 1 >= i)
					BR.p[i] = B.p[B.size() - 1 - i];
			}
			mint_poly D = AR * BR.inv(n - m + 1);
			D.resize(n - m + 1);
			reverse(D.p.begin(), D.p.end());
			mint_poly tmp = B * D;
			mint_poly R = A - tmp;
			R.truncate();
			return {D, R};
		}
		mint_poly operator / (const mint_poly &other) const {
			return divmod(*this, other)[0];
		}
		void operator /= (const mint_poly &other) {
			mint_poly tmp = divmod(*this, other)[0];
			p = tmp.p;
		}
		mint_poly operator % (const mint_poly &other) const {
			return divmod(*this, other)[1];
		}
		void operator %= (const mint_poly &other) {
			mint_poly tmp = divmod(*this, other)[1];
			p = tmp.p;
		}

		static mint_poly build_tree(vector<mint_poly> &res, int node, typename vector<T>::iterator beg, typename vector<T>::iterator end) {
			if (end - beg == 1) {
				vector<T> tmp = {-*beg, 1};
				return res[node] = mint_poly(tmp); // x - *beg
			}
			auto mid = beg + (end - beg) / 2;
			return res[node] = build_tree(res, 2 * node, beg, mid) * build_tree(res, 2 * node + 1, mid, end);
		}
		vector<T> evaluate_rec(const vector<mint_poly> &tree, int node, int l, int r) {
			if (r - l == 1) {
				if (p.size() == 0) return {T(0)};
				return {p[0]};
			}
			int m = l + (r - l) / 2;
			vector<T> first_half = (*this % tree[2 * node]).evaluate_rec(tree, 2 * node, l, m);
			vector<T> second_half = (*this % tree[2 * node + 1]).evaluate_rec(tree, 2 * node + 1, m, r);
			first_half.insert(first_half.end(), second_half.begin(), second_half.end());
			return first_half;
		}
		vector<T> evaluate(vector<T> x) {
			size_t n = x.size();
			if (p.size() == 0) {
				return vector<T>(n, 0);
			}
			vector<mint_poly> tree(4 * n);
			build_tree(tree, 1, x.begin(), x.end());
			mint_poly newp = *this % tree[1];
			return newp.evaluate_rec(tree, 1, 0, (int)n);
		}
		// *************** END ADV. OPS ***************
	};
	using mpoly = mint_poly<mint>;
};

void solve() {
	int n, m;
	cin >> n >> m;
	vector<mint> a(n);
	cin >> a;
	mpoly P(a);
	vector<mint> x(m);
	cin >> x;

	vector<mint> res = P.evaluate(x);
	for (auto &i : res) cout << i << " ";
	cout << endl;
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