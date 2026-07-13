namespace {
	using ft = long double;
	const ft EPS = 1e-12;
	bool almost_eq(ft x, ft y) {
		return abs(x - y) < EPS;
	}

	// T is the type of the coefficients
	template<typename T>
	struct real_poly {
		using comp = complex<T>;
		vector<T> p;
		real_poly() {}
		real_poly(size_t sz, T values = T(0)) : p(sz, values) {}
		real_poly(const vector<T> &values) : p(values) {}
		real_poly(const real_poly &other) : p(other.p) {}
		real_poly& operator = (const real_poly &other) {
			p = other.p;
			return *this;
		}
		// ************** BEGIN UTILITY **************
		// Removes all zero leading coefficients
		void truncate() {
			if (p.size() == 0) return;
			size_t ind = p.size() - 1;
			while (ind > 0 && p[ind] == 0) ind--;
			if (p[ind] != 0) {
				p.resize(ind + 1);
			}
			else {
				p.clear();
			}
		}
		void resize(size_t newsize) {
			p.resize(newsize, T(0));
		}
		size_t size() const {
			return p.size();
		}
		int degree() const {
			return (int)p.size() - 1;
		}
		inline T coeff(int k) const {
			return p[k];
		}
		inline T operator [] (int k) const {
			return coeff(k);
		}
		void pretty_print() const {
			auto output_val = [](T x) {
				ll y = roundl(x);
				if (almost_eq(x, T(y))) {
					cout << y;
				}
				else {
					cout << x;
				}
			};
			real_poly q(p);
			while (q.size() > 0 && almost_eq(q.p.back(), 0)) q.p.pop_back();
			if (q.size() == 0) {
				cout << "0" << endl;
				return;
			}
			if (q.size() == 1) {
				output_val(q[0]);
				cout << endl;
				return;
			}
			// print most significant
			if (!almost_eq(q[q.size() - 1], 1) && !almost_eq(q[q.size() - 1], -1)) {
				output_val(q[q.size() - 1]);
				cout << "x";
			}
			else if (q[q.size() - 1] > 0)
				cout << "x";
			else
				cout << "-x";
			if (q.size() > 2) {
				cout << "^" << q.size() - 1;
			}
			for (int i = q.size() - 2; i >= 0; i--) {
				if (almost_eq(q[i], 0)) continue;
				if (q[i] > 0) cout << " + ";
				else cout << " - ";

				if (!almost_eq(abs(q[i]), 1) || i == 0) output_val(abs(q[i]));
				if (i > 0) {
					cout << "x";
					if (i > 1) {
						cout << "^" << i;
					}
				}
			}
			cout << endl;
		}
		// *************** END UTILITY ***************

		// ************** BEGIN BASIC OPS **************
		T eval(T x) const {
			T result(0);
			for (int i = (int)p.size() - 1; i >= 0; i--)
				result = result * x + p[i];
			return result;
		}
		inline T operator () (T x) const {
			return eval(x);
		}
		
		void operator += (const real_poly &other) {
			if (size() < other.size()) p.resize(other.size());
			size_t iter = other.size();
			for (size_t i = 0; i < iter; i++)
				p[i] += other[i];
		}
		real_poly operator + (const real_poly &other) const {
			real_poly result(max(size(), other.size()));
			for (size_t i = 0; i < p.size(); i++) {
				result.p[i] += p[i];
			}
			for (size_t i = 0; i < other.size(); i++) {
				result.p[i] += other[i];
			}
			return result;
		}
		void operator -= (const real_poly &other) {
			if (size() < other.size()) p.resize(other.size());
			size_t iter = other.size();
			for (size_t i = 0; i < iter; i++)
				p[i] -= other[i];
		}
		real_poly operator - (const real_poly &other) const {
			real_poly result(max(size(), other.size()));
			for (size_t i = 0; i < p.size(); i++) {
				result.p[i] = p[i];
			}
			for (size_t i = 0; i < other.size(); i++) {
				result.p[i] -= other[i];
			}
			return result;
		}
		real_poly derivative() const {
			if (p.size() <= 1) return real_poly();
			real_poly Q(p.size() - 1);
			for (size_t i = 0; i < Q.size(); i++)
				Q[i] = T(i + 1) * p[i + 1];
			return Q;
		}
		// with the free coefficient being 0
		real_poly integral() const {
			if (p.size() == 0) return real_poly();
			real_poly Q(p.size() + 1);
			for (size_t i = 1; i < Q.size(); i++)
				Q[i] = p[i - 1] / T(i);
			return Q;
		}
		// *************** END BASIC OPS ***************

		// ************** BEGIN ADV. OPS **************
		static void fft(vector<comp> &a) {
			if (a.size() == 0) return;
			size_t n = a.size(), L = 31 - __builtin_clz(n);
			// fix if p's size is not a power of 2
			while (n != (n & -n)) n += n & -n;
			if (a.size() < n) a.resize(n);

			static vector<comp> R(2, 1);
			static vector<comp> rt(2, 1);
			for (static size_t k = 2; k < n; k *= 2) {
				R.resize(n); rt.resize(n);
				auto x = polar(1.0L, acos(-1.0L) / k);
				for (size_t i = k; i < 2 * k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
			}
			vector<size_t> rev(n);
			for (size_t i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
			for (size_t i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
			// now to really do the fft (and some illegal shit to skip std::complex)
			for (size_t k = 1; k < n; k *= 2)
				for (size_t i = 0; i < n; i += 2 * k) for (size_t j = 0; j < k; j++) {
					// comp z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
					auto x = (T *)&rt[j + k], y = (T *)&a[i + j + k];        /// exclude-line
					comp z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);           /// exclude-line
					a[i + j + k] = a[i + j] - z;
					a[i + j] += z;
				}
		}
		real_poly operator * (const real_poly &other) const {
			if (size() == 0 || other.size() == 0) return real_poly();
			vector<T> result(size() + other.size() - 1);
			int L = 32 - __builtin_clz(result.size()), n = 1 << L;
			vector<comp> in(n), out(n);
			copy(p.begin(), p.end(), begin(in));
			for (int i = 0; i < (int)other.size(); i++) in[i].imag(other[i]);
			fft(in);
			for (comp &x : in) x *= x;
			for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
			fft(out);
			for (int i = 0; i < (int)result.size(); i++) result[i] = imag(out[i]) / (4 * n);
			return result;
		}
		void operator *= (const real_poly &other) {
			if (size() == 0 || other.size() == 0) {
				p.clear();
				return;
			}
			size_t newsize = size() + other.size() - 1;
			size_t L = 32 - __builtin_clz(newsize), n = 1 << L;
			vector<comp> in(n), out(n);
			copy(p.begin(), p.end(), begin(in));
			resize(newsize);
			for (size_t i = 0; i < other.size(); i++) in[i].imag(other[i]);
			fft(in);
			for (comp &x : in) x *= x;
			for (size_t i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
			fft(out);
			for (size_t i = 0; i < newsize; i++) p[i] = imag(out[i]) / (4 * n);
		}
		// Polynomial inverse, but only the first n coefficients (upto x^{n-1})
		real_poly inv(size_t n) const {
			if (p.size() == 0 || p[0] == 0) {
				throw std::runtime_error("Cannot inverse a polynomial with 0 as the free coefficient.");
			}
			real_poly B(1, T(1) / p[0]);
			// now inverse modulo x^1, we want inverse modulo x^n
			for (size_t k = 1; k < n; k *= 2) {
				// newB = B(2 - pB) (mod x^2k)
				// but first truncate p
				real_poly truncated_p(min(2 * k, size()));
				for (size_t i = 0; i < truncated_p.p.size(); i++)
					truncated_p.p[i] = p[i];
				real_poly rhs(1, 2);
				rhs -= truncated_p * B;
				B *= rhs;
				B.resize(2 * k);
			}
			B.resize(n);
			return B;
		}
		// *************** END ADV. OPS ***************
	};
	using rpoly = real_poly<ft>;
};