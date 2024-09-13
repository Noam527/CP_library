// first add queries, then call solve
struct mo {
	static const int K; // IMP: set K to be approximately N / sqrt(Q).
	struct query {
		int l, r, ind;
		int ans; // IMP: field to hold query answer, defaulted as int
		query(int l = 0, int r = 0, int ind = 0) : l(l), r(r), ind(ind) {}
		bool operator < (const query& other) const {
			if (l / K != other.l / K)
				return l < other.l;
			if ((l / K) % 2 == 0)
				return r < other.r;
			return r > other.r;
		}
	};
	// IMP: the specific data structure members and constructor for default state
	void add(int i); // IMP: function to add element at index i to the data structure
	void remove(int i); // IMP: function to remove element at index i from the data structure
	int answer_query(); // IMP: function to answer the current given the current state. defaulted as int

	vector<query> Q;
	void add_query(int l, int r) {
		Q.push_back(query(l, r, (int)Q.size()));
	}
	// IMP: change the return type inside the vector to fit the problem
	vector<int> solve() {
		sort(Q.begin(), Q.end());
		vector<int> ans(Q.size());
		int l = 0, r = -1;
		for (auto& q : Q) {
			while (l > q.l)
				add(--l);
			while (r < q.r)
				add(++r);
			while (l < q.l)
				remove(l++);
			while (r > q.r)
				remove(r--);
			ans[q.ind] = answer_query();
		}
		return ans;
	}
};