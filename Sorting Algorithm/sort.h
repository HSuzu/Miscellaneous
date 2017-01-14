#ifndef SORT_H
#define SORT_H
typedef struct _operations {
  int (*compare)(void *, void *);
  void (*cpy)(void *, void *);
  void (*switch)(void *, void *);
  void (*next)(void *);
} operations;
#endif
