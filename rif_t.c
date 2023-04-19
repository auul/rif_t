#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int num;
	int denom;
} rif_t;

static inline int gcd(register int a, register int b)
{
	register int r, i;

	while (b) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

static inline rif_t r_simplify(rif_t r)
{
	register int g = gcd(r.num, r.denom);

	return (g > 0) ? ((rif_t){r.num / g, r.denom / g}) : r;
}

static inline rif_t r_add(rif_t a, rif_t b)
{
	return (rif_t){a.num * b.denom + b.num * a.denom, a.denom * b.denom};
}

static inline float f_add(rif_t a, rif_t b)
{
	return ((float)a.num / (float)b.denom) +
	       ((float)b.num / (float)b.denom);
}

#define TRIAL_COUNT 1000000000

int main(void)
{
	clock_t start, end;
	unsigned seed = time(NULL);
	int checksum;
	rif_t a, b, r;
	float f;

	srand(seed);
	checksum = 0;
	start    = clock();
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {
		a.num    = rand() % 10000;
		a.denom  = (rand() % 10000) + 1;
		b.num    = rand() % 10000;
		b.denom  = (rand() % 10000) + 1;
		r        = r_add(a, b);
		checksum = (checksum + (r.num / r.denom)) % 2;
	}
	end = clock();
	printf(
	    "%i r_add: %f\n", checksum, (double)(end - start) / CLOCKS_PER_SEC);

	srand(seed);
	checksum = 0;
	start    = clock();
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {
		a.num    = rand() % 10000;
		a.denom  = (rand() % 10000) + 1;
		b.num    = rand() % 10000;
		b.denom  = (rand() % 10000) + 1;
		f        = f_add(a, b);
		checksum = (checksum + (int)floor(f)) % 2;
	}
	end = clock();
	printf(
	    "%i f_add: %f\n", checksum, (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}
