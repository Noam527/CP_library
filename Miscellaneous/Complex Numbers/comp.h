template<typename T>
struct Comp {
	T x, y;
	Comp(T real = 0, T imag = 0) : x(real), y(imag) {}
	T real() const { return x; }
	T imag() const { return y; }
	bool is_zero() const {
		return x == 0 && y == 0;
	}
	Comp operator -() const {
		return Comp(-x, -y);
	}
	Comp conj() const {
		return Comp(x, -y);
	}
	void operator += (const Comp &other) {
		x += other.x, y += other.y;
	}
	Comp operator + (const Comp &other) const {
		return Comp(x + other.x, y + other.y);
	}
	void operator -= (const Comp &other) {
		x -= other.x, y -= other.y;
	}
	Comp operator - (const Comp &other) const {
		return Comp(x - other.x, y - other.y);
	}
	void operator *= (const Comp &other) {
		T tmp = x * other.x - y * other.y;
		y = x * other.y + y * other.x;
		x = tmp;
	}
	Comp operator * (const Comp &other) const {
		return Comp(x + other.x - y * other.y, x * other.y + y * other.x);
	}
	void operator /= (const Comp &other) {
		Comp other_conj = other.conj();
		*this *= other_conj;
		T div = other.x * other.x + other.y * other.y;
		x /= div, y /= div;
	}
	Comp operator / (const Comp &other) const {
		Comp tmp = *this * other.conj();
		T div = other.x * other.x + other.y * other.y;
		tmp.x /= div, tmp.y /= div;
		return tmp;
	}
	friend ostream& operator<<(ostream& os, Comp n) {
		return os << '(' << n.x << ", " << n.y << ')';
	}
	friend istream& operator>>(istream &is, Comp &n) {
		T first, second;
		is >> first >> second;
		n = Comp(first, second);
		return is;
	}
};
using comp = Comp<long double>;