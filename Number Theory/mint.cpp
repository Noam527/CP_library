// Assumes prime modulo at most 2^30.
template<int MOD>
struct Mint {
	int x;
	Mint(int y = 0) {
		if (0 <= y && y < MOD) x = y;
		else x = (y % MOD + MOD) % MOD;
	}
	Mint operator + (Mint a) {
		int res = x + a.x;
		if (res >= MOD) res -= MOD;
		return Mint(res);
	}
	Mint operator - (Mint a) {
		int res = x - a.x + MOD;
		if (res >= MOD) res -= MOD;
		return Mint(res);
	}
	Mint operator * (Mint a) { return Mint((ll)x * a.x % MOD); }
	Mint operator ^ (ll e) {
		Mint b(x), res(1);
		while (e) {
			if (e & 1) res = res * b;
			e /= 2, b = b * b;
		}
		return res;
	}
	Mint inv() { return *this ^ (MOD - 2); }
	Mint operator / (Mint a) { return *this * a.inv(); }
};
// factorial + binomial component, use FLIM above your maximum! it is exclusive. don't forget to call prepare
const int FLIM = 500005, MOD = (int)1e9 + 7;
using Min = Mint<MOD>;
Min fac[FLIM], ifac[FLIM];
void prepare() {
	fac[0] = ifac[0] = Min(1);
	for (int i = 1; i < FLIM; i++)
		fac[i] = fac[i - 1] * Min(i);
	ifac[FLIM - 1] = fac[FLIM - 1].inv();
	for (int i = FLIM - 2; i > 0; i--)
		ifac[i] = ifac[i + 1] * Min(i + 1);
}
Min choose(int n, int k) {
	if (n < k) return Min(0);
	return fac[n] * ifac[k] * ifac[n - k];
}