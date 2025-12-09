/**
 * Author: Thieu Nguyen Huy
 * Description: Fast set
 * Time: O(log64(n)) for update and lowerbound, upperbound
 * Status: Well-tested
 */

namespace FastSet {
    const int N = 250000 + 5;
    const int BLOCK = 64;
    const int LAYER = 3;

    ull a[N + 5];
    int layer_start[LAYER];

    void init() {
        int start = 0, pos = 1;
        for(int i = 0; i < LAYER; ++i) {
            layer_start[i] = start;
            start += pos;
            pos = pos * BLOCK;
        }
    }

    void update(int x) {
        int id = x >> 6, prev = layer_start[LAYER - 1] + id;
        a[prev] ^= MASK(x & (BLOCK - 1));
        for (int i = LAYER - 2; i >= 0; --i) {
            x >>= 6, id >>= 6;
            int digit = x & (BLOCK - 1), cur = id + layer_start[i];
            if ((a[prev] > 0) != BIT(a[cur], digit)) a[cur] ^= MASK(digit);
            prev = cur;
        }
    }

    int get_next(ull mask, int l) {
        ull foo = -1; mask &= foo << l;
        if (l == BLOCK || mask == 0) return -1;
        return CTZ(mask);
    }

    int find_next(int x) { // return >= x
        int id = x >> 6;
        int foo = get_next(a[id + layer_start[LAYER - 1]], x & (BLOCK - 1));
        if (foo != -1) return x - (x & (BLOCK - 1)) + foo;
        x >>= 6, id >>= 6;
        for (int i = LAYER - 2; i>=0; --i) {
            int digit = (x & (BLOCK - 1)) + 1;
            int cur = layer_start[i] + id;
            int foo = get_next(a[cur], digit);
            if (foo != -1) {
                id = (id << 6) + foo;
                for (int j = i + 1; j < LAYER; ++j) {
                    int digit = CTZ(a[id + layer_start[j]]);
                    id = (id << 6) + digit;
                }
                return id;
            }
            x >>= 6, id >>= 6;
        }
        return -1;
    }

    int get_prev(ull mask, int l) {
        mask &= MASK(l) - 1;
        if (l == BLOCK || mask == 0) return -1;
        return LOG(mask);
    }

    int find_prev(int x) { // return < x
        int id = x >> 6;
        int foo = get_prev(a[id + layer_start[LAYER - 1]], x & (BLOCK - 1));
        if (foo != -1) return x - (x & (BLOCK - 1)) + foo;
        x >>= 6, id >>= 6;
        for(int i = LAYER - 2; i>=0; --i) {
            int digit = (x & (BLOCK - 1)) + 1;
            int cur = layer_start[i] + id;
            int foo = get_prev(a[cur], digit - 1);
            if (foo != -1) {
                id = (id << 6) + foo;
                for(int j = i + 1; j < LAYER; ++j) {
                    int digit = LOG(a[id + layer_start[j]]);
                    id = (id << 6) + digit;
                }
                return id;
            }
            x >>= 6, id >>= 6;
        }
        return -1;
    }

    int get_min() {
        return find_next(1);
    }

    int get_max() {
        return find_prev(N + 1);
    }
}