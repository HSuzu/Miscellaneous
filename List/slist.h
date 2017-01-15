/* Simple list
 */
#ifndef SLIST_H
#define SLIST_H

#define SLIST_TAIL(l) (l) ## .size - 1

typedef struct _snode {
  struct _snode *next;
  void *elem;
} snode;

typedef struct _slist {
  snode *head;
  snode *tail;
  unsigned long int size;
  void (*destroyelem)(void *elem);
} slist;

#endif
