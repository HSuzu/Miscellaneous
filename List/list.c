#include "list.h"

char *listerr_func(list_err err) {
  switch(err & LIST_ERR_FUNCTION) {
    case LIST_ERR_FUNCTION_BEGIN:
      return "listbegin";
    case LIST_ERR_FUNCTION_INSERT:
      return "listinsert";
  }
}

char *listerr_msg(list_err err) {
  switch(err & LIST_ERR_MSG) {
    case LIST_ERR_MSG_NO_ERROR:
      return "No errors.";
    case LIST_ERR_MSG_CREATE_NODE:
      return "Failed in creation of node.";
  }
}

list_err listbegin(
    list *l,
    list_type header,
    list_destroyvalue (*destroyelem)(list_type)
  ) {
  node *newnode = (node *)malloc(sizeof(node));
  if(node) {
    newnode->elem = header;
    newnode->next = newnode;
    newnode->prev = newnode;

    l->head        = newnode;
    l->tail        = newnode;
    l->size        = 0;
    l->destroyelem = destroyelem;

    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_BEGIN;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_BEGIN;
}


/* Iterator */
void list_itrbind(iterator *i, void *list) {
  i->data = list;
  i->node = (list *)list->header->next;
}

uint8_t list_itrlast(iterator *i) {
  if(i->node == ((node *)(i->data))->header)
    return 1;
  return 0;
}

void list_itrnext(iterator *i) {
  i->data = ((node *)(i->data))->next;
}

itrelem list_itrretrieve(iterator *i) {
  return ((node *)(i->data))->elem;
}
