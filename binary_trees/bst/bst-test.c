#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

static int
cmp_int(const void *a, const void *b)
{
  return *(const int *)a - *(const int *)b;
}

static void
print_int(void *elem, void *unused)
{
  printf("%d->", *(int *)elem);
}

int
main(int argc, const char *argv[])
{
  bst_t *tree = bst_init(sizeof(int), cmp_int, NULL);
  assert(tree != NULL);
  assert(tree->root == NULL);

  for (int i = 0; i < 10; i++) {
    int rand = (int)(random() % 100);
    bst_insert(tree, &rand);
  }

  bst_map(tree, IN_ORDER, print_int, NULL);
  printf("\n");

  return 0;
}
