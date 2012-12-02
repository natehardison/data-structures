#include "bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) (((x) > (y))? (x) : (y))

/* Taken from Julie Zelenski, May 2012 */
#define NOT_YET_IMPLEMENTED printf("%s() not yet implemented!\n", __FUNCTION__); exit(1);

static node_t *build_node(void *elem, size_t elem_size)
{
    node_t *n = calloc(1, sizeof(node_t) + elem_size);
    if (n == NULL)
    {
        printf("malloc() failed! Exiting...\n");
        exit(1);
    }
    memcpy(n->data, elem, elem_size);
    return n;
}

bst_t *bst_init(size_t elem_size, bst_cmp_fn cmp_fn, bst_free_fn free_fn)
{
    bst_t *tree = malloc(sizeof(bst_t));
    if (tree == NULL)
    {
        printf("malloc() failed! Exiting...\n");
        exit(1);
    }
    tree->root = NULL;
    tree->elem_size = elem_size;
    tree->cmp_fn = cmp_fn;
    tree->free_fn = free_fn;
    return tree;
}

static void free_node(node_t *n, bst_free_fn free_fn)
{
    if (n != NULL)
    {
        free_node(n->left_child, free_fn);
        free_node(n->right_child, free_fn);
        if (free_fn != NULL)
        {
            free_fn(n->data);
        }
        free(n);
    }
}

void bst_free(bst_t *tree)
{
    free_node(tree->root, tree->free_fn);
}

size_t height(node_t *n, size_t max_height)
{
    if (n == NULL)
    {
        return max_height;
    }

    return MAX(height(n->left_child, max_height + 1),
            height(n->right_child, max_height + 1));
}

size_t bst_height(bst_t *tree)
{
    return height(tree->root, 1);
}

static node_t *insert(node_t *n, node_t *to_insert, bst_cmp_fn cmp_fn)
{
    if (n == NULL)
    {
        return to_insert;
    }
    int comparison = cmp_fn(to_insert->data, n->data);
    if (comparison <= 0)
    {
        n->left_child = insert(n->left_child, to_insert, cmp_fn);
    }
    else
    {
        n->right_child = insert(n->right_child, to_insert, cmp_fn);
    }
    return n;
}

void bst_insert(bst_t *tree, void *elem)
{
    node_t *to_insert = build_node(elem, tree->elem_size);
    tree->root = insert(tree->root, to_insert, tree->cmp_fn);
}

void bst_remove(bst_t *tree)
{
    NOT_YET_IMPLEMENTED
}

static void *search(node_t *n, void *elem, bst_cmp_fn cmp_fn)
{
    if (n != NULL)
    {
        int comparison = cmp_fn(elem, n->data);
        if (comparison < 0)
        {
            return search(n->left_child, elem, cmp_fn);
        }
        else if (comparison > 0)
        {
            return search(n->right_child, elem, cmp_fn);
        }
    }
    return n;
}

void *bst_search(bst_t *tree, void *elem)
{
    return search(tree->root, elem, tree->cmp_fn);
}

static void map_pre_order(node_t *n, bst_map_fn map_fn, void *aux_data)
{
    if (n != NULL)
    {
        map_fn(n->data, aux_data);
        map_pre_order(n->left_child, map_fn, aux_data);
        map_pre_order(n->right_child, map_fn, aux_data);
    } 
}

static void map_in_order(node_t *n, bst_map_fn map_fn, void *aux_data)
{
    if (n != NULL)
    {
        map_in_order(n->left_child, map_fn, aux_data);
        map_fn(n->data, aux_data);
        map_in_order(n->right_child, map_fn, aux_data);
    }
}

    static void
map_post_order(node_t *n, bst_map_fn map_fn, void *aux_data)
{
    if (n != NULL)
    {
        map_post_order(n->left_child, map_fn, aux_data);
        map_post_order(n->right_child, map_fn, aux_data);
        map_fn(n->data, aux_data);
    }
}

void bst_map(bst_t *tree, enum ORDER traversal_order, bst_map_fn map_fn, void *aux_data)
{
    switch (traversal_order)
    {
        case PRE_ORDER:
            map_pre_order(tree->root, map_fn, aux_data);
            break;
        case POST_ORDER:
            map_post_order(tree->root, map_fn, aux_data);
            break;
        case IN_ORDER:
        default:
            map_in_order(tree->root, map_fn, aux_data);
            break;
    }
}
