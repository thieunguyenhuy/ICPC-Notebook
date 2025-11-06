/**
 * Author: Thieu Nguyen Huy
 * Description: Persistent segment tree with range updates and range sum queries.
 * Usage: Remember to call mytree.resize(n) before any operations.
 * Time: O(\log N) for each operation
 * Memory: O(4 \cdot \log N \cdot numUpdates) 
 * Status: Not tested
 */

struct Node {
    int le, ri;
    ll lazy, sum;

    Node(int _le = 0, int _ri = 0, ll _lazy = 0, ll _sum = 0) {
        le = _le, ri = _ri, lazy = _lazy, sum = _sum;
    }
} nodes[4 * N * LG];
int numNode = 0;
vector<int> version;

struct PersistentLazyIT {
    int n;

    PersistentLazyIT(int _n = 0) {
        resize(_n);
    }

    void resize(int _n) {
        n = _n;
    }

    int newlazykid(int oldId, int l, int r, ll val) {
        int id = ++numNode;
        nodes[id] = nodes[oldId];

        nodes[id].sum += 1ll * val * (r - l + 1);
        nodes[id].lazy += val;

        return id;
    }

    int newparent(int le, int ri) {
        int id = ++numNode;
        nodes[id].le = le, nodes[id].ri = ri;
        nodes[id].sum = nodes[le].sum + nodes[ri].sum;
        return id;
    }

    void push(int id, int l, int r) {
        if (nodes[id].lazy == 0) return;
        if (l != r) {
            int mid = (l + r) >> 1;
            nodes[id].le = newlazykid(nodes[id].le, l, mid, nodes[id].lazy);
            nodes[id].ri = newlazykid(nodes[id].ri, mid + 1, r, nodes[id].lazy);
        }
        nodes[id].lazy = 0;
    }

    int update(int oldId, int l, int r, int u, int v, ll val) {
        if (l > v || r < u) return oldId;
        if (u <= l && r <= v) return newlazykid(oldId, l, r, val);
        push(oldId, l, r); int mid = (l + r) >> 1;
        int le = update(nodes[oldId].le, l, mid, u, v, val),
            ri = update(nodes[oldId].ri, mid + 1, r, u, v, val);
        return newparent(le, ri);
    }

    int update(int root, int u, int v, int val) {
        return update(root, 1, n, u, v, val);
    }

    ll get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) return nodes[id].sum;
        push(id, l, r); int mid = (l + r) >> 1;
        return get(nodes[id].le, l, mid, u, v) + get(nodes[id].ri, mid + 1, r, u, v);
    }

    ll get(int root, int u, int v) {
        return get(root, 1, n, u, v);
    }
} mytree;
