/**
 * sll.h
 * -----
 * Author: Nate Hardison
 *
 * Implementation of a generic, singly-linked list. This serves as a wrapper
 * around the node_t module, which is where most of the primary linked list
 * operations are implemented. The idea is that clients of the sll module
 * are interested in manipulating values instead of node_ts, so we hide those
 * details from them.
 */
#include <stdbool.h>

#include "node.h" /* Figure out a good way to forward-declare node_t */

#ifndef SLL_H_
#define SLL_H_

typedef void (*sll_map_fn)(void *elem, void *aux_data);
typedef int (*sll_cmp_fn)(const void *a, const void *b);
typedef void (*sll_free_fn)(void *elem);

typedef struct
{
  node_t *head;
  size_t elem_size;
  sll_free_fn free_fn;
} sll;

void sll_push(sll *list, void *elem);
void *sll_pop(sll *list);
void *sll_ith(sll *list, int i);
void sll_insert_ith(sll *list, int i, void *elem);
void sll_remove_ith(sll *list, int i);
size_t sll_length(sll *list);
void sll_free(sll *list);
void *sll_search(sll *list, void *elem, sll_cmp_fn cmp_fn);
size_t sll_elem_count(sll *list, void *elem, sll_cmp_fn cmp_fn);
void sll_map(sll *list, sll_map_fn map_fn, void *aux_data);
void sll_bubble_sort(sll *list, sll_cmp_fn cmp_fn);
void sll_sorted_insert(sll *list, void *elem, sll_cmp_fn cmp_fn);
void sll_insert_sort(sll *list, sll_cmp_fn cmp_fn);

/* Splits a list into two sublists, one for the front half
 * and one for the back half. If the number of elements is
 * odd, then the extra element goes in the front list. */
void sll_front_back_split(sll *list, sll *front, sll *back);

/* Removes duplicates from a list sorted in increasing
 * order. Traverses the list only once. */
void sll_remove_duplicates(sll *list, sll_cmp_fn cmp_fn);

/* Moves the first node_t of the source list to the front
 * of the destination list. */
void sll_move_node(sll *dst, sll *src);
void sll_alternating_split(sll *list, sll *a, sll *b);
sll *sll_shuffle_merge(sll *a, sll *b);
sll *sll_sorted_merge(sll *a, sll *b, sll_cmp_fn cmp_fn);
void sll_merge_sort(sll *list, sll_cmp_fn cmp_fn);
sll *sll_sorted_intersect(sll *a, sll *b, sll_cmp_fn cmp_fn);
void sll_reverse(sll *list);
bool sll_has_cycle(sll *list);

#endif /* SLL_H_ */
