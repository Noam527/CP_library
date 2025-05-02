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
	Mint(int y, bool safe) {
		safe;
		x = y;
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
	Mint inv() const { return *this ^ (MOD - 2); }
	Mint operator / (Mint a) const { return *this * a.inv(); }
	void operator /= (Mint a) {
		*this *= a.inv();
	}
	bool operator == (Mint a) const { return x == a.x; }
	bool operator != (Mint a) const { return x != a.x; }
	friend ostream& operator<<(ostream& os, Mint n) {
		return os << n.x;
	}
};
using mint = Mint<md>;