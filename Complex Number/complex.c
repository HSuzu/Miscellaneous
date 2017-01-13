#include <math.h>
#include "complex.h"

void complexinit(complex * const z) {
  z->re = 0;
  z->im = 0;
}

void complexsum(complex * const z1,
                complex * const z2,
                complex * const result) {
  result->re = z1->re + z2->re;
  result->im = z1->im + z2->im;
}

void complexsub(complex * const z1,
                complex * const z2,
                complex * const result) {
  result->re = z1->re - z2->re;
  result->im = z1->im - z2->im;
}

void complexmult(complex * const z1,
                 complex * const z2,
                 complex * const result) {
  if(result == z1 || result == z2) {
    complex z;
    z.re = z1->re*z2->re - z1->im*z2->im;
    z.im = z1->re*z2->im + z1->im*z2->re;
    result->re = z.re;
    result->im = z.im;
  } else {
    result->re = z1->re*z2->re - z1->im*z2->im;
    result->im = z1->re*z2->im + z1->im*z2->re;
  }
}

void complexconj(complex * const z) {
  z->im = -z->im;
}

void complexinv(complex * const z) {
  if(z->re == 0 && z->im == 0)
    return;

  double n = pow(z->re,2) + pow(z->im, 2);
  complexconj(z);
  z->re /= n;
  z->im /= n;
}

void complexdiv(complex * const z1,
                complex * const z2,
                complex * const result) {
  if(z2->re == 0 && z2->im == 0)
    return;

  double n = pow(z2->re,2) + pow(z2->im, 2);

  if(result == z1 || result == z2) {
    complex z;
    z.re = z1->re*z2->re + z1->im*z2->im;
    z.im = z1->im*z2->re - z1->re*z2->im;
    result->re = z.re / n;
    result->im = z.im / n;
  } else {
    result->re = (z1->re*z2->re + z1->im*z2->im) / n;
    result->im = (z1->im*z2->re - z1->re*z2->im) / n;
  }
}

__inline__ double complexlen(complex * const z) {
  return sqrt(pow(z->re,2) + pow(z->im, 2));
}

double complexarg(complex * const z) {
  if(z->re == 0 && z->im == 0)
    return 0;

  double len = complexlen(z);
  double theta = acos(z->re/len);
  if(z->im < 0)
    theta = 2*M_PI - theta;

  return theta;
}
