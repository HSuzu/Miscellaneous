#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

typedef struct _complex {
  double re, im;
} complex;

void complexinit(complex * const z);
void complexsum(complex * const z1,
                complex * const z2,
                complex * const result);
void complexsub(complex * const z1,
                complex * const z2,
                complex * const result);
void complexmult(complex * const z1,
                 complex * const z2,
                 complex * const result);
void complexconj(complex * const z);
void complexinv(complex * const z);
void complexdiv(complex * const z1,
                complex * const z2,
                complex * const result);
__inline__ double complexlen(complex * const z);
double complexarg(complex * const z);

#endif
