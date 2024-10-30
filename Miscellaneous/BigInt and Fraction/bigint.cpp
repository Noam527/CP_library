template<int N> struct bigint { // 32N-bit number, SIGNED!
	using u32 = uint32_t;
	using u64 = uint64_t;
	bigint(ll x = 0) {
		for (auto& i : inner) i = u32(x), x >>= 32;
	}
	u32 to32() { return inner[0]; }
	u64 to64() { return inner[0] | (u64(inner[1]) << 32); }
#define CMP(X) \
	bool operator X (const bigint<N> &r) const { \
		for (int i = N - 1; i >= 0; i--) if (sat(i) != r.sat(i)) \
			return sat(i) X r.sat(i);\
		return sat(0) X r.sat(0);\
	}
	CMP(== ); CMP(!= ); CMP(< ); CMP(<= ); CMP(> ); CMP(>= );
	bigint<N> operator -() const {
		bigint<N> result;
		for (int i = 0; i < N; i++) result[i] = ~inner[i];
		for (int i = 0; i < N; i++) if (++result[i] != 0) break;
		return result;
	}
	bigint<N> operator + (const bigint<N>& r) const {
		array<u64, N> board = {};
		for (int i = 0; i < N; i++)
			board[i] = u64(inner[i]) + r[i];
		fixall(board);
		return bigint<N>(board);
	}
	bigint<N> operator - (const bigint<N>& r) const {
		return *this + (-r);
	}
	bigint<N> operator * (const bigint<N>& r) const {
		array<u64, N> board = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; i + j < N; j++)
				board[i + j] += u64(inner[i]) * r[j];
			fixall(board);
		}
		return bigint<N>(board);
	}
	// OPTIONALS: Usually not needed, maybe you need base b repr.
	// signed floor division, assuming r > 0. -1 / 2 = -1.
	bigint<N> operator / (const bigint<N>& r) const {
		vector<bigint<N>> mult = { r };
		while (1) {
			auto q = mult.back() + mult.back();
			if (q < bigint<N>(0)) break;
			mult.push_back(q);
		}
		bigint<N> add, sub, cp = *this;
		while (cp < 0)
			cp = cp + mult.back(), sub = sub + 1;
		for (int i = (int)mult.size() - 1; i >= 0; i--) {
			if (i + 1 < mult.size()) sub = sub + sub;
			add = add + add;
			while (cp >= mult[i])
				cp = cp - mult[i], add = add + 1;
		}
		return add - sub;
	}
	bigint<N> operator % (const bigint<N>& r) const {
		return *this - r * (*this / r);
	}
	string base10() const {
		bool isneg = false;
		bigint<N> cp = *this;
		if (cp == 0) return "0";
		if (cp < 0) isneg = true, cp = -cp;
		string result = "";
		while (cp > 0)
			result.push_back(char('0' + (cp % 10).to32())), cp = cp / 10;
		if (isneg) result.push_back('-');
		reverse(result.begin(), result.end());
		return result;
	}
	friend ostream& operator << (ostream& os, bigint<N> n) {
		return os << n.base10();
	}
	bigint(string b10) {
		bigint<N> pw(1);
		for (auto& i : inner) i = 0;
		reverse(b10.begin(), b10.end());
		for (auto& i : b10) {
			if (i == '-') *this = -*this;
			else *this = *this + pw * (i - '0');
			pw = pw * 10;
		}
	}
private:
	array<u32, N> inner;
	template<typename T> bigint(const array<T, N>& x) {
		for (int i = 0; i < N; i++) inner[i] = x[i];
	}
	ll sat(int i) const { // signed at: regard last entry as signed
		if (i == N - 1) return ll(int(inner[i]));
		return ll(inner[i]);
	}
	u32& operator [] (int i) { return inner[i]; }
	u32 operator [] (int i) const { return inner[i]; }
	static void fix(u64& low, u64& high) {
		high += low >> 32, low = (low << 32) >> 32;
	}
	static void fixall(array<u64, N>& a) {
		for (int i = 0; i + 1 < N; i++)
			fix(a[i], a[i + 1]);
		a[N - 1] = (a[N - 1] << 32) >> 32;
	}
};