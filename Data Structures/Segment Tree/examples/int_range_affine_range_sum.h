struct tag {
	int mult, add;
	tag() : mult(1), add(0) {}
	tag(int m, int a) : mult(m), add(a) {}
	bool empty() const {
		return mult == 1 && add == 0;
	}
	tag operator * (const tag &other) const {
		return tag(mult * other.mult, other.mult * add + other.add);
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
		return esum(other.mult * v + other.add * l, l);
	}
};