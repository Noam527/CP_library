/*
the struct 'element' must have:
* neutral element (as default constructor)
* operator *, to combine with a right operand and return the result
*/
template<typename element>
struct RMQ {
	static const int B = 32;
	int n, h;
	vector<element> val;
	vector<element> pref, suf;
	vector<vector<element>> t;
	RMQ() {}
	template<typename T>
	RMQ(const vector<T> &a) {
		n = (int)a.size();
		h = n >= B ? 32 - __builtin_clz(n / B) : 0;
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
	element query(int l, int r) const {
		if (l > r) return element();
		if (l / B == r / B) {
			element res = val[l];
			for (int i = l + 1; i <= r; i++) {
				res = res * val[i];
			}
			return res;
		}
		element resl, resr;
		if (l % B != 0) resl = suf[l], l += B - l % B;
		if (r % B != B - 1) resr = pref[r], r -= r % B + 1;
		if (l > r) return resl * resr;
		l /= B, r /= B;
		int layer = 31 - __builtin_clz(r - l + 1);
		return resl * t[layer][l] * t[layer][r - (1 << layer) + 1] * resr;
	}
};