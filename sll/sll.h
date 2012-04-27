/*
 * sll.h
 * -----
 * Author: Nate Hardison
 * Updated: Mar 15 2012
 *
 * Implementation of a generic singly linked list.
 */
#include <stdbool.h>

#ifndef _SLL_H
#define _SLL_H

typedef struct
{
	void *next;
	char data[];
} node;

typedef void (*sll_map_fn)(void *elem, void *aux_data);
typedef int (*sll_cmp_fn)(const void *a, const void *b);
typedef void (*sll_free_fn)(void *elem);

void sll_push(node **list, node *n);
node *sll_pop(node **list);

void sll_insert_after(node *n, node *to_insert);
void sll_remove_after(node *n);

node *sll_find_last(node *list);
void sll_append(node **list, node *n);

node *sll_ith(node *list, int i);
void sll_insert_ith(node **list, node *n, int i);
void sll_remove_ith(node **list, int i);

size_t sll_length(node *list);
void sll_free(node *list, sll_free_fn free_fn);
node *sll_search(node *list, void *elem, sll_cmp_fn cmp_fn);
size_t sll_elem_count(node *list, void *elem, sll_cmp_fn cmp_fn);
void sll_map(node *list, sll_map_fn map_fn, void *aux_data);
void sll_bubble_sort(node **list);

void sll_sorted_insert(node **list, node *n);
void sll_insert_sort(node **list);

void sll_front_back_split(node *list, node **front, node **back);
void sll_remove_duplicates(node *list, sll_cmp_fn cmp_fn);
void sll_move_node(node **dst, node **src);
void sll_alternating_split(node *list, node **a, node **b);
node *sll_shuffle_merge(node *a, node *b);
node *sll_sorted_merge(node *a, node *b);
void sll_merge_sort(node **list);
node *sll_sorted_intersect(node *a, node *b);

void sll_reverse(node **list);
void sll_reverse_recursive(node **list);

bool sll_has_cycle(node *list);

#endif