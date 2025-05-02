using itype = ll;
struct tag {
	itype add;
	tag() : add(0) {}
	tag(itype add) : add(add) {}
	bool empty() const {
		return add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(add + other.add);
	}
};

struct emin {
	itype v;
	emin() : v(numeric_limits<itype>::max() / 2) {} // IMP: make sure this is sufficient
	emin(itype v) : v(v) {}
	emin operator * (const emin &other) const {
		return emin(min(v, other.v));
	}
	emin operator * (const tag &other) const {
		return emin(v + other.add);
	}
};