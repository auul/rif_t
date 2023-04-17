#include "rif.c"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRIAL_COUNT 100000000

char chbuf[128];

char *r_str(rif_t r)
{
	sprintf(chbuf, "%i/%i", r.num, r.denom);
	return chbuf;
}

#define test_unary(func, macro, f_func, f_macro)               \
	srand(seed);                                           \
	r.num   = (rand() % 100) + 1;                          \
	r.denom = (rand() % 100) + 1;                          \
	f       = (float)r.num / (float)r.denom;               \
	printf("Ratio: %s %f\n", r_str(r), f);                 \
	printf(#func ": %s\n", r_str(func(r)));                \
	printf(#macro ": %s\n", r_str(macro(r)));              \
	printf(#f_func ": %f\n", f_func(f));                   \
	printf(#f_macro ": %f\n", f_macro(f));                 \
	printf("\n");                                          \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	f        = 0.0;                                        \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		r.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			r.num = -r.num;                        \
		}                                              \
		r.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			r.denom = -r.denom;                    \
		}                                              \
		f        = (float)r.num / (float)r.denom;      \
		r        = func(r);                            \
		checksum = (checksum + (r.num / r.denom)) % 2; \
	}                                                      \
	end = clock();                                         \
	printf("%i " #func ": %fs\n",                          \
	       checksum + (int)floor(f / 10000.0),             \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	func_s += (double)(end - start) / CLOCKS_PER_SEC;      \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	f        = 0.0;                                        \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		r.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			r.num = -r.num;                        \
		}                                              \
		r.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			r.denom = -r.denom;                    \
		}                                              \
		f        = (float)r.num / (float)r.denom;      \
		r        = macro(r);                           \
		checksum = (checksum + (r.num / r.denom)) % 2; \
	}                                                      \
	end = clock();                                         \
	printf("%i " #macro ": %fs\n",                         \
	       checksum + (int)floor(f / 10000.0),             \
	       f,                                              \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	macro_s += (double)(end - start) / CLOCKS_PER_SEC;     \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		r.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			r.num = -r.num;                        \
		}                                              \
		r.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			r.denom = -r.denom;                    \
		}                                              \
		f        = (float)r.num / (float)r.denom;      \
		f        = f_func(f);                          \
		checksum = (checksum + (int)floor(f)) % 2;     \
	}                                                      \
	end = clock();                                         \
	printf("%i " #f_func ": %fs\n",                        \
	       checksum,                                       \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	f_func_s += (double)(end - start) / CLOCKS_PER_SEC;    \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		r.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			r.num = -r.num;                        \
		}                                              \
		r.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			r.denom = -r.denom;                    \
		}                                              \
		f        = (float)r.num / (float)r.denom;      \
		f        = f_macro(f);                         \
		checksum = (checksum + (int)floor(f)) % 2;     \
	}                                                      \
	end = clock();                                         \
	printf("%i " #f_macro ": %fs\n",                       \
	       checksum,                                       \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	f_macro_s += (double)(end - start) / CLOCKS_PER_SEC;   \
                                                               \
	printf("\n\n");

#define test_binary(func, macro, f_func, f_macro)              \
	srand(seed);                                           \
	a.num   = (rand() % 100) + 1;                          \
	a.denom = (rand() % 100) + 1;                          \
	b.num   = (rand() % 100) + 1;                          \
	b.denom = (rand() % 100) + 1;                          \
	f       = (float)a.num / (float)a.denom;               \
	g       = (float)b.num / (float)b.denom;               \
	printf("Ratio: %s ", r_str(a));                        \
	printf("%s %f %f\n",                                   \
	       r_str(b),                                       \
	       (float)a.num / (float)a.denom,                  \
	       (float)b.num / (float)b.denom);                 \
	printf(#func ": %s\n", r_str(func(a, b)));             \
	printf(#macro ": %s\n", r_str(macro(a, b)));           \
	printf(#f_func ": %f\n", f_func(f, g));                \
	printf(#f_macro ": %f\n", f_macro(f, g));              \
	printf("\n");                                          \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		a.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			a.num = -a.num;                        \
		}                                              \
		a.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			a.denom = -a.denom;                    \
		}                                              \
		b.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			b.num = -b.num;                        \
		}                                              \
		b.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			b.denom = -b.denom;                    \
		}                                              \
		f        = (float)a.num / (float)a.denom;      \
		g        = (float)b.num / (float)b.denom;      \
		r        = func(a, b);                         \
		checksum = (checksum + (r.num / r.denom)) % 2; \
	}                                                      \
	end = clock();                                         \
	printf("%i " #func ": %f\n",                           \
	       checksum + (int)floor((f + g) / 10000),         \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	func_s += (double)(end - start) / CLOCKS_PER_SEC;      \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		a.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			a.num = -a.num;                        \
		}                                              \
		a.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			a.denom = -a.denom;                    \
		}                                              \
		b.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			b.num = -b.num;                        \
		}                                              \
		b.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			b.denom = -b.denom;                    \
		}                                              \
		f        = (float)a.num / (float)a.denom;      \
		g        = (float)b.num / (float)b.denom;      \
		r        = macro(a, b);                        \
		checksum = (checksum + (r.num / r.denom)) % 2; \
	}                                                      \
	end = clock();                                         \
	printf("%i " #macro ": %f\n",                          \
	       checksum + (int)floor((f + g) / 10000),         \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	macro_s += (double)(end - start) / CLOCKS_PER_SEC;     \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		a.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			a.num = -a.num;                        \
		}                                              \
		a.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			a.denom = -a.denom;                    \
		}                                              \
		b.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			b.num = -b.num;                        \
		}                                              \
		b.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			b.denom = -b.denom;                    \
		}                                              \
		f        = (float)a.num / (float)a.denom;      \
		g        = (float)b.num / (float)b.denom;      \
		f        = f_func(f, g);                       \
		checksum = (checksum + (int)floor(f)) % 2;     \
	}                                                      \
	end = clock();                                         \
	printf("%i " #f_func ": %f\n",                         \
	       checksum,                                       \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	f_func_s += (double)(end - start) / CLOCKS_PER_SEC;    \
                                                               \
	srand(seed);                                           \
	checksum = 0;                                          \
	start    = clock();                                    \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {           \
		a.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			a.num = -a.num;                        \
		}                                              \
		a.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			a.denom = -a.denom;                    \
		}                                              \
		b.num = (rand() % 1000) + 1;                   \
		if (rand() % 2) {                              \
			b.num = -b.num;                        \
		}                                              \
		b.denom = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                              \
			b.denom = -b.denom;                    \
		}                                              \
		f        = (float)a.num / (float)a.denom;      \
		g        = (float)b.num / (float)b.denom;      \
		f        = f_macro(f, g);                      \
		checksum = (checksum + (int)floor(f)) % 2;     \
	}                                                      \
	end = clock();                                         \
	printf("%i " #f_macro ": %f\n",                        \
	       checksum,                                       \
	       (double)(end - start) / CLOCKS_PER_SEC);        \
	f_macro_s += (double)(end - start) / CLOCKS_PER_SEC;   \
                                                               \
	printf("\n\n");

