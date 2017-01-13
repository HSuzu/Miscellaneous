#ifndef _VECTOR_H
#define _VECTOR_H
#define VECTOR_DEBUB_ERRMSG

typedef struct _vector {
  void *array;
  unsigned long int elemnum;
  unsigned long int elemblocks;
  unsigned int elemsize;
  unsigned long int arraysize;
  unsigned int increaseconst;
} vector;

void vctinit(vector * const v,
             const unsigned int elemsize);
void vctclean(vector * const v);
void vctsetincreaseconst(vector * const v,
                         const unsigned int n);
unsigned long int vctchangesize(vector * const v,
                                const unsigned long int n);
unsigned long int vctincreasesize(vector * const v,
                                  const unsigned int n);
unsigned long int vctdecreasesize(vector * const v,
                                  const unsigned int n);
unsigned long int vctrelativechangesize(vector * const v,
                                        const int n);

unsigned long int vctpush(vector * const v, void *elem, unsigned long int n);

unsigned int vctcopycontent(vector * const v,
                   void * const content,
                   unsigned int destpos,
                   unsigned int nelem);
int vctpop(vector * const v, void *dest, unsigned long int n);
#endif
