#ifndef LIST_H
#define LIST_H

#define PATH_ITERATOR "../Iterator/iterator.h"

/* Include standard librarys */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Include iterator*/
#include PATH_ITERATOR

/* Error messages is separable into two
 * pieces: the function part and the msg
 * part.. the first 8bits holds the function
 * information (what function send the error)
 * the rest (8bits) holds the msg
 */
#define LIST_ERR_MSG      0x00FF
#define LIST_ERR_FUNCTION 0xFF00

/* Definitions of the error messages */
#define LIST_ERR_MSG_NO_ERROR    0x0000
#define LIST_ERR_MSG_CREATE_NODE 0x0001
#define LIST_ERR_MSG_EMPTY_LIST  0x0002

/* Here will be defined the values of the
 * functions (that will be used by the error
 * message)
 */

#define LIST_ERR_FUNCTION_BEGIN    0x0000
#define LIST_ERR_FUNCTION_INSERT   0x0100
#define LIST_ERR_FUNCTION_INSERT_H 0x0200
#define LIST_ERR_FUNCTION_INSERT_T 0x0300
#define LIST_ERR_FUNCTION_REMOVE   0x0400
#define LIST_ERR_FUNCTION_REMOVE_H 0x0500
#define LIST_ERR_FUNCTION_REMOVE_T 0x0600

typedef void *        list_type;
typedef void          list_destroyvalue;
typedef uint16_t      list_position;
typedef list_position list_size;
typedef uint16_t      list_err;

typedef struct _node {
  list_type elem;
  struct _node * next;
  struct _node * prev;
} node;

typedef struct _list {
  node *header;
  node *tail;
  list_size size;

  list_destroyvalue (*destroyelem)(list_type);
} list;

extern char *listerr_func(list_err err);
extern char *listerr_msg(list_err err);
extern list_err listbegin(list *l,
                          list_type header,
                          list_destroyvalue (*destroyelem)(list_type));

/* I think I must explain the difference
 * between clean and destroy... clean will
 * destroy all elements, but the list will
 * be functional... destroy will clean and
 * make the list non-functional
 */
extern void listclean(list *l);
extern void listdestroy(list *l);
extern inline uint8_t listempty(list *l);
extern list_err listinserthead(list *l,
                               list_type elem);
extern list_err listinserttail(list *l,
                               list_type elem);
extern list_err listinsert(list *l,
                           list_type elem,
                           list_position n);
extern list_err listremovehead(list *l);
extern list_err listremovetail(list *l);
extern list_err listremove(list *l,
                           list_position n);


/* Iterator */
extern void      list_itrbind(iterator *i, void *);
extern uint8_t   list_itrfirst(iterator *i);
extern uint8_t   list_itrlast(iterator *i);
extern void      list_itrprev(iterator *i);
extern void      list_itrnext(iterator *i);
extern list_type list_itrretrieve(iterator *i);

#endif
