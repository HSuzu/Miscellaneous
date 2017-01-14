/* Simple list
 */
#ifndef SLIST_H
#define SLIST_H

typedef struct _snode {
  struct _snode *next;
  void *elem;
} snode;

typedef struct _slist {
  snode *head;
  snode *tail;
  void (*destroyelem)(void *elem);
} slist;

#endif
