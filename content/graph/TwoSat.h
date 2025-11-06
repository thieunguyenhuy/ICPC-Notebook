/**
 * Author: KickingKun
 * Description: 2sat -> finding an arbitrary equation
 * Time: O(n + m)
 * Status: Tested by KickingKun
 */

struct TwoSat { // convert vector -> array to get higher speed ....
	int n; vector <int> lab, num, low; vector <vector <int>> adj;
	int timeDfs, scc; stack <int> st;
	
	TwoSat (int _n) {
		this->n = _n; lab.assign(n * 2 + 1, 0); low.assign(n * 2 + 1, 0);
		num.assign(n * 2 + 1, 0); adj.assign(n * 2 + 1, vector <int>());
		timeDfs = scc = 0; while (!st.empty()) st.pop();
	}
	
	int NON(int u) {
		return u <= n ? u + n : u - n;
	}

	void add(int u, int v) {
		adj[u].emplace_back(v);
	}
	
	void add_u_or_v(int u, int v) { // u or v = 1
		adj[NON(u)].emplace_back(v); adj[NON(v)].emplace_back(u);
	}
	void assign(int u, bool val) { // u = val
		if (val == 1) add_u_or_v(u, u);
		else add_u_or_v(NON(u), NON(u));
	}
	void add_equal(int u, int v) { // u = v
		add_u_or_v(u, NON(v)); add_u_or_v(NON(u), v);
	}
	void add_non_equal(int u, int v) { // u != v
		add_u_or_v(u, v); add_u_or_v(NON(u), NON(v));
	}
	
	void dfs(int u) {
		low[u] = num[u] = ++timeDfs; st.emplace(u);
		for (int v: adj[u]) {
			if (lab[v]) continue;
			if (!num[v]) dfs(v), minimize(low[u], low[v]);
			else minimize(low[u], num[v]);
		}
		
		if (low[u] == num[u]) {
			++scc;
			while (true) {
				int v = st.top(); st.pop();
				lab[v] = scc; if (v == u) break;
			}
		}
	}
	
	bool check_exist() {
		for (int i = 1; i <= n; i++) {
			if (!lab[NON(i)]) dfs(NON(i));
			if (!lab[i]) dfs(i);
		}
		for (int i = 1; i <= n; i++)
			if (lab[i] == lab[NON(i)]) return false;
		return true;
	}
	
	vector <int> get_equation() {
		if (!check_exist()) return {-1};
		vector <int> ans = {0};
		for (int i = 1; i <= n; i++) ans.emplace_back(lab[i] < lab[NON(i)]);
		return ans;
	}
};
