mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/*
Recommended primes (for no reason, just use one):
  1000000007, 1000000009, 1000000021, 1000000033, 1000000087
*/
template<int MOD = 1000000007, int N = 2>
struct rolling_hash {
	static_assert(MOD >= 1000 && MOD < (1 << 30), "Must have 1000 <= MOD < 2**30 in rolling hash");
	static array<vector<int>, N> pw;
	static array<int, N> base;
	static bool initialized;
	array<vector<int>, N> h;
	rolling_hash() {}
	rolling_hash(const string &s) {
		int n = (int)s.size();
		if (!initialized) {
			set<int> bases;
			while ((int)bases.size() < N) {
				int r = rng() % MOD;
				if (bases.count(r)) continue;
				base[bases.size()] = r;
				bases.insert(r);
			}
			initialized = true;
		}
		for (int it = 0; it < N; it++) {
			if ((int)pw[it].size() < n) {
				int m = (int)pw[it].size();
				pw[it].resize(n);
				pw[it][0] = 1;
				for (int i = max(m, 1); i < n; i++) {
					pw[it][i] = (ll)pw[it][i - 1] * base[it] % MOD;
				}
			}
		}
		for (int it = 0; it < N; it++) {
			h[it].resize(n);
			h[it][0] = s[0];
			for (int i = 1; i < n; i++) {
				h[it][i] = ((ll)h[it][i - 1] * base[it] + s[i]) % MOD;
			}
		}
	}
	int size() const {
		return (int)h[0].size();
	}
	int hash(int i, int l, int r) const {
		if (l == 0) return h[i][r];
		int res = (h[i][r] - (ll)h[i][l - 1] * pw[i][r - l + 1]) % MOD;
		if (res < 0) res += MOD;
		return res;
	}
};
template<int MOD, int N> array<vector<int>, N> rolling_hash<MOD, N>::pw = {};
template<int MOD, int N> array<int, N> rolling_hash<MOD, N>::base = {};
template<int MOD, int N> bool rolling_hash<MOD, N>::initialized = false;

// H[l1..r1] == H[l2..r2]
template<int MOD, int N>
bool is_equal(const rolling_hash<MOD, N> &H1, int l1, int r1, const rolling_hash<MOD, N> &H2, int l2, int r2) {
	for (int i = 0; i < N; i++) {
		if (H1.hash(i, l1, r1) != H2.hash(i, l2, r2)) return false;
	}
	return true;
}

// comparing string of H1[i..] and H2[j..], returns the length of the longest common prefix
template<int MOD, int N>
int lcp(const rolling_hash<MOD, N> &H1, int i, const rolling_hash<MOD, N> &H2, int j) {
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