#define test_trunc_unary(func, macro, f_func, f_macro)       \
	srand(seed);                                         \
	r.num   = (rand() % 100) + 1;                        \
	r.denom = (rand() % 100) + 1;                        \
	f       = (float)r.num / (float)r.denom;             \
	printf("Ratio: %s %f\n", r_str(r), f);               \
	printf(#func ": %i\n", func(r));                     \
	printf(#macro ": %i\n", macro(r));                   \
	printf(#f_func ": %i\n", f_func(f));                 \
	printf(#f_macro ": %i\n", f_macro(f));               \
	printf("\n");                                        \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	f        = 0.0;                                      \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		r.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			r.num = -r.num;                      \
		}                                            \
		r.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			r.denom = -r.denom;                  \
		}                                            \
		f        = (float)r.num / (float)r.denom;    \
		n        = func(r);                          \
		checksum = (checksum + n) % 2;               \
	}                                                    \
	end = clock();                                       \
	printf("%i " #func ": %fs\n",                        \
	       checksum + (int)floor(f / 10000.0),           \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	func_s += (double)(end - start) / CLOCKS_PER_SEC;    \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	f        = 0.0;                                      \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		r.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			r.num = -r.num;                      \
		}                                            \
		r.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			r.denom = -r.denom;                  \
		}                                            \
		f        = (float)r.num / (float)r.denom;    \
		n        = macro(r);                         \
		checksum = (checksum + n) % 2;               \
	}                                                    \
	end = clock();                                       \
	printf("%i " #macro ": %fs\n",                       \
	       checksum + (int)floor(f / 10000.0),           \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	macro_s += (double)(end - start) / CLOCKS_PER_SEC;   \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		r.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			r.num = -r.num;                      \
		}                                            \
		r.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			r.denom = -r.denom;                  \
		}                                            \
		f        = (float)r.num / (float)r.denom;    \
		n        = f_func(f);                        \
		checksum = (checksum + n) % 2;               \
	}                                                    \
	end = clock();                                       \
	printf("%i " #f_func ": %fs\n",                      \
	       checksum,                                     \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	f_func_s += (double)(end - start) / CLOCKS_PER_SEC;  \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		r.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			r.num = -r.num;                      \
		}                                            \
		r.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			r.denom = -r.denom;                  \
		}                                            \
		f        = (float)r.num / (float)r.denom;    \
		n        = f_macro(f);                       \
		checksum = (checksum + n) % 2;               \
	}                                                    \
	end = clock();                                       \
	printf("%i " #f_macro ": %fs\n",                     \
	       checksum,                                     \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	f_macro_s += (double)(end - start) / CLOCKS_PER_SEC; \
                                                             \
	printf("\n\n");

#define test_trunc_binary(func, macro, f_func, f_macro)      \
	srand(seed);                                         \
	a.num   = (rand() % 100) + 1;                        \
	a.denom = (rand() % 100) + 1;                        \
	b.num   = (rand() % 100) + 1;                        \
	b.denom = (rand() % 100) + 1;                        \
	f       = (float)a.num / (float)a.denom;             \
	g       = (float)b.num / (float)b.denom;             \
	printf("Ratio: %s ", r_str(a));                      \
	printf("%s %f %f\n",                                 \
	       r_str(b),                                     \
	       (float)a.num / (float)a.denom,                \
	       (float)b.num / (float)b.denom);               \
	printf(#func ": %i\n", func(a, b));                  \
	printf(#macro ": %i\n", macro(a, b));                \
	printf(#f_func ": %i\n", f_func(f, g));              \
	printf(#f_macro ": %i\n", f_macro(f, g));            \
	printf("\n");                                        \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		a.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			a.num = -a.num;                      \
		}                                            \
		a.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			a.denom = -a.denom;                  \
		}                                            \
		b.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			b.num = -b.num;                      \
		}                                            \
		b.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			b.denom = -b.denom;                  \
		}                                            \
		f = (float)a.num / (float)a.denom;           \
		g = (float)b.num / (float)b.denom;           \
		n = func(a, b);                              \
	}                                                    \
	end = clock();                                       \
	printf("%i " #func ": %f\n",                         \
	       checksum + (int)floor((f + g) / 10000),       \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	func_s += (double)(end - start) / CLOCKS_PER_SEC;    \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		a.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			a.num = -a.num;                      \
		}                                            \
		a.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			a.denom = -a.denom;                  \
		}                                            \
		b.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			b.num = -b.num;                      \
		}                                            \
		b.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			b.denom = -b.denom;                  \
		}                                            \
		f = (float)a.num / (float)a.denom;           \
		g = (float)b.num / (float)b.denom;           \
		n = macro(a, b);                             \
	}                                                    \
	end = clock();                                       \
	printf("%i " #macro ": %f\n",                        \
	       checksum + (int)floor((f + g) / 10000),       \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	macro_s += (double)(end - start) / CLOCKS_PER_SEC;   \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		a.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			a.num = -a.num;                      \
		}                                            \
		a.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			a.denom = -a.denom;                  \
		}                                            \
		b.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			b.num = -b.num;                      \
		}                                            \
		b.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			b.denom = -b.denom;                  \
		}                                            \
		f = (float)a.num / (float)a.denom;           \
		g = (float)b.num / (float)b.denom;           \
		n = f_func(f, g);                            \
	}                                                    \
	end = clock();                                       \
	printf("%i " #f_func ": %f\n",                       \
	       checksum,                                     \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	f_func_s += (double)(end - start) / CLOCKS_PER_SEC;  \
                                                             \
	srand(seed);                                         \
	checksum = 0;                                        \
	start    = clock();                                  \
	for (unsigned i = 0; i < TRIAL_COUNT; i++) {         \
		a.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			a.num = -a.num;                      \
		}                                            \
		a.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			a.denom = -a.denom;                  \
		}                                            \
		b.num = (rand() % 1000) + 1;                 \
		if (rand() % 2) {                            \
			b.num = -b.num;                      \
		}                                            \
		b.denom = (rand() % 1000) + 1;               \
		if (rand() % 2) {                            \
			b.denom = -b.denom;                  \
		}                                            \
		f = (float)a.num / (float)a.denom;           \
		g = (float)b.num / (float)b.denom;           \
		n = f_macro(f, g);                           \
	}                                                    \
	end = clock();                                       \
	printf("%i " #f_macro ": %f\n",                      \
	       checksum,                                     \
	       (double)(end - start) / CLOCKS_PER_SEC);      \
	f_macro_s += (double)(end - start) / CLOCKS_PER_SEC; \
                                                             \
	printf("\n\n");

