const int FLIM = 500005; // IMP: choose properly
mint fac[FLIM], ifac[FLIM];
void prepare() { // IMP: call prepare()
	fac[0] = ifac[0] = mint(1);
	for (int i = 1; i < FLIM; i++)
		fac[i] = fac[i - 1] * mint(i);
	ifac[FLIM - 1] = fac[FLIM - 1].inv();
	for (int i = FLIM - 2; i > 0; i--)
		ifac[i] = ifac[i + 1] * mint(i + 1);
}
mint choose(int n, int k) {
	if (n < k) return mint(0);
	return fac[n] * ifac[k] * ifac[n - k];
}
ll gcd(ll x, ll y) {
	return !y ? x : gcd(y, x % y);
}
ll lcm(ll x, ll y) {
	return x / gcd(x, y) * y;
}