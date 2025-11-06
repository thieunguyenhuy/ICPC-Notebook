/**
 * Author: Thieu Nguyen Huy
 * Description: Primality check for numbers up to $7 \cdot 10^{18}$, extend bases for larger number
 * Time: O(7 * logN)
 * Status: Tested on judge.yosupo.jp
 */

namespace MillerRabin {
    using T = unsigned long long;

    T binpow(T x, T y, T mod) {
        T ans = 1; x %= mod;
        while (y > 0) {
            if (y & 1) ans = (Int)ans * x % mod;
            x = (Int)x * x % mod, y >>= 1;
        }
        return ans;
    }

    bool notPrime(T n, T base, T d, int s) {
        if (base % n == 0) return false;
        T x = binpow(base % n, d, n);
        if (x == 1 || x == n - 1) return false;
        for (int r = 1; r < s; ++r) {
            x = (Int)x * x % n;
            if (x == n - 1) return false;
        }
        return true;
    }

    bool isPrime(T n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        int s = CTZ(n - 1); T d = n >> s;

        const T bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

        for (T base : bases) {
            if (notPrime(n, base, d, s)) return false;
        }
        return true;
    }
}
