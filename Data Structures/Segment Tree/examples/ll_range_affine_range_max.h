struct tag {
	ll mult, add;
	tag() : mult(1), add(0) {}
	tag(ll m, ll a) : mult(m), add(a) {}
	bool empty() const {
		return mult == 1 && add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(mult * other.mult, other.mult * add + other.add);
	}
};

// NOTE: assuming mult >= 0
struct emax {
	ll v;
	emax() : v(numeric_limits<ll>::min() / 2) {} // IMP: make sure this is sufficient
	emax(ll v) : v(v) {}
	emax operator * (const emax &other) const {
		return emax(max(v, other.v));
	}
	emax operator * (const tag &other) const {
		return emax(other.mult * v + other.add);
	}
};