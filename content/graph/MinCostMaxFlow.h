/**
 * Author: Thieu Nguyen Huy
 * Description: Edmond-Karp algorithm with SPFA to find the shortest path
 * Usage: Call myflow.resize(num_vertices, source, sink) to initalize the network.
 * Time: O(F * V * E) in worst cases
 * Status: Well-tested
 */
 
struct MCMF {
    struct FlowEdge {
        int u, v;
        ll capacity, cost, flow = 0;
     
        FlowEdge(int _u = 0, int _v = 0, ll _capacity = 0, ll _cost = 0) {
            u = _u, v = _v, capacity = _capacity, cost = _cost, flow = 0;
        }
    };

    const ll FLOW_INF = (ll)2e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr;
    int n, m;
    int source, sink;
 
    MCMF(int _n = 0, int _s = 0, int _t = 0) {
        resize(_n, _s, _t);
    }
 
    void resize(int _n, int _s, int _t) {
        n = _n, m = 0, source = _s, sink = _t;
        adj.assign(n + 1, vector<int>()), level.assign(n + 1, -1);
        ptr.assign(n + 1, 0); edges.clear();
    }

    void reset_flow() {
        for (auto &edge : edges) edge.flow = 0;
    }
 
    void add(int u, int v, ll capacity, ll cost) {
        edges.emplace_back(u, v, capacity, cost);
        edges.emplace_back(v, u, 0, -cost);
        adj[u].emplace_back(m++), adj[v].emplace_back(m++);
    }
 
    bool bfs() {
        fill(level.begin(), level.end(), -1); level[source] = 0;
        queue<int> q; q.emplace(source);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto id : adj[u]) {
                if (edges[id].capacity - edges[id].flow <= 0) continue;
                if (level[edges[id].v] != -1) continue;
                level[edges[id].v] = level[u] + 1;
                q.emplace(edges[id].v);
            }
        }
        return level[sink] != -1;
    }
 
    ll dfs(int u, ll pushed) {
        if (pushed == 0) return 0;
        if (u == sink) return pushed;
        for (int &cid = ptr[u]; cid < (int)adj[u].size(); ++cid) {
            int id = adj[u][cid], v = edges[id].v;
            if (level[u] + 1 != level[v] || edges[id].capacity - edges[id].flow <= 0) continue;
            ll amount = dfs(v, min(pushed, edges[id].capacity - edges[id].flow));
            if (amount == 0) continue;
            edges[id].flow += amount, edges[id ^ 1].flow -= amount;
            return amount;
        }
        return 0;
    }
 
    ll maxFlow() {
        ll flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(source, FLOW_INF)) flow += pushed;
        }
        return flow;
    }

    bool spfa(vector<ll> &dist, vector<int> &par) {
        dist.assign(n + 1, INF), par.assign(n + 1, -1);
        vector<bool> inQueue(n + 1, false); queue<int> q;
        dist[source] = 0; inQueue[source] = true; q.emplace(source);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inQueue[u] = false;
            for (auto id : adj[u]) {
                int v = edges[id].v;
                if (edges[id].capacity - edges[id].flow <= 0) continue;
                if (minimize(dist[v], dist[u] + edges[id].cost)) {
                    par[v] = id;
                    if (!inQueue[v]) {
                        inQueue[v] = true;
                        q.emplace(v);
                    }
                }
            }
        }
        return dist[sink] != INF;
    }

    ll minCost() {
        ll flow = 0, cost = 0; vector<ll> dist; vector<int> par;
        while (spfa(dist, par)) {
            ll amount = FLOW_INF - flow; int cur = sink;
            while (cur != source) {
                minimize(amount, edges[par[cur]].capacity - edges[par[cur]].flow);
                cur = edges[par[cur]].u;
            }

            flow += amount, cost += amount * dist[sink], cur = sink;
            while (cur != source) {
                edges[par[cur]].flow += amount;
                edges[par[cur] ^ 1].flow -= amount;
                cur = edges[par[cur]].u;
            }
        }

        return cost;
    }
} myflow;