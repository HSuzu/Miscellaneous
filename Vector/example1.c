#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main() {
  vector v;
  vctinit(&v, sizeof(int));
  int elem = 1;
  fprintf(stderr, "vctpush returned %ld\n", vctpush(&v, &elem, 10));

  elem = 2;
  fprintf(stderr, "vctpush returned %ld\n", vctpush(&v, &elem, 1));

  int foo[8] = {11,12,13,14,15,16,17,18};
  fprintf(stderr, "vctcopycontent returned %d\n", vctcopycontent(&v, foo, 1, 100));

  fprintf(stderr, "vctpop returned %d\n", vctpop(&v, &elem, 1));

  fprintf(stdout, "%d\n", elem);

  vctclean(&v);
  return 0;
}
