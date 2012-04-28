/*
 * sll.c
 * -----
 * Author: Nate Hardison
 *
 * Implementation of some helper functions for a generic, singly-linked
 * list. Includes some interesting algorithms (reversal, cycle detection).
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "sll.h"

void
sll_push(node **list, node *n)
{
    assert(list != NULL);
    assert(n != NULL);

    n->next = *list;
    *list = n;
}

node *
sll_pop(node **list)
{
    assert(list != NULL);
    assert(*list != NULL);

    node *n = *list;
    *list = n->next;

    return n;
}

void
sll_insert_after(node *n, node *to_insert)
{
    assert(n != NULL);
    assert(to_insert != NULL);

    to_insert->next = n->next;
    n->next = to_insert;
}

void
sll_remove_after(node *n)
{
    assert(n != NULL);

    // TODO: implement me!
}

/* Find the last elem of a list */
node *
sll_find_last(node *list)
{
    node *last;

    for (last = list; list != NULL; list = list->next) {
        last = list;
    }

    return last;
}

void
sll_append(node **list, node *n)
{
    assert(list != NULL);
    assert(n != NULL);

    if (*list == NULL) sll_push(list, n);
    else sll_insert_after(sll_find_last(*list), n);
}

node *
sll_ith(node *list, int i)
{
    assert(i >= 0);

    for (; i > 0; i--) {
        assert(list != NULL);
        list = list->next;
    }

    return list;
}

void
sll_insert_ith(node **list, node *n, int i)
{
    assert(list != NULL);
    assert(n != NULL);
    assert(i >= 0);

    if (i == 0) {
        sll_push(list, n);
    } else {
        node *prev = sll_ith(*list, i - 1);
        sll_insert_after(prev, n);
    }
}

void
sll_remove_ith(node **list, int i)
{
    assert(list != NULL);
    assert(i >= 0);

    // TODO: implement me!
}

static void
count_length(void *elem, void *aux_data)
{
    (*(size_t *)aux_data)++;
}

size_t
sll_length(node *list)
{
    size_t length = 0;
    sll_map(list, count_length, &length);
    return length;
}

void
sll_free(node *list, sll_free_fn free_fn)
{
    while (list != NULL) {
        node *next = list->next;
        if (free_fn != NULL) {
            free_fn(list->data);
        }
        free(list);
        list = next;
    }
}

node *
sll_search(node *list, void *elem, sll_cmp_fn cmp_fn)
{
    assert(elem != NULL);
    assert(cmp_fn != NULL);

    for (; list != NULL; list = list->next) {
        if (cmp_fn(list->data, elem) == 0) return list;
    }

    return NULL;
}

size_t
sll_elem_count(node *list, void *elem, sll_cmp_fn cmp_fn)
{
    size_t elem_count = 0;

    for (node *n = list; n != NULL; n = n->next) {
        if (cmp_fn(n->data, elem) == 0) elem_count++;
    }

    return elem_count;
}

void
sll_map(node *list, sll_map_fn map_fn, void *aux_data)
{
    for (; list != NULL; list = list->next) {
        map_fn(list->data, aux_data);
    }
}

void
sll_bubble_sort(node **list, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);

    // TODO: implement me!
}

void
sll_sorted_insert(node **list, node *n, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(n != NULL);
    assert(cmp_fn != NULL);

    node *prev = NULL;
    for (node *cur = *list; cur != NULL; prev = cur, cur = cur->next) {
        if (cmp_fn(cur->data, n->data) > 0) break;
    }

    if (prev == NULL) sll_push(list, n);
    else sll_insert_after(prev, n);

}

void
sll_insert_sort(node **list, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(cmp_fn != NULL);

    node *sorted_list = NULL;
    
    while (*list != NULL) {
        node *n = sll_pop(list);
        sll_sorted_insert(&sorted_list, n, cmp_fn);
    }

    *list = sorted_list;
}

void
sll_front_back_split(node *list, node **front, node **back)
{
    assert(front != NULL);
    assert(back != NULL);

    size_t length = sll_length(list);
    size_t front_length = (length / 2) + (length % 2);

    *front = list;
    node *front_end = sll_ith(list, front_length - 2);

    *back = front_end->next;
    front_end->next = NULL;
}

void
sll_remove_duplicates(node *list, sll_cmp_fn cmp_fn)
{

}

void
sll_move_node(node **dst, node **src)
{
    assert(dst != NULL);
    assert(src != NULL);

    sll_push(dst, sll_pop(src));
}

void
sll_alternating_split(node *list, node **a, node **b)
{
    node **to_push = a;

    while (list != NULL) {
        sll_push(a, sll_pop(&list));
        if (list != NULL) {
            sll_push(b, sll_pop(&list));
        }
    }
}

node *
sll_shuffle_merge(node *a, node *b)
{
    return NULL;
}

node *
sll_sorted_merge(node *a, node *b, sll_cmp_fn cmp_fn)
{
    return NULL;
}

void
sll_merge_sort(node **list, sll_cmp_fn cmp_fn)
{

}

node *
sll_sorted_intersect(node *a, node *b, sll_cmp_fn cmp_fn)
{
    return NULL;
}

void
sll_reverse(node **list)
{
    assert(list != NULL);

    node *reversed_list = NULL;

    while (*list != NULL) {
        sll_push(&reversed_list, sll_pop(list));
    }

    *list = reversed_list;
}

void
sll_reverse_recursive(node **list)
{

}

bool
sll_detect_cycle(node *list)
{
    if (list == NULL) return false;

    for (node *tortoise = list, *hare = list->next; hare != NULL; 
         tortoise = tortoise->next, hare = hare->next) {

        if (tortoise == hare) return true;

        hare = hare->next;
        if (hare == NULL) break;
    }

    return false;
}