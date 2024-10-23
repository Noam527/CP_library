// Make sure n * m fits in type T!
template<typename T> struct frac {
	T n, m; // represents n/m, m > 0
	frac(T x = 0) : n(x), m(1) {}
	frac(T top, T bot) : n(top), m(bot) {
		if (m < 0) n = -n, m = -m;
	}
#define CMP(X) \
	bool operator X (const frac &r) const { \
		return n * r.m X r.n * m; \
	}
	CMP(== ); CMP(!= ); CMP(< ); CMP(<= ); CMP(> ); CMP(>= );
	frac operator -() const { return frac(-n, m); }
	frac operator +(const frac& r) const {
		if (m == r.m) return frac(n + r.n, m);
		return frac(n * r.m + m * r.n, m * r.m);
	}
	frac operator -(const frac& r) const { return *this + (-r); }
	frac operator *(const frac& r) const {
		return frac(n * r.n, m * r.m);
	}
	friend ostream& operator<<(ostream& os, frac f) {
		return os << f.n << "/" << f.m;
	}
};