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

/**
 * Pushes a node onto the front of a list.
 */
void
sll_push(node **list, node *n)
{
    assert(list != NULL);
    assert(n != NULL);

    n->next = *list;
    *list = n;
}

/**
 * Removes the first node of a list and returns it.
 */
node *
sll_pop(node **list)
{
    assert(list != NULL);
    assert(*list != NULL);

    node *n = *list;
    *list = n->next;

    return n;
}

/**
 * Inserts a node into a list immediately after another.
 * Does not work for empty lists.
 */
void
sll_insert_after(node *n, node *to_insert)
{
    assert(n != NULL);
    assert(to_insert != NULL);

    to_insert->next = n->next;
    n->next = to_insert;
}

/**
 *
 */
void
sll_remove_after(node *n, sll_free_fn free_fn)
{
    assert(n != NULL);

    node *to_remove = n->next;
    if (to_remove != NULL)
    {
        node *next = to_remove->next;
        if (free_fn != NULL) free_fn(to_remove->data);
        free(to_remove);
        n->next = next;
    }
}

/**
 * Finds the last element of a list.
 */
node *
sll_find_last(node *list)
{
    node *last;

    for (last = list; list != NULL; list = list->next)
    {
        last = list;
    }

    return last;
}

/**
 * Appends a node/list to a list.
 */
void
sll_append(node **list, node *n)
{
    assert(list != NULL);
    assert(n != NULL);

    if (*list == NULL) sll_push(list, n);
    else sll_insert_after(sll_find_last(*list), n);
}

/**
 * Returns a pointer to the ith node in a list. Errors
 * if i is out of the range of the list (< 0 or > len - 1)
 */
node *
sll_ith(node *list, int i)
{
    assert(i >= 0);

    for (; i > 0; i--)
    {
        assert(list != NULL);
        list = list->next;
    }

    return list;
}

/**
 * 
 */
void
sll_insert_ith(node **list, node *n, int i)
{
    assert(list != NULL);
    assert(n != NULL);
    assert(i >= 0);

    if (i == 0)
    {
        sll_push(list, n);
    } 
    else
    {
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
    while (list != NULL)
    {
        node *next = list->next;
        if (free_fn != NULL)
        {
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

    for (; list != NULL; list = list->next)
    {
        if (cmp_fn(list->data, elem) == 0) return list;
    }

    return NULL;
}

/**
 * Counts the number of times that a particular elem
 * occurs in a list
 */
size_t
sll_elem_count(node *list, void *elem, sll_cmp_fn cmp_fn)
{
    size_t elem_count = 0;

    for (node *n = list; n != NULL; n = n->next)
    {
        if (cmp_fn(n->data, elem) == 0) elem_count++;
    }

    return elem_count;
}

void
sll_map(node *list, sll_map_fn map_fn, void *aux_data)
{
    for (; list != NULL; list = list->next)
    {
        map_fn(list->data, aux_data);
    }
}

void
sll_bubble_sort(node **list, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);

    // TODO: implement me!
}

/**
 * Inserts a node into a list in sorted position according
 * to the supplied comparison function.
 */
void
sll_sorted_insert(node **list, node *n, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(n != NULL);
    assert(cmp_fn != NULL);

    node *prev = NULL;
    for (node *cur = *list; cur != NULL; prev = cur, cur = cur->next)
    {
        if (cmp_fn(cur->data, n->data) > 0) break;
    }

    if (prev == NULL) sll_push(list, n);
    else sll_insert_after(prev, n);

}

/**
 * Sorts a list using the insert sort algorithm according
 * to the supplied comparison function.
 */
void
sll_insert_sort(node **list, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(cmp_fn != NULL);

    node *sorted_list = NULL;
    
    while (*list != NULL)
    {
        node *n = sll_pop(list);
        sll_sorted_insert(&sorted_list, n, cmp_fn);
    }

    *list = sorted_list;
}

/**
 * Splits a list into two sublists, one for the front half
 * and one for the back half. If the number of elements is
 * odd, then the extra element goes in the front list.
 */
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

/**
 * Removes duplicates from a list sorted in increasing
 * order. Traverses the list only once.
 */
void
sll_remove_duplicates(node *list, sll_cmp_fn cmp_fn, sll_free_fn free_fn)
{
    if (list == NULL) return;

    for (node *prev = list, *cur = prev->next; cur != NULL; cur = prev->next)
    {
        if (cmp_fn(prev->data, cur->data) == 0) 
        {
            sll_remove_after(prev, free_fn);
        }
        else
        {
            prev = cur;
        }
    }
}

/**
 * Moves the first node of the source list to the front
 * of the destination list.
 */
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
    while (list != NULL)
    {
        sll_move_node(a, &list);
        if (list == NULL) break;
        sll_move_node(b, &list);
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

    while (*list != NULL)
    {
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
         tortoise = tortoise->next, hare = hare->next) 
    {
        if (tortoise == hare) return true;

        hare = hare->next;
        if (hare == NULL) break;
    }

    return false;
}