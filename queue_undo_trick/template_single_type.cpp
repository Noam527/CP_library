/* ---------- UPDATE TYPE ---------- */
// TODO: struct update with usual constructors
struct update {};
/* ---------- UNDERLYING DS ---------- */
struct someds {
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

	// TODO: updates, choose return types
private:

public:
	// update convention: push and switch case
	void upd(const update &u) {
		// TODO: push_back change here
		updates.push_back(u);
		// TODO: call update
	}
	// undo convention: return the update that was undone
	update undo() {
		// TODO: roll back from changes
		// TODO: pop_back last change
		update tmp = move(updates.back());
		updates.pop_back();
		return tmp;
	}
};

#define ds knapsack
struct queuesack : ds {
	vector<bool> st;
	vector<update> tmp[2];
	int nxtA;
	// TODO: imitate constructors
	queuesack() : nxtA(0) {}
	queuesack(int sz) : ds(sz) {
		nxtA = 0;
	}
	// TODO: choose return type
	void upd(const update &u) {
		st.push_back(1);
		ds::upd(u);
	}
	void undo() {
		while (nxtA < st.size() && st[nxtA]) nxtA++;
		if (nxtA == st.size()) {
			// reverse
			nxtA = 0;
			tmp[0].clear();
			for (int i = 0; i < st.size(); i++) {
				tmp[0].push_back(ds::undo());
				st[i] = 0;
			}
			st.pop_back();
			tmp[0].pop_back();
			for (auto &u : tmp[0])
				ds::upd(u);
			return;
		}
		if (!st.back()) {
			// A on top
			st.pop_back();
			ds::undo();
			return;
		}
		// fix
		tmp[0].clear(), tmp[1].clear();
		do {
			tmp[st.back()].push_back(ds::undo());
			st.pop_back();
		} while (nxtA < st.size() && tmp[0].size() < tmp[1].size());
		for (int i : {1, 0}) {
			reverse(tmp[i].begin(), tmp[i].end());
			if (i == 0) tmp[0].pop_back();
			for (auto &u : tmp[i]) {
				ds::upd(u);
				st.push_back(i);
			}
		}
	}
};
#undef ds
