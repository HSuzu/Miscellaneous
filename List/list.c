#include "list.h"

char *listerr_func(list_err err) {
  switch(err & LIST_ERR_FUNCTION) {
    case LIST_ERR_FUNCTION_BEGIN:
      return "listbegin";
    case LIST_ERR_FUNCTION_INSERT:
      return "listinsert";
    case LIST_ERR_FUNCTION_INSERT_H:
      return "listinserthead";
    case LIST_ERR_FUNCTION_INSERT_T:
      return "listinserttail";
    case LIST_ERR_FUNCTION_REMOVE:
      return "listremove";
    case LIST_ERR_FUNCTION_REMOVE_H:
      return "listremovehead";
    case LIST_ERR_FUNCTION_REMOVE_T:
      return "listremovetail";
    default:
      return "";
  }
}

char *listerr_msg(list_err err) {
  switch(err & LIST_ERR_MSG) {
    case LIST_ERR_MSG_NO_ERROR:
      return "No errors.";
    case LIST_ERR_MSG_CREATE_NODE:
      return "Failed in creation of node.";
    case LIST_ERR_MSG_EMPTY_LIST:
      return "List is empty.";
    default:
      return "";
  }
}

list_err listbegin(
    list *l,
    list_type header,
    list_destroyvalue (*destroyelem)(list_type)
  ) {
  node *newnode = (node *)malloc(sizeof(node));
  if(newnode) {
    newnode->elem = header;
    newnode->next = newnode;
    newnode->prev = newnode;

    l->header      = newnode;
    l->tail        = newnode;
    l->size        = 0;
    l->destroyelem = destroyelem;

    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_BEGIN;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_BEGIN;
}

void listclean(list *l) {
  node *_node = l->header->next;

  while(_node != l->header) {
    l->destroyelem(_node->elem);
    free(_node);
    _node = _node->next;
  }

  l->size = 0;
}

void listdestroy(list *l) {
  node *_node = l->header->next;

  while(_node != l->header) {
    l->destroyelem(_node->elem);
    free(_node);
    _node = _node->next;
  }

  if(_node->elem)
    l->destroyelem(_node->elem);
  free(_node);

  l->header = NULL;
  l->tail   = NULL;
  l->size   = 0;
}

inline uint8_t listempty(list *l) {
  if(l->size)
    return 0;
  return 1;
}

list_err listinserthead(list *l,
                        list_type elem) {
  node *newnode = (node *)malloc(sizeof(node));
  if(newnode) {
    newnode->elem       = elem;
    newnode->next       = l->header;
    newnode->prev       = l->tail;
// hahahahhaha... well, I write this line after
// you will know what I'm talking about
    l->header->next->prev = newnode;
    l->header->next       = newnode;
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_INSERT_H;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_INSERT_H;
}

list_err listinserttail(list *l,
                        list_type elem) {
  node *newnode = (node *)malloc(sizeof(node));
  if(newnode) {
    newnode->elem       = elem;
    newnode->next       = l->header;
    newnode->prev       = l->tail;
// hahahhahahah 2 (I'm having second toughts about it)
// I read that making several -> wasn't good
// so... what to do? don't really know...
    l->tail->prev->next = newnode;
    l->tail->prev       = newnode;
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_INSERT_T;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_INSERT_T;
}

list_err listinsert(list *l,
                    list_type elem,
                    list_position n) {
  node *newnode = (node *)malloc(sizeof(node));
  if(newnode) {
    newnode->elem = elem;

    if(n > l->size) n = l->size;
// Make sure we are counting correct
    node **prev = &(l->header->next);
    while(n-- > 0)
      prev = &((*prev)->next);

    newnode->next = (*prev)->next;
    newnode->prev = *prev;
// I really laugh when I write this line... hahaha
// if you are confused, don't be... this was the first one
    (*prev)->next->prev = newnode;
    *prev = newnode;
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_INSERT;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_INSERT;
}

list_err listremovehead(list *l) {
  if(l->size) {
    node *head = l->header->next;
    l->header->next = head->next;
    l->destroyelem(head->elem);
    free(head);
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_REMOVE_H;
  }
  return LIST_ERR_MSG_EMPTY_LIST | LIST_ERR_FUNCTION_REMOVE_H;
}

list_err listremovetail(list *l) {
  if(l->size) {
    node *tail = l->tail;
    tail->prev->next = tail->next;
    l->destroyelem(tail->elem);
    free(tail);
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_REMOVE_T;
  }
  return LIST_ERR_MSG_EMPTY_LIST | LIST_ERR_FUNCTION_REMOVE_T;
}

list_err listremove(list *l,
                    list_position n) {
  if(l->size) {
    node **prev = &(l->header->next);
    if(n > l->size) n = l->size;
    while(n-- > 0)
      prev = &((*prev)->next);

    node *rmnode = (*prev)->next;
    rmnode->next->prev = *prev;
    *prev = rmnode->next;
    l->destroyelem(rmnode->elem);
    free(rmnode);
    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_REMOVE_T;
  }
  return LIST_ERR_MSG_EMPTY_LIST | LIST_ERR_FUNCTION_REMOVE;
}

/* Iterator */
void list_itrbind(iterator *i, void *l) {
  i->data = l;
  i->node = ((list *)l)->header;
}

uint8_t list_itrfirst(iterator *i) {
  if(i->node == ((list *)(i->data))->header)
    return 1;
  return 0;
}

uint8_t list_itrlast(iterator *i) {
  if(i->node == ((list *)(i->data))->tail)
    return 1;
  return 0;
}

void list_itrprev(iterator *i) {
  i->data = ((node *)(i->node))->prev;
}

void list_itrnext(iterator *i) {
  i->data = ((node *)(i->node))->next;
}

itrelem list_itrretrieve(iterator *i) {
  return ((node *)(i->node))->elem;
}

/* Sorting */
void listswap(list *l,
              list_position i,
              list_position e) {
  if(i > l->size)
    i = l->size;
  if(e > l->size)
    e = l->size;

  if(i == e) return;
  if(e < i) {
    list_position j = i;
    i = e;
    e = j;
  }
 // TODO: we can optmize
  node *node1 = l->header;
  while(i-- > 0)
    node1 = node1->next;

  e -= i;
  node *node2 = node1;
  while(e-- > 0)
    node2 = node2->next;

  list_type aux = node1->elem;
  node1->elem = node2->elem;
  node2->elem = aux;
}
