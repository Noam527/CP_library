/* -------------------- BASE CLASS -------------------- */

template<typename update>
struct queue_undo_trick {
	vector<int> st;
	vector<update> tmp[2];
	int nxt0;
	queue_undo_trick() : nxt0(0) {}
	void qupdate(const update &u) {
		st.push_back(1), supdate(u);
	}
	void qundo() {
		while (nxt0 < st.size() && st[nxt0]) nxt0++;
		if (nxt0 == st.size()) {
			nxt0 = 0;
			tmp[0].clear();
			for (auto &i : st)
				tmp[0].push_back(sundo()), i = 0;
			st.pop_back(), tmp[0].pop_back();
			for (auto &u : tmp[0])
				supdate(u);
			return;
		}
		if (!st.back()) {
			st.pop_back();
			sundo();
			return;
		}
		tmp[0].clear(), tmp[1].clear();
		do {
			tmp[st.back()].push_back(sundo());
			st.pop_back();
		} while (nxt0 < st.size() && tmp[0].size() < tmp[1].size());
		for (int i : {1, 0}) {
			reverse(tmp[i].begin(), tmp[i].end());
			if (i == 0) tmp[0].pop_back();
			for (auto &u : tmp[i])
				supdate(u), st.push_back(i);
		}
	}
	virtual update sundo() = 0;
	virtual void supdate(const update &u) = 0;
};

// IMP: struct uniting all types of updates
struct update {};
struct your_ds : public queue_undo_trick<update> {
	// IMP: data structure members, constructors, queries
	// IMP: keeping track of changes for stack undo, for example: vector of (index, prev_value)
	vector<update> updates; // memorize all updates
private:
	virtual void supdate(const update &u) {
		updates.push_back(u);
		// IMP: perform the update and keep track of changes
	}
	virtual update sundo() {
		// IMP: roll back last change and pop it
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};