/*
 * Assuming `good` returns `false` and then `true`, finds the first x in [lo, hi] for which good(x) is true.
 * If there is no such x, returns hi + 1.
*/
template<typename T, class F>
T first_bs(T lo, T hi, const F &good) {
	hi++;
	T mid;
	while (lo < hi) {
		if (lo < 0 && 0 < hi) mid = (lo + hi) >> 1;
		else mid = lo + ((hi - lo) >> 1);
		if (good(mid)) hi = mid;
		else lo = mid + 1;
	}
	return lo;
}
/*
 * Assuming `good` returns `true` and then `false`, finds the last x in [lo, hi] for which good(x) is true.
 * If there is no such x, returns lo - 1.
*/
template<typename T, class F>
T last_bs(T lo, T hi, const F &good) {
	lo--;
	T mid;
	while (lo < hi) {
		if (lo < 0 && 0 < hi) mid = (lo + hi + 1) >> 1;
		else mid = lo + ((hi - lo + 1) >> 1);
		if (good(mid)) lo = mid;
		else hi = mid - 1;
	}
	return lo;
}