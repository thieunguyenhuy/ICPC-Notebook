/**
 * Author: Thieu Nguyen Huy
 * Description: Gauss elimation to solve system of linear equations (mod 2)
 * Usage: all roots of the system have the form: ans + sum(c(i) * basis(i))
 * Time: O(min(N, M) * N * M / 64) where N = equations, M = variables
 * Status: Tested on judge.yosupo.jp
 */

namespace Gauss {
    // n: num equations, m: num variables
    // left hand side: 0 -> m-1, right hand side: column m
    const int M = 4096 + 5;
    using T = bitset<M>;

    int n, m;
    int where[M];
    vector<T> a;
    T ans;

    void init(int _n, int _m, const vector<T> &_a) {
        n = _n, m = _m, a = _a;
    }

    int gauss() {
        for (int i = 0; i < m; ++i) where[i] = -1;
        int row = 0;
        for (int col = 0; col < m && row < n; ++col) {
            for (int i = row; i < n; ++i) if (a[i][col]) {
                swap(a[i], a[row]);
                break;
            }
            if (!a[row][col]) continue;
            where[col] = row;
            for (int i = 0; i < n; ++i) 
                if (i != row && a[i][col]) a[i] ^= a[row];
            ++row;
        }

        for (int i = 0; i < m; ++i) if (where[i] != -1) {
            ans[i] = a[where[i]][m];
        }

        for (int i = 0; i < n; ++i) {
            bool sum = 0;
            for (int j = 0; j < m; ++j) sum ^= ans[j] & a[i][j];
            if (sum != a[i][m]) return -1;
        }
        return row;
    }

    vector<T> get_basis() { // assume gauss() has been called
        vector<T> basis;
        for (int i = 0; i < m; ++i) if (where[i] == -1) {
            T x; x[i] = 1;
            // x(j) + a[where[j]][i] * x[i] = 0
            for (int j = 0; j < m; ++j) 
                if (where[j] != -1) x[j] = a[where[j]][i];
            basis.emplace_back(x);
        }
        return basis;
    }
}