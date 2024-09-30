#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <random>
#include <time.h>
#include <cmath>
#include <functional>
#include <utility>
#include <sstream>
#include <climits>
#include <complex>
#include <array>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
constexpr int OO = 1;
const int md = (int)1e9 + 7; // (int)1e9 + 7, 998244353
const ll inf = 2e18;

namespace {
	template <class T>
	std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
		out << "[ ";
		for (int i = 0; i < vec.size(); ++i) {
			out << (i ? ", " : "") << vec[i];
		}
		out << " ]";
		return out;
	}

#define PRINT_VARS(...) print_vars(#__VA_ARGS__, __VA_ARGS__)
#define PRINT_VARS_DBG(...) if constexpr (OO) PRINT_VARS(__VA_ARGS__)

	template <class T, class... Args>
	void print_vars(std::vector<std::string> labels, T arg, Args... args) {
		std::string label = labels[labels.size() - sizeof...(args) - 1];
		std::cout << label << " = " << arg;
		if constexpr (sizeof...(args) > 0) {
			std::cout << ",";
			print_vars(labels, args...);
		}
		else {
			std::cout << std::endl;
		}
	}

	template <class... Args>
	void print_vars(std::string labels, Args... args) {
		std::stringstream input_labels(labels);
		std::string label;
		std::vector<std::string> vectorized_lables;
		while (std::getline(input_labels, label, ',')) {
			vectorized_lables.push_back(label);
		}
		print_vars(vectorized_lables, args...);
	}
}

const ldb EPS = 1e-10;
const ldb PI = atan2l(0, -1);
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> int epssgn(T x) { return (x > EPS) - (x < -EPS); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a) - y * sin(a), x*sin(a) + y * cos(a));
	}
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")";
	}
};
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return { -(s1.cross(e1, s2) == 0), P(0, 0) };
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return { 1, (s1 * p + e1 * q) / d };
}

typedef Point<double> pd;
struct plane {
	pd p, dir;
	double angle;
	plane(pd p, pd dir) : p(p), dir(dir), angle(dir.angle()) {}
	bool in(pd q) {
		return dir.cross(q - p) > 0;
	}
	int diff(plane &pre) { // -1 if close, 0 if opposite, 1 else
		if (angle >= pre.angle) return epssgn(angle - pre.angle - PI);
		return epssgn(angle - pre.angle + PI);
	}
	pd intersect(plane &a) { // assumes not parallel
		return lineInter(p, p + dir, a.p, a.p + a.dir).second;
	}
	bool operator < (plane &a) {
		if (angle != a.angle) return angle < a.angle;
		return a.in(p);
	}
};

/*
 * inplace. returns whether the intersection is finite or not, so:
 * if intersection is empty, `a` becomes empty, returns `false`.
 * if the intersection is infinite, `a` is undefined but `true` is returned.
 * otherwise, a is the planes defining the intersection, in order, and `false` is returned.
*/
bool halfplane_intersection(vector<plane> &a) {
	sort(a.begin(), a.end());
	vector<plane> b = { a[0] };
	for (int i = 1; i < a.size(); i++)
		if (a[i - 1].angle < a[i].angle)
			b.push_back(a[i]);
	a = b;
	int n = a.size();
	if (n == 1) return true;
	// check for infinite
	for (int i = 0; i < n; i++) {
		int p = (i - 1 + n) % n;
		if (a[i].in(a[i].p + a[p].dir))
			return true;
		if (a[i].diff(a[p]) == 0) {
			if (a[i].in(a[p].p)) return true; // inf
			return a.clear(), false; // empty
		}
	}
	b = { a[0], a[1] };
#define bsz (int)b.size() // helps readability
	for (int at = 2; at < 3 * n; at++) {
		int i = at % n;
		while (bsz >= 2) {
			if (a[i].diff(b[bsz - 2]) >= 0) {
				// check empty and break
				if (!a[i].in(b.back().intersect(b[bsz - 2])))
					return a.clear(), false;
				break;
			}
			if (!b.back().in(a[i].intersect(b[bsz - 2])))
				break;
			b.pop_back();
		}
		b.push_back(a[i]);
	}
	int st = 1, en;
	while (b[st - 1] < b[st]) st++;
	en = st + 1;
	while (b[en - 1] < b[en]) en++;
	a = vector<plane>(b.begin() + st, b.begin() + en);
	return false; // certainly not inf
}

void test(vector<plane> a) {
	srand(time(NULL));
	auto b = a;
	bool res = halfplane_intersection(b);
	cout << "4 rotations tests..." << '\n';
	for (int i = 1; i < 4; i++) {
		cout << "rotation " << i << '\n';
		auto c = a;
		for (int t = 0; t < i; t++) {
			for (auto &j : c) {
				j.p = j.p.perp();
				j.dir = j.dir.perp();
			}
		}
		if (res != halfplane_intersection(c)) {
			cout << "failed at infinity\n";
			return;
		}
		if (res) continue;
		if (b.size() != c.size()) {
			if (b.size() == 0) {
				cout << "answer empty, but rotation says not\n";
				return;
			}
			if (c.size() == 0) {
				cout << "answer nonempty, but rotation says empty\n";
				return;
			}
			cout << "failed at size test\n";
			return;
		}
		for (int t = i; t < 4; t++) {
			for (auto &j : c) {
				j.p = j.p.perp();
				j.dir = j.dir.perp();
			}
		}
		sort(b.begin(), b.end());
		sort(c.begin(), c.end());
		// check equality
		for (int i = 0; i < b.size(); i++) {
			if (!(b[i].p == c[i].p && b[i].dir == c[i].dir)) {
				cout << "failed at equality\n";
				return;
			}
		}
	}
	cout << "passed 4 rotations test, onto random rotations...\n";
	for (int test = 0; test < 1000; test++) {
		double angle = rand() % 1000;
		auto c = a, d = b;
		for (auto &j : c) {
			j = plane(j.p.rotate(angle), j.dir.rotate(angle));
		}
		for (auto &j : d) {
			j = plane(j.p.rotate(angle), j.dir.rotate(angle));
		}
		if (res != halfplane_intersection(c)) {
			cout << "failed at infinity\n";
			return;
		}
		if (res) continue;
		if (c.size() != d.size()) {
			if (d.size() == 0) {
				cout << "answer empty, but rotation says not\n";
				return;
			}
			if (c.size() == 0) {
				cout << "answer nonempty, but rotation says empty\n";
				return;
			}
			cout << "failed at size test\n";
			return;
		}
		sort(c.begin(), c.end());
		sort(d.begin(), d.end());
		for (int i = 0; i < c.size(); i++) {
			if (!(c[i].p == d[i].p && c[i].dir == d[i].dir)) {
				cout << "failed at equality test\n";
				return;
			}
		}
	}
	cout << "passed all tests\n";
}

void solve() {
	int n;
	cin >> n;
	vector<plane> a;
	for (int i = 0; i < n; i++) {
		double sx, sy, dx, dy;
		cout << "point and direction: ";
		cin >> sx >> sy >> dx >> dy;
		a.emplace_back(pd(sx, sy), pd(dx, dy));
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(a.begin(), a.end(), g);
	auto copy = a;

	// first output the result to the user...
	if (halfplane_intersection(a)) {
		cout << "infinite\n";
	}
	else if (!a.size()) {
		cout << "empty\n";
	}
	else {
		cout << "border:\n";
		for (auto &i : a) {
			cout << i.p << " " << i.dir << '\n';
		}
	}
	// now test
	test(copy);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cout.precision(10);
	int tests = 1;
	//cin >> tests;
	while (tests--) solve();
}