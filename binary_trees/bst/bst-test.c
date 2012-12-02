#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

static int cmp_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

static void print_int(void *elem, void *unused)
{
    printf("%d->", *(int *)elem);
}

static node_t *build_node(int val)
{
    node_t *n = calloc(1, sizeof(node_t));
    if (n == NULL)
    {
        printf("Out of memory...\n");
        exit(1);
    }
    memcpy(n->data, &val, sizeof(int));
    return n;
}

int main(int argc, const char *argv[])
{
    bst_t *tree = bst_init(sizeof(int), cmp_int, NULL);
    assert(tree != NULL);
    assert(tree->root == NULL);

    tree->root = build_node(3);
    printf("Height: %lu\n", bst_height(tree));

    tree->root->left_child = build_node(5);
    printf("Height: %lu\n", bst_height(tree));

    tree->root->right_child = build_node(5);
    printf("Height: %lu\n", bst_height(tree));

    tree->root->right_child->right_child = build_node(5);
    printf("Height: %lu\n", bst_height(tree));

    tree->root->right_child->right_child->right_child = build_node(5);
    printf("Height: %lu\n", bst_height(tree));
  
/*    for (int i = 0; i < 10000; i++)
    {
        int rand = (int)(random() % 100000);
        bst_insert(tree, &rand);
    }

    for (int i = 0; i < 10000; i++)
    {
        int rand = (int)(random() % 100000);
        printf("bst_search(%d) = %s\n", rand, bst_search(tree, &rand)? "YES" : "NO");
    }
*/
  
    //bst_map(tree, IN_ORDER, print_int, NULL);
    //printf("\n");
  
    return 0;
}
