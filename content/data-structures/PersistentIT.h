/**
 * Author: Thieu Nguyen Huy
 * Description: Persistent segment tree with point updates and range sum queries.
 * Usage: Remember to call mytree.resize(n) before any operations.
 *  Make sure to check for integer overflows in update values.
 * Time: O(logN) for each operation
 * Memory: O(logN * numUpdates) 
 * Status: Tested on CSES
 */

struct Node {
    int le, ri;
    ll sum;
 
    Node(int _le = 0, int _ri = 0, ll _sum = 0) {
        le = _le, ri = _ri, sum = _sum;
    }
} nodes[N * LG];
int numNode = 0;
vector<int> version;

struct PersistentIT { // 1-indexed
    int n;

    PersistentIT(int _n = 0) {
        resize(_n);
    }

    void resize(int _n) {
        n = _n;
    }

    int update(int oldId, int l, int r, int p, int val) {
        if (l > p || r < p) return oldId;
 
        int id = ++numNode;
        if (l == r) {
            nodes[id] = nodes[oldId];
            nodes[id].sum += val;
            return id;
        }
 
        int mid = (l + r) >> 1;
        nodes[id].le = update(nodes[oldId].le, l, mid, p, val);
        nodes[id].ri = update(nodes[oldId].ri, mid + 1, r, p, val);
 
        nodes[id].sum = nodes[nodes[id].le].sum + nodes[nodes[id].ri].sum;
        return id;
    }

    int update(int root, int p, int val) {
        return update(root, 1, n, p, val);
    }
 
    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) return nodes[id].sum;
        int mid = (l + r) >> 1;
        return get(nodes[id].le, l, mid, u, v) + get(nodes[id].ri, mid + 1, r, u, v);
    }

    ll get(int root, int u, int v) {
        return get(root, 1, n, u, v);
    }
} mytree;