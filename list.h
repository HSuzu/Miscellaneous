#ifndef LIST_H
#define LIST_H

#include "common_header.h"

typedef listposition        quint16_t;
typedef listdestroyfunction void;

typedef struct _node {
  void *elem;
  struct _node *next;
#ifdef LIST_DOUBLE
  struct _node *prev;
#endif
} listnode;

typedef struct _list {
  listposition size;
  listdestroyfunction (*destroyelem)(void *);
  listnode first;
#ifdef LIST_TAIL
  listnode tail;
#endif
} list;

#endif
