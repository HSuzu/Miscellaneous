#include "list.h"

char *listerr_func(list_err err) {
  switch(err & LIST_ERR_FUNCTION) {
    case LIST_ERR_FUNCTION_BEGIN:
      return "listbegin";
    case LIST_ERR_FUNCTION_INSERT:
      return "listinsert";
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

    l->head        = newnode;
    l->tail        = newnode;
    l->size        = 0;
    l->destroyelem = destroyelem;

    return LIST_ERR_MSG_NO_ERROR | LIST_ERR_FUNCTION_BEGIN;
  }
  return LIST_ERR_MSG_CREATE_NODE | LIST_ERR_FUNCTION_BEGIN;
}



/* Iterator */
void list_itrbind(iterator *i, void *l) {
  i->data = l;
  i->node = ((list *)l)->head->next;
}

uint8_t list_itrlast(iterator *i) {
  if(i->node == ((list *)(i->data))->head)
    return 1;
  return 0;
}

void list_itrnext(iterator *i) {
  i->data = ((node *)(i->node))->next;
}

itrelem list_itrretrieve(iterator *i) {
  return ((node *)(i->node))->elem;
}