int main(int argc, char **args)
{
	unsigned checksum, seed = time(NULL);
	clock_t start, end;
	rif_t a, b, r;
	float f, g;
	int n;
	double func_s    = 0.0;
	double macro_s   = 0.0;
	double f_func_s  = 0.0;
	double f_macro_s = 0.0;

	test_unary(r_invert, R_INVERT, f_invert, F_INVERT);
	test_trunc_unary(
	    r_trunc_invert, R_TRUNC_INVERT, f_trunc_invert, F_TRUNC_INVERT);
	test_unary(r_negate, R_NEGATE, f_negate, F_NEGATE);
	test_trunc_unary(
	    r_trunc_negate, R_TRUNC_NEGATE, f_trunc_negate, F_TRUNC_NEGATE);
	test_unary(r_floor, R_FLOOR, f_floor, F_FLOOR);
	test_trunc_unary(
	    r_trunc_floor, R_TRUNC_FLOOR, f_trunc_floor, F_TRUNC_FLOOR);
	test_unary(r_ceil, R_CEIL, f_ceil, F_CEIL);
	test_trunc_unary(
	    r_trunc_ceil, R_TRUNC_CEIL, f_trunc_ceil, F_TRUNC_CEIL);

	printf("Total time taken\n");
	printf("Func: %f\n", func_s);
	printf("Macro: %f\n", macro_s);
	printf("Float Func: %f\n", f_func_s);
	printf("Float Macro: %f\n", f_macro_s);

	return 0;
}
