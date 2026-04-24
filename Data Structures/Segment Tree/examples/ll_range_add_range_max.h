struct tag {
	ll add;
	tag() : add(0) {}
	tag(ll add) : add(add) {}
	bool empty() const {
		return add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(add + other.add);
	}
};
struct emax {
	ll v;
	emax() : v(numeric_limits<ll>::min() / 2) {} // IMP: make sure this is sufficient
	emax(ll v) : v(v) {}
	emax operator * (const emax &other) const {
		return emax(max(v, other.v));
	}
	emax operator * (const tag &other) const {
		return emax(v + other.add);
	}
};