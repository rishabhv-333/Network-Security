#include<bits/stdc++.h>
using namespace std;

struct xorshift32_state {
	uint32_t a;
};

/* The state word must be initialized to non-zero */
uint32_t xorshift32(struct xorshift32_state *state)
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	uint32_t x = state->a;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return state->a = x;
}

struct xorshift64_state {
	uint64_t a;
};

uint64_t xorshift64(struct xorshift64_state *state)
{
	uint64_t x = state->a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return state->a = x;
}
int main() {

	auto seed = new xorshift32_state();
	seed->a = time(NULL);
	map<int, int>cnt;
	for (int i = 0; i < 10000; i++) {
		cnt[(xorshift32(seed)) % 100]++;
	}
	for (int i = 0; i < 100; i++) {
		cout << cnt[i] << endl;
	}
	return 0;
}