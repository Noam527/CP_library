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
/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
*/
template<typename element>
struct RMQ {
	static const int B = 16;
	int n, h;
	vector<element> val;
	vector<element> pref, suf;
	vector<vector<element>> t;
	RMQ() {}
	template<typename T>
	RMQ(const vector<T> &a) {
		n = (int)a.size();
		h = 32 - __builtin_clz(n / B);
		val.resize(n);
		pref.resize(n);
		suf.resize(n);
		t.resize(h, vector<element>(n / B));
		for (int i = 0; i < n; i++) {
			val[i] = element(a[i]);
			if (i % B == 0) pref[i] = val[i];
			else pref[i] = pref[i - 1] * val[i];
		}
		for (int i = n / B * B - 1; i >= 0; i--) {
			if (i % B == B - 1) suf[i] = val[i];
			else suf[i] = val[i] * suf[i + 1];
		}
		for (int i = 0; i < n / B; i++) {
			t[0][i] = suf[i * B];
		}
		for (int layer = 1; layer < h; layer++) {
			for (int i = 0; i + (1 << layer) <= n / B; i++) {
				t[layer][i] = t[layer - 1][i] * t[layer - 1][i + (1 << layer) / 2];
			}
		}
	}
	// inclusive [l, r]
	element query(int l, int r) {
		if (l > r) return element();
		if (l / B == r / B) {
			element res = val[l];
			for (int i = l + 1; i <= r; i++) {
				res = res * val[i];
			}
			return res;
		}
		element resl, resr;
		while (l % B != 0) resl = resl * val[l++];
		while (r % B != B - 1) resr = val[r--] * resr;
		if (l > r) return resl * resr;
		l /= B, r /= B;
		int layer = 31 - __builtin_clz(r - l + 1);
		return resl * t[layer][l] * t[layer][r - (1 << layer) + 1] * resr;
	}
};