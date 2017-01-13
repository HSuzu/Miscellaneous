#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "vector.h"

void vctinit(vector * const v,
             const unsigned int elemsize) {
  v->array         = NULL;
  v->elemnum       = 0;
  v->elemblocks    = 0;
  v->elemsize      = elemsize;
  v->arraysize     = 0;
  v->increaseconst = 1;
}

void vctclean(vector * const v) {
  free(v->array);
  v->array      = NULL;
  v->elemnum    = 0;
  v->elemblocks = 0;
  v->arraysize  = 0;
}

void vctsetincreaseconst(vector * const v,
                         const unsigned int n) {
  v->increaseconst = n;
}

unsigned long int vctchangesize(vector * const v,
                                const unsigned long int n) {
  if(n == 0) {
    vctclean(v);
    return 0;
  }

  unsigned long int size = n*v->elemsize;
  void *array = realloc(v->array, size);
  if(array) {
    v->array      = array;
    if(v->elemnum > n)
      v->elemnum = n;
    v->elemblocks = n;
    v->arraysize  = size;
    return n;
  }

  return 0;
}

unsigned long int vctincreasesize(vector * const v,
                                  const unsigned int n) {
  unsigned long int newLen = v->elemblocks + n;
  if(newLen > v->elemblocks)
    return vctchangesize(v, newLen);
  return vctchangesize(v, LONG_MAX);
}

unsigned long int vctdecreasesize(vector * const v,
                                  const unsigned int n) {
  unsigned long int newLen = v->elemblocks - n;
  if(newLen < v->elemblocks)
    return vctchangesize(v, newLen);
  vctclean(v);
  return 0;
}

unsigned long int vctrelativechangesize(vector * const v,
                                        const int n) {
  if(n < 0) {
    return vctdecreasesize(v, (const unsigned int)-n);
  } else if(n > 0) {
    return vctincreasesize(v, (const unsigned int)n);
  }
  vctclean(v);
  return 0;
}

unsigned long int vctpush(vector * const v,
                          void *elem,
                          unsigned long int n) {
  unsigned long int size = 0;
  if(n >= v->elemblocks ) {
    if((size = vctchangesize(v, n+1)) == 0)
      return -1;
  }

  void *dest = v->array + n * v->elemsize;
  memcpy(dest, elem, v->elemsize);
//  *((int *)dest) = *((int *)elem);
  v->elemnum += 1;

  return size;
}

unsigned int vctcopycontent(vector * const v,
                   void * const content,
                   unsigned int destpos,
                   unsigned int nelem) {
  unsigned long int size = nelem + destpos;
  if(destpos + nelem >= v->elemblocks) {
    if((size = vctchangesize(v, destpos + nelem)) == 0 )
      return -1;
  }

  size -= destpos;

  void *dest = v->array + destpos * v->elemsize;
  memcpy(dest, content, size * v->elemsize);
  v->elemnum += size;

  return size;
}

int vctpop(vector * const v, void *dest, unsigned long int n) {
  if(n >= v->elemblocks)
    return -1;

  void *src = v->array + n * v->elemsize;
  memcpy(dest, src, v->elemsize);
//  *((int *)dest) = *((int *)src);
  return 0;
}
