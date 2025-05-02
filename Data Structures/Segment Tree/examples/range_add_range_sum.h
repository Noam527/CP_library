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

struct esum {
	itype v;
	int l;
	esum() : v(0), l(0) {}
	esum(itype v, int l = 1) : v(v), l(l) {}
	esum operator * (const esum &other) const {
		return esum(v + other.v, l + other.l);
	}
	esum operator * (const tag &other) const {
		return esum(v + other.add * l, l);
	}
};