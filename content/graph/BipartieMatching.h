/**
 * Author: KickingKun
 * Description: use for max matching
 * Time: O(E * sqrt(V))
 * Status: approved by KickingKun
*/

struct bipartite_matching {
	const int n, m;
	vector <int> match1, match2, que, dist;
	vector <vector<int>> adj;

	bipartite_matching(int _n, int _m) : n(_n), m(_m) {
		match1.assign(n + 1, -1); match2.assign(m + 1, -1);
		que.assign(n + 1, 0); dist.assign(n + 1, 0); adj.assign(n + 1, vector <int>());
	}

	void add(int u, int v) {
		adj[u].emb(v);
	}

	bool bfs() {
		fill(dist.begin(), dist.end(), -1);
		int queBegin = 1, queEnd = 1;
		for (int u = 1; u <= n; ++u) {
			if (match1[u] == -1) dist[u] = 0, que[queEnd++] = u;
		}
		bool success = false;
		while (queBegin < queEnd) {
			int u = que[queBegin++];
			for (int v : adj[u]) {
				if (match2[v] == -1) {
					success = true;
				}
				else if (dist[match2[v]] == -1) {
					dist[match2[v]] = dist[u] + 1;
					que[queEnd++] = match2[v];
				}
			}
		}
		return success;
	}

	bool dfs(int u) {
		for (int v : adj[u]) {
			if (match2[v] == -1 || (dist[match2[v]] == dist[u] + 1 && dfs(match2[v]))) {
				match1[u] = v; match2[v] = u; dist[u] = n + m;
				return true;
			}
		}
		dist[u] = n + m;
		return false;
	}
	
	int max_matching() {
		while (bfs()) {
			for (int u = 1; u <= n; ++u) {
				if (match1[u] == -1) dfs(u);
			}
		}
		return n - count(match1.begin() + 1, match1.end(), -1);
	}
	
	pair <vector <int>, vector <int>> minimum_vertex_cover() {
    	vector <int> L, R;
    	for (int u = 1; u <= n; ++u) {
    		if (dist[u] == -1) L.emb(u);
    		else if (match1[u] != -1) R.emb(match1[u]);
    	}
		return {L, R};
	}
    
    pair <vector <int>, vector <int>> maximum_independent_set() {
		auto [_L, _R] = minimum_vertex_cover();
		vector <int> L, R;
		vector <bool> mark1(n + 2), mark2(m + 2);
		for (int x: _L) mark1[x] = true; for (int x: _R) mark2[x] = true;
		for (int u = 1; u <= n; u++) if (!mark1[u]) L.emb(u);
		for (int u = 1; u <= m; u++) if (!mark2[u]) R.emb(u);
		return {L, R};
	}

	vector <pii> get_edges() { // get from max matching
    	vector <pii> ans;
    	for (int u = 1; u <= n; ++u)
        	if (match1[u] != -1) ans.emplace_back(u, match1[u]);
    	return ans;
	}
};
