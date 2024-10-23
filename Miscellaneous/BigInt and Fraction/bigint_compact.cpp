// Implement private methods before publics, for autocomplete
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