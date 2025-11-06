/**
 * Author: Thieu Nguyen Huy
 * Description: Gauss elimation to solve system of linear equations
 * Usage: variables are numbered 0 -> m-1, the m-th column is the right hand side
 * Time: O(min(N, M) \cdot N \cdot M) where N = equations, M = variables
 * Status: Tested on VNOI
 */

int gauss(vector<vector<double>> &a, vector<double> &ans) {
    const double EPS = 1e-9;
    int n = a.size(), m = a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int p = row;
        for (int i = row; i < n; ++i) 
            if (abs(a[i][col]) > abs(a[p][col])) p = i;

        if (abs(a[p][col]) < EPS) continue;

        swap(a[row], a[p]);
        where[col] = row;

        for (int i = 0; i < n; ++i) if (i != row) {
            double c = a[i][col] / a[row][col];
            for (int j = col; j <= m; ++j)
                a[i][j] -= a[row][j] * c;
        }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) if (where[i] != -1) {
        ans[i] = a[where[i]][m] / a[where[i]][i];
    }

    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS) return 0;
    }

    for (int i = 0; i < m; ++i) 
        if (where[i] == -1) return 2;
    return 1;
}