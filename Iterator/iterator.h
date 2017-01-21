#ifndef ITERATOR_H
#define ITERATOR_H

/* I was informed (hahahah, by who I don't
 * remember....) that iterators have three
 * steps: setups, ending and increasing the
 * value... Well, this iterator will function
 * more or less like this
 * iterator i;
 * for(itrbind(&i, list); !itrend(&i); itrnext(&i)) {
 *   elemtype *value = (elemtype *) itrretrieve(&i);
 *   ****** some code ******
 * }
 */

#include <stdint.h>

/* WOW, I remembered!!!
 * http://www.di-mare.com/adolfo/p/c-iter.htm
 * thanks...
 */

typedef void *   itrelem;
#define ITR_NODE_INT_VALUE NULL

typedef struct _iterator {
  void *data;
  itrelem node;
} iterator;

/* well, the functions depend on the type
 * of the variable... So the functions will
 * be develop inside the librarys or by the
 * user... Be Happy!! hahahahahha
 */
#endif
