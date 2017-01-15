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

void slistinit(slist *l, void (*destroyelem)(void *));
void slistiterator(slist *l, int (*itfunc)(void *, unsigned long int));
void slistclean(slist *l);
int slistempty(slist *l);
int slistrmhead(slist *l);
int slistrm(slist *l, unsigned long int pos);
int slistpushhead(slist *l, void *elem);
int slistpush(slist *l, void *elem, unsigned long int pos);
void *slisthead(slist *l);
void *slisttail(slist *l);
void *slistelem(slist *l, unsigned long int pos);
void *slistpophead(slist *l);
void *slistpop(slist *l, unsigned long int n);

#endif
