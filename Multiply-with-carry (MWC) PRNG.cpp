// C99 Complementary Multiply With Carry generator
#include<bits/stdc++.h>
using namespace std;
#define LOG_1(n) (((n) >= 2) ? 1 : 0)
#define LOG_2(n) (((n) >= 1<<2) ? (2 + LOG_1((n)>>2)) : LOG_1(n))
#define LOG_4(n) (((n) >= 1<<4) ? (4 + LOG_2((n)>>4)) : LOG_2(n))
#define LOG_8(n) (((n) >= 1<<8) ? (8 + LOG_4((n)>>8)) : LOG_4(n))
#define LOG(n)   (((n) >= 1<<16) ? (16 + LOG_8((n)>>16)) : LOG_8(n))
#define BITS_TO_REPRESENT(n) (LOG(n) + !!((n) & ((n) - 1)))
#if ((RAND_MAX | (RAND_MAX >> 1)) != RAND_MAX)
#error "expected a RAND_MAX that is 2^n - 1!"
#endif
#define RAND_BITS BITS_TO_REPRESENT(RAND_MAX)

// CMWC working parts
#define CMWC_CYCLE 4096         // as Marsaglia recommends
#define CMWC_C_MAX 809430660    // as Marsaglia recommends
struct cmwc_state {
	uint32_t Q[CMWC_CYCLE];
	uint32_t c;	// must be limited with CMWC_C_MAX
	unsigned i;
};

// Collect 32 bits of rand().
uint32_t rand32(void)
{
	uint32_t result = rand();
	for (int bits = RAND_BITS; bits < 32; bits += RAND_BITS)
		result = result << RAND_BITS | rand();
	return result;
}

// Init the state with seed
void initCMWC(struct cmwc_state *state, unsigned int seed)
{
	srand(seed);
	for (int i = 0; i < CMWC_CYCLE; i++)
		state->Q[i] = rand32();
	do
		state->c = rand32();
	while (state->c >= CMWC_C_MAX);
	state->i = CMWC_CYCLE - 1;
}

// CMWC engine
uint32_t randCMWC(struct cmwc_state *state)  //EDITED parameter *state was missing
{
	uint64_t const a = 18782;	// as Marsaglia recommends
	uint32_t const m = 0xfffffffe;	// as Marsaglia recommends
	uint64_t t;
	uint32_t x;

	state->i = (state->i + 1) & (CMWC_CYCLE - 1);
	t = a * state->Q[state->i] + state->c;
	/* Let c = t / 0xffffffff, x = t mod 0xffffffff */
	state->c = t >> 32;
	x = t + state->c;
	if (x < state->c) {
		x++;
		state->c++;
	}
	return state->Q[state->i] = m - x;
}

int main()
{
	struct cmwc_state cmwc;
	unsigned int seed = time(NULL);

	initCMWC(&cmwc, seed);
	map<int, int>cnt;
	for (int i = 0; i < 10000; i++) {
		cnt[(randCMWC(&cmwc)) % 100]++;
	}
	for (int i = 0; i < 100; i++) {
		cout << cnt[i] << endl;
	}
}