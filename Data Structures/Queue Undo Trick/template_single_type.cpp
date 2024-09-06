/* -------------------- BASE CLASS -------------------- */

template<typename upd_t>
struct queue_undo_trick {
	vector<bool> st;
	vector<upd_t> tmp[2];
	int nxt0;
	queue_undo_trick() : nxt0(0) {}
	void qupdate(const upd_t &u) {
		st.push_back(1);
		supdate(u);
	}
	void qundo() {
		while (nxt0 < st.size() && st[nxt0]) nxt0++;
		if (nxt0 == st.size()) {
			// reverse. we assume st.size() > 0.
			nxt0 = 0;
			tmp[0].clear();
			for (int i = 0; i < st.size(); i++) {
				tmp[0].push_back(sundo());
				st[i] = 0;
			}
			st.pop_back();
			tmp[0].pop_back();
			for (auto &u : tmp[0])
				supdate(u);
			return;
		}
		if (!st.back()) {
			// A on top
			st.pop_back();
			sundo();
			return;
		}
		// fix
		tmp[0].clear(), tmp[1].clear();
		do {
			tmp[st.back()].push_back(sundo());
			st.pop_back();
		} while (nxt0 < st.size() && tmp[0].size() < tmp[1].size());
		for (int i : {1, 0}) {
			reverse(tmp[i].begin(), tmp[i].end());
			if (i == 0) tmp[0].pop_back();
			for (auto &u : tmp[i]) {
				supdate(u);
				st.push_back(i);
			}
		}
	}
	// to be implemented by inheriting class
	virtual upd_t sundo() = 0;
	virtual void supdate(const upd_t &u) = 0;
};

/* -------------------- UPDATE TYPE -------------------- */
// TODO: struct update with usual constructors
struct update {};
/* -------------------- INHERITING CLASS -------------------- */
// TODO: choose class name
struct your_queue_ds : public queue_undo_trick<update> {
	/*
	TODO
	normal variables
	*/
	// stack memory
	vector<update> updates;
	/*
	TODO
	tailored implementation of changes, usually elementary data types / struct change, along with vector<change>
	*/

	// TODO: constructors
	// TODO: queries
private:
	// TODO: updates, choose return types. In private so that the user doesn't call it on accident.

	// update convention: push and switch case
	// TODO: choose the return value
	virtual void supdate(const update &u) {
		// TODO: push_back change here
		updates.push_back(u);
		// TODO: call the actual update function (or just do it here)
	}
	// undo convention: return the update that was undone
	virtual update sundo() {
		// TODO: roll back from changes
		// TODO: pop_back last change
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};
