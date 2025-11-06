/**
 * Author: KACTL
 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
 * Description: Compute $a \% b$ about 5 times faster than usual, where $b$ is constant but not known at compile time.
 * Returns a value congruent to $a \pmod b$ in the range $[0, 2b)$.
 * Status: proven correct, stress-tested
 */

struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) { // a % b + (0 or b)
		return a - (ull)((__uint128_t(m) * a) >> 64) * b;
	}
};
