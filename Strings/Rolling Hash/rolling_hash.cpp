mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<int MOD>
struct one_rolling_hash {
	static_assert(MOD >= 1000 && MOD < (1 << 30), "Must have 1000 <= MOD < 2**30 in rolling hash");
	vector<int> pw, h;
	int base;
	one_rolling_hash() {}
	one_rolling_hash(const string &s) {
		int n = (int)s.size();
		pw.resize(n), h.resize(n);
		base = rng() % MOD;
		pw[0] = 1;
		for (int i = 1; i < n; i++) {
			pw[i] = (ll)pw[i - 1] * base % MOD;
		}
		h[0] = s[0];
		for (int i = 1; i < n; i++) {
			h[i] = ((ll)h[i - 1] * base + s[i]) % MOD;
		}
	}
	int size() const {
		return (int)pw.size();
	}
	int hash(int l, int r) const {
		if (l == 0) return h[r];
		int res = (h[r] - (ll)h[l - 1] * pw[r - l + 1]) % MOD;
		if (res < 0) res += MOD;
		return res;
	}
};

/*
Recommended primes (for no reason, just use one):
  1000000007, 1000000009, 1000000021, 1000000033, 1000000087
*/
template<int MOD, int N>
struct rolling_hash {
	vector<one_rolling_hash
	one_rolling_hash<MOD1> H1;
	one_rolling_hash<MOD2> H2;
	rolling_hash() {}
	rolling_hash(const string &s, int count) : H1(s), H2(s) {}
	int size() const {
		return H1.size();
	}
	int hash1(int l, int r) const {
		return H1.hash(l, r);
	}
	int hash2(int l, int r) const {
		return H2.hash(l, r);
	}
};

// H[l1..r1] == H[l2..r2]
template<int MOD1, int MOD2>
bool is_equal(const rolling_hash<MOD1, MOD2> &H1, int l1, int r1, const rolling_hash<MOD1, MOD2> &H2, int l2, int r2) {
	if (H1.hash1(l1, r1) != H2.hash1(l2, r2)) return false;
	if (H1.hash2(l1, r1) != H2.hash2(l2, r2)) return false;
	return true;
}

// comparing string of H1[i..] and H2[j..], returns the length of the longest common prefix
template<int MOD1, int MOD2>
bool lcp(const rolling_hash<MOD1, MOD2> &H1, int i, const rolling_hash<MOD1, MOD2> &H2, int j) {
	int lo = 0, hi = min(H1.size() - i, H2.size() - j), mid;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		if (is_equal(H1, i, i + mid, H2, j, j + mid)) {
			lo = mid + 1;
		}
		else {
			hi = mid;
		}
	}
	return lo;
}