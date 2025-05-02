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
struct emax {
	itype v;
	emax() : v(-inf) {}
	emax(itype v) : v(v) {}
	emax operator * (const emax &other) const {
		return emax(max(v, other.v));
	}
	emax operator * (const tag &other) const {
		return emax(v + other.add);
	}
};