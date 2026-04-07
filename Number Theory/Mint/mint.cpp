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