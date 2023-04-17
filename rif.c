#ifndef RIF_H
#define RIF_H

#include <math.h>

typedef struct rif {
	int num;
	int denom;
} rif_t;

#define R_INVERT(r) ((rif_t){r.denom, r.num})
rif_t r_invert(rif_t r)
{
	return ((rif_t){r.denom, r.num});
}
#define F_INVERT(f) (1.0 / f)
float f_invert(float f)
{
	return 1.0 / f;
}

#define R_TRUNC_INVERT(r) (r.denom / r.num)
int r_trunc_invert(rif_t r)
{
	return r.denom / r.num;
}
#define F_TRUNC_INVERT(f) (int)floor(1.0 / f)
int f_trunc_invert(float f)
{
	return (int)floor(1.0 / f);
}

#define R_NEGATE(r) ((rif_t){-r.num, r.denom})
rif_t r_negate(rif_t r)
{
	r.num = -r.num;
	return r;
}
#define F_NEGATE(f) (-f)
float f_negate(float f)
{
	return -f;
}

#define R_TRUNC_NEGATE(r) (-r.num / r.denom)
int r_trunc_negate(rif_t r)
{
	return -r.num / r.denom;
}
#define F_TRUNC_NEGATE(f) (int)floor(-f)
int f_trunc_negate(float f)
{
	return (int)floor(-f);
}

#define R_FLOOR(r)                                                           \
	(r.num < 0                                                           \
	     ? (r.denom < 0 ? ((rif_t){r.num / r.denom, 1})                  \
	                    : ((rif_t){(r.num + r.denom - 1) / r.denom, 1})) \
	     : (r.denom < 0 ? ((rif_t){(r.num + r.denom - 1) / r.denom, 1})  \
	                    : ((rif_t){r.num / r.denom, 1})))
rif_t r_floor(rif_t r)
{
	if (r.num < 0) {
		if (r.denom < 0) {
			r.num /= r.denom;
		} else {
			r.num = (r.num + r.denom - 1) / r.denom;
		}
	} else if (r.denom < 0) {
		r.num = (r.num + r.denom - 1) / r.denom;
	} else {
		r.num /= r.denom;
	}
	r.denom = 1;

	return r;
}
#define F_FLOOR(f) floor(f)
float f_floor(float f)
{
	return floor(f);
}

#define R_TRUNC_FLOOR(r)                                             \
	(r.num < 0 ? (r.denom < 0 ? r.num / r.denom                  \
	                          : (r.num + r.denom - 1) / r.denom) \
	           : (r.denom < 0 ? (r.num + r.denom - 1) / r.denom  \
	                          : r.num / r.denom))
int r_trunc_floor(rif_t r)
{
	if (r.num < 0) {
		if (r.denom < 0) {
			return r.num / r.denom;
		} else {
			return (r.num + r.denom - 1) / r.denom;
		}
	} else if (r.denom < 0) {
		return (r.num + r.denom - 1) / r.denom;
	} else {
		return r.num / r.denom;
	}
}
#define F_TRUNC_FLOOR(f) (int)floor(f)
int f_trunc_floor(float f)
{
	return (int)floor(f);
}

#define R_CEIL(r)                                                           \
	(r.num < 0                                                          \
	     ? (r.denom < 0 ? ((rif_t){(r.num + r.denom + 1) / r.denom, 1}) \
	                    : ((rif_t){r.num / r.denom, 1}))                \
	     : (r.denom < 0 ? ((rif_t){r.num / r.denom})                    \
	                    : ((rif_t){(r.num + r.denom - 1) / r.denom})))
rif_t r_ceil(rif_t r)
{
	if (r.num < 0) {
		if (r.denom < 0) {
			r.num = (r.num + r.denom + 1) / r.denom;
		} else {
			r.num /= r.denom;
		}
	} else if (r.denom < 0) {
		r.num /= r.denom;
	} else {
		r.num = (r.num + r.denom - 1) / r.denom;
	}
	r.denom = 1;
	return r;
}
#define F_CEIL(f) (int)ceil(f)
float f_ceil(float f)
{
	return (int)ceil(f);
}

#define R_TRUNC_CEIL(r)                                             \
	(r.num < 0 ? (r.denom < 0 ? (r.num + r.denom + 1) / r.denom \
	                          : r.num / r.denom)                \
	           : (r.denom < 0 ? r.num / r.denom                 \
	                          : (r.num + r.denom - 1) / r.denom))
