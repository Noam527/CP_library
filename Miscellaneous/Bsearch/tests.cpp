void solve() {
	int lo = -1000, hi = 1000;
	cout << first_bs(lo, hi, [](int x) {
		return x * x * x > 27;
	}) << endl;
	cout << first_bs(lo, hi, [](int x) {
		return x * x * x >= 27;
	}) << endl;
	cout << first_bs(lo, hi, [](int x) {
		return x * x * x > -1000;
	}) << endl;
	cout << first_bs(lo, hi, [](int x) {
		return x * x * x >= -1000;
	}) << endl;
	cout << last_bs(lo, hi, [](int x) {
		return x * x * x < 27;
	}) << endl;
	cout << last_bs(lo, hi, [](int x) {
		return x * x * x <= 27;
	}) << endl;
	cout << last_bs(lo, hi, [](int x) {
		return x * x * x < -1000;
	}) << endl;
	cout << last_bs(lo, hi, [](int x) {
		return x * x * x <= 1000;
	}) << endl;
}