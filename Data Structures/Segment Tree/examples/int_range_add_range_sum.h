struct tag {
	int add;
	tag() : add(0) {}
	tag(int add) : add(add) {}
	bool empty() const {
		return add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(add + other.add);
	}
};

struct esum {
	int v;
	int l;
	esum() : v(0), l(0) {}
	esum(int v, int l = 1) : v(v), l(l) {}
	esum operator * (const esum &other) const {
		return esum(v + other.v, l + other.l);
	}
	esum operator * (const tag &other) const {
		return esum(v + other.add * l, l);
	}
};