#ifndef BST_BST_H_
#define BST_BST_H_

#include <stdlib.h>

typedef int (*bst_cmp_fn)(const void *a, const void *b);
typedef void (*bst_free_fn)(void *elem);
typedef void (*bst_map_fn)(void *elem, void *aux_data);

enum ORDER { PRE_ORDER, IN_ORDER, POST_ORDER };

struct node {
  struct node *left_child;
  struct node *right_child;
  char data[];
};

struct bst {
  struct node *root;
  size_t elem_size;
  bst_cmp_fn cmp_fn;
  bst_free_fn free_fn;
};

typedef struct bst bst_t;
typedef struct node node_t;

bst_t *bst_init(size_t elem_size, bst_cmp_fn cmp_fn, bst_free_fn free_fn);
void bst_free(bst_t *tree);
size_t bst_height(bst_t *tree);
void bst_insert(bst_t *tree, void *elem);
void *bst_search(bst_t *tree, void *elem);
void bst_map(bst_t *tree, enum ORDER traversal_order, bst_map_fn map_fn, void *aux_data);
void bst_remove(bst_t *tree);

#endif /* BST_BST_H_ */
