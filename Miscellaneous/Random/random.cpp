mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd_range(int l, int r) {
	return rng() % (r - l + 1) + l;
}

template<typename T>
void good_shuffle(vector<T> &a) {
	shuffle(a.begin(), a.end(), rng);
}