#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "../../util/util.h"

int
cmp_int(const void *a, const void *b)
{
  return *(const int *)a - *(const int *)b;
}

int
main(int argc, const char *argv[])
{
  bst_t *tree = bst_init(sizeof(int), cmp_int, NULL);
  assert(tree != NULL);
  assert(tree->root == NULL);

  return 0;
}
