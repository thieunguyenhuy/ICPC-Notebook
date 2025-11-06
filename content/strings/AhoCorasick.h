/**
 * Author: Thieu Nguyen Huy
 * Description: Aho-corasick.
 * Usage: Call init() before any operations.
 * Time: O(len(s)) for addition, O(total_len) for build(), O(len(x)) or O(num of occurences) for query()
 * Status: Tested on some problems
 */

struct AhoCorasick {
    static const int SIZE = 26;
    static const char START_CHAR = 'a';

    struct Node {
        int fail, link;
        int child[SIZE], nxt[SIZE];
        int output;

        Node() {
            fail = 0, link = -1, output = 0;
            memset(child, -1, sizeof child);
            memset(nxt, -1, sizeof nxt);
        }
    };

    vector<Node> nodes;

    void init() {
        nodes.clear(), nodes.emplace_back(Node());
    }

    void add(string &s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - START_CHAR;
            if (nodes[v].child[c] == -1) {
                nodes[v].child[c] = nodes.size();
                nodes.emplace_back(Node());
            }
            v = nodes[v].child[c];
        }
        ++nodes[v].output;
    }

    void build() {
        nodes[0].fail = nodes[0].link = 0;
        for (int i = 0; i < SIZE; ++i)
            nodes[0].nxt[i] = (nodes[0].child[i] == -1 ? 0 : nodes[0].child[i]);
    
        queue<int> q; q.emplace(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
 
            for (int c = 0; c < SIZE; ++c) if (nodes[u].child[c] != -1) {
                int v = nodes[u].child[c];
                nodes[v].fail = (u == 0 ? 0 : nodes[nodes[u].fail].nxt[c]);
                for (int d = 0; d < SIZE; ++d)
                    nodes[v].nxt[d] = (nodes[v].child[d] == -1 ? nodes[nodes[v].fail].nxt[d] : nodes[v].child[d]);
                if (nodes[nodes[v].fail].output != 0) nodes[v].link = nodes[v].fail;
                else nodes[v].link = nodes[nodes[v].fail].link;
                q.emplace(v);
            }
        }
    }

    int query(string &x) {
        int ans = 0, p = 0;
        for (auto ch : x) {
            int c = ch - 'a', nxt = nodes[p].nxt[c];
            for (int u = nxt; u != 0; u = nodes[u].link) {
                ans += nodes[u].output;
            }
            p = nxt;
        }
        return ans;
    }
} aho;