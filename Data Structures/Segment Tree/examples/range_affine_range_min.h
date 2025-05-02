using itype = ll;
struct tag {
	itype mult, add;
	tag() : mult(1), add(0) {}
	tag(itype m, itype a) : mult(m), add(a) {}
	bool empty() const {
		return mult == 1 && add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(mult * other.mult, other.mult * add + other.add);
	}
};

// NOTE: assuming mult >= 0
struct emin {
	itype v;
	emin() : v(numeric_limits<itype>::max() / 2) {} // IMP: make sure this is sufficient
	emin(itype v) : v(v) {}
	emin operator * (const emin &other) const {
		return emin(min(v, other.v));
	}
	emin operator * (const tag &other) const {
		return emin(other.mult * v + other.add);
	}
};