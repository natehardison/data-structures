/*
 * sll.c
 * -----
 * Author: Nate Hardison
 * Updated: Apr 13 2012
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
	for (; i >= 0; i--) {
		assert(list != NULL);
		list = list->next;
	}

	return list;
}

void
sll_insert_ith(node **list, node *n, int i)
{
	node *ith = sll_ith(*list, i - 1);
	sll_insert_after(ith, n);
}

void
sll_remove_ith(node **list, int i)
{

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
		if (cmp_fn(n, elem) == 0) elem_count++;
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
sll_bubble_sort(node **list)
{

}

void
sll_sorted_insert(node **list, node *n)
{

}

void
sll_insert_sort(node **list)
{

}

void
sll_front_back_split(node *list, node **front, node **back)
{

}

void
sll_remove_duplicates(node *list, sll_cmp_fn cmp_fn)
{

}

void
sll_move_node(node **dst, node **src)
{

}

void
sll_alternating_split(node *list, node **a, node **b)
{

}

node *
sll_shuffle_merge(node *a, node *b)
{
	return NULL;
}

node *
sll_sorted_merge(node *a, node *b)
{
	return NULL;
}

void
sll_merge_sort(node **list)
{

}

node *
sll_sorted_intersect(node *a, node *b)
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

// TODO: needs fixing
void
sll_reverse_recursive(node **list)
{
	assert(list != NULL);

	if (*list == NULL) return;

	node *n = sll_pop(list);
	sll_reverse_recursive(list);
	sll_push(list, n);
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