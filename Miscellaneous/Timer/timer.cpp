// int64_t
#define TIME_NS chrono::steady_clock::now().time_since_epoch().count()

// Times f(args...) in seconds.
// void f:     double ns = timeit(f, a, b);
// non-void f: auto [res, ns] = timeit(f, a, b);
template<typename F, typename... Args>
auto timeit(F&& f, Args&&... args) {
	using R = invoke_result_t<F, Args...>;
	int64_t start = TIME_NS;
	if constexpr (is_void_v<R>) {
		invoke(forward<F>(f), forward<Args>(args)...);
		return (double)(TIME_NS - start) / 1e9;
	} else {
		pair<R, double> out{invoke(forward<F>(f), forward<Args>(args)...), 0};
		out.second = (double)(TIME_NS - start) / 1e9;
		return out;
	}
}