int r_trunc_ceil(rif_t r)
{
	if (r.num < 0) {
		if (r.denom < 0) {
			return (r.num + r.denom + 1) / r.denom;
		} else {
			return r.num / r.denom;
		}
	} else if (r.denom < 0) {
		return r.num / r.denom;
	} else {
		return (r.num + r.denom - 1) / r.denom;
	}
}
#define F_TRUNC_CEIL(f) (int)ceil(f)
int f_trunc_ceil(float f)
{
	return (int)ceil(f);
}

#define R_ADD(a, b)                                                         \
	((rif_t){(long)a.num * (long)b.denom + (long)b.num * (long)a.denom, \
	         (long)a.denom * (long)b.denom})
rif_t r_add(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom + (long)b.num * (long)a.denom;
	long denom = (long)a.denom * (long)b.denom;

	return (rif_t){num, denom};
}
#define F_ADD(a, b) (a + b)
float f_add(float a, float b)
{
	return a + b;
}

#define R_TRUNC_ADD(a, b)                                              \
	(((long)a.num * (long)b.denom + (long)b.num * (long)a.denom) / \
	 ((long)a.denom * (long)b.denom))
int r_trunc_add(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom + (long)b.num * (long)a.denom;
	long denom = (long)a.denom * (long)b.denom;

	return num / denom;
}
#define F_TRUNC_ADD(a, b) (int)floor(a + b)
int f_trunc_add(float a, float b)
{
	return (int)floor(a + b);
}

#define R_SUBTRACT(a, b)                                                    \
	((rif_t){(long)a.num * (long)b.denom - (long)b.num * (long)a.denom, \
	         (long)a.denom * (long)b.denom})
rif_t r_subtract(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom - (long)b.num * (long)a.denom;
	long denom = (long)a.denom * (long)b.denom;

	return (rif_t){num, denom};
}
#define F_SUBTRACT(a, b) (a - b)
float f_subtract(float a, float b)
{
	return a - b;
}

#define R_TRUNC_SUBTRACT(a, b)                                         \
	(((long)a.num * (long)b.denom - (long)b.num * (long)a.denom) / \
	 ((long)a.denom * (long)b.denom))
int r_trunc_subtract(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom - (long)b.num * (long)a.denom;
	long denom = (long)a.denom * (long)b.denom;

	return num / denom;
}
#define F_TRUNC_SUBTRACT(a, b) (int)floor(a - b)
int f_trunc_subtract(float a, float b)
{
	return (int)floor(a - b);
}

#define R_MULTIPLY(a, b) \
	((rif_t){(long)a.num * (long)b.num, (long)a.denom * (long)b.denom})
rif_t r_multiply(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.num;
	long denom = (long)a.denom * (long)b.denom;

	return (rif_t){num, denom};
}
#define F_MULTIPLY(a, b) (a * b)
float f_multiply(float a, float b)
{
	return (a * b);
}

#define R_TRUNC_MULTIPLY(a, b) \
	(((long)a.num * (long)b.num) / ((long)a.denom * (long)b.denom))
int r_trunc_multiply(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.num;
	long denom = (long)a.denom * (long)b.denom;

	return num / denom;
}
#define F_TRUNC_MULTIPLY(a, b) (int)floor(a *b)
int f_trunc_multiply(float a, float b)
{
	return (int)floor(a * b);
}

#define R_DIVIDE(a, b) \
	((rif_t){(long)a.num * (long)b.denom, (long)a.denom * (long)b.num})
rif_t r_divide(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom;
	long denom = (long)a.denom * (long)b.num;

	return (rif_t){num, denom};
}
#define F_DIVIDE(a, b) (a / b)
float f_divide(float a, float b)
{
	return a / b;
}

#define R_TRUNC_DIVIDE(a, b) \
	(((long)a.num * (long)b.denom) / ((long)a.denom * (long)b.num))
int r_trunc_divide(rif_t a, rif_t b)
{
	long num   = (long)a.num * (long)b.denom;
	long denom = (long)a.denom * (long)b.num;

	return num / denom;
}
#define F_TRUNC_DIVIDE(a, b) (int)floor(a / b)
int f_trunc_divide(float a, float b)
{
	return (int)floor(a / b);
}

#endif
