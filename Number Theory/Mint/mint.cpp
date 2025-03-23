// Assumes prime modulo at most 2^30.
const int md = 998244353; // IMP: verify prime, maybe (int)1e9 + 7
template<int MOD>
struct Mint {
	int x;
	Mint(ll y = 0) {
		if (0 <= y && y < MOD) x = y;
		else {
			x = y % MOD;
			if (x < 0) x += MOD;
		}
	}
	Mint operator + (Mint a) { return Mint(x + a.x); }
	void operator += (Mint a) {
		x += a.x;
		if (x >= MOD) x -= MOD;
	}
	Mint operator - (Mint a) { return Mint(x - a.x); }
	void operator -= (Mint a) {
		x -= a.x;
		if (x < 0) x += MOD;
	}
	Mint operator * (Mint a) { return Mint((ll)x * a.x % MOD); }
	void operator *= (Mint a) {
		x = (ll)x * a.x % MOD;
	}
	Mint operator ^ (ll e) {
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
	Mint inv() { return *this ^ (MOD - 2); }
	Mint operator / (Mint a) { return *this * a.inv(); }
	void operator /= (Mint a) {
		*this *= a.inv();
	}
	bool operator == (Mint a) { return x == a.x; }
	bool operator != (Mint a) { return x != a.x; }
	friend ostream& operator<<(ostream& os, Mint n) {
		return os << n.x;
	}
};
using mint = Mint<md>;