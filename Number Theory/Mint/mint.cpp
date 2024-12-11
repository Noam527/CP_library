const int md = 998244353;
// Assumes prime modulo at most 2^30.
template<int MOD>
struct Mint {
	int x;
	Mint(ll y = 0) {
		if (0 <= y && y < MOD) x = y;
		else {
			x = y % MOD + MOD;
			if (x >= MOD) x -= MOD;
		}
	}
	Mint operator + (Mint a) { return Mint(x + a.x); }
	Mint operator - (Mint a) { return Mint(x - a.x); }
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
	bool operator == (Mint a) { return x == a.x; }
	bool operator != (Mint a) { return x != a.x; }
	friend ostream& operator<<(ostream& os, Mint n) {
		return os << n.x;
	}
};
using mint_t = Mint<md>;
const int FLIM = 500005; // IMP: choose properly
mint_t fac[FLIM], ifac[FLIM];
void prepare() { // IMP: call prepare()
	fac[0] = ifac[0] = mint_t(1);
	for (int i = 1; i < FLIM; i++)
		fac[i] = fac[i - 1] * mint_t(i);
	ifac[FLIM - 1] = fac[FLIM - 1].inv();
	for (int i = FLIM - 2; i > 0; i--)
		ifac[i] = ifac[i + 1] * mint_t(i + 1);
}
mint_t choose(int n, int k) {
	if (n < k) return mint_t(0);
	return fac[n] * ifac[k] * ifac[n - k];
}