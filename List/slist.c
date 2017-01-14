#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

void slistinit(slist *l, void (*destroyelem)(void *)) {
  l->head = NULL;
  l->tail = NULL;
  l->destroyelem = destroyelem;
}

void slistiterator(slist *l, void (*itfunc)(void *, unsigned long int)) {
  snode *node = l->head;
  unsigned long int i = 0ul;

  while(node) {
    itfunc(node->elem, i++);
    node = node->next;
  }
}

void slistclean(slist *l) {
  snode *prev = NULL;
  snode *node = l->head;
  while(node) {
    l->destroyelem(node->elem);
    prev = node;
    node = node->next;
    free(prev);
  }
}

__inline__ int slistempty(slist *l) {
  return (l->head)?0:1;
}

int slistrmhead(slist *l) {
  if(l->head) {
    snode *head = l->head;
    l->head = head->next;
    if(!head->next) // head->next == NULL
      l->tail = NULL;

    l->destroyelem(head->elem);
    free(head);

    return 0;
  }

  return -1;
}

int slistrm(slist *l, unsigned long int pos) {
  snode **node = &(l->head);
  while(*node && pos-- > 0) {
    node = &((*node)->next);
  }

  snode *rmnode = *node;
  if(rmnode) {
    *node = (*node)->next;
    l->destroyelem(rmnode->elem);
    free(rmnode);

    return 0;
  }

  return -1;
}
