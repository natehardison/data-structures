/**
 * sll.c
 * -----
 * Author: Nate Hardison
 *
 * Implementation of a generic, singly-linked list.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "sll.h"
#include "node.h"

static node *
build_node(void *elem, size_t elem_size)
{
  node *n = calloc(1, sizeof(node) + elem_size);
  if (n == NULL) {
    // TODO: handle out-of-memory error
  }
  memcpy(n->data, elem, elem_size);
  return n;
}

sll *
sll_init(size_t elem_size, sll_free_fn free_fn)
{
  assert(elem_size > 0);
  sll *list = malloc(sizeof(sll));
  list->head = NULL;
  list->elem_size = elem_size;
  list->free_fn = free_fn;
  return list;
}

/**
 * Pushes a node onto the front of a list.
 */
void
sll_push(sll *list, void *elem)
{
  assert(list != NULL);
  assert(elem != NULL);
  node *n = build_node(elem, list->elem_size);
  push(&list->head, n);
}

/**
 * Removes the first elem of a list and returns it.
 */
void *
sll_pop(sll *list)
{
  assert(list != NULL);
  node *n = pop(&list->head);
  void *elem = malloc(list->elem_size);
  memcpy(elem, n->data, list->elem_size);
  free(n);
  return elem;
}

/**
 * Returns a pointer to the ith elem in a list. Errors
 * if i is out of the range of the list (< 0 or > len - 1)
 */
void *
sll_ith(sll *list, int i)
{
  assert(list != NULL);
  assert(i >= 0);
  node *ith_node = ith(list->head, i);
  return ith_node->data;
}

/**
 * Inserts a node into a list immediately after another.
 * Does not work for empty lists.
 */
void
sll_insert_ith(sll *list, int i, void *elem)
{
  assert(list != NULL);
  assert(i >= 0);
  assert(elem != NULL);
  node *n = build_node(elem, list->elem_size);
  if (i == 0) {
    push(&list->head, n);
  } else {
    node *prev = ith(list->head, i - 1);
    insert_after(prev, n);
  }
}

void
sll_remove_ith(sll *list, int i)
{
  assert(list != NULL);
  assert(i >= 0);
  // TODO: implement me!
}

size_t
sll_length(sll *list)
{
  assert(list != NULL);
  return length(list->head);
}

void
sll_free(sll *list)
{
  assert(list != NULL);
  while (list->head != NULL) {
    node *n = pop(&list->head);
    if (list->free_fn != NULL) {
      list->free_fn(n->data);
    }
    free(n);
  }
  free(list);
}

void *
sll_search(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(elem != NULL);
  assert(cmp_fn != NULL);
  for (node *n = list->head; n != NULL; n = n->next) {
    if (cmp_fn(n->data, elem) == 0) return n->data;
  }
  return NULL;
}

/**
 * Counts the number of times that a particular elem
 * occurs in a list
 */
size_t
sll_elem_count(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(elem != NULL);
  assert(cmp_fn != NULL);
  size_t elem_count = 0;
  for (node *n = list->head; n != NULL; n = n->next) {
    if (cmp_fn(n->data, elem) == 0) elem_count++;
  }
  return elem_count;
}

void
sll_map(sll *list, sll_map_fn map_fn, void *aux_data)
{
  assert(list != NULL);
  assert(map_fn != NULL);
  for (node *n = list->head; n != NULL; n = n->next) {
    map_fn(n->data, aux_data);
  }
}

void
sll_bubble_sort(sll *list, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(cmp_fn != NULL);
  // TODO: implement me!
}

/**
 * Inserts a node into a list in sorted position according
 * to the supplied comparison function.
 */
void
sll_sorted_insert(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(elem != NULL);
  assert(cmp_fn != NULL);
  node *n = build_node(elem, list->elem_size);
  node *prev = NULL;
  for (node *cur = list->head; cur != NULL; prev = cur, cur = cur->next) {
    if (cmp_fn(cur->data, n->data) > 0) break;
  }
  if (prev == NULL) {
    push(&list->head, n);
  } else {
    insert_after(prev, n);
  }
}

/**
 * Sorts a list using the insert sort algorithm according
 * to the supplied comparison function.
 */
void
sll_insert_sort(sll *list, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(cmp_fn != NULL);
  node *sorted_list = NULL;
  while (list->head != NULL) {
    node *n = pop(&list->head);
    //sorted_insert(&sorted_list, n, cmp_fn);
  }
  list->head = sorted_list;
}

/**
 * Splits a list into two sublists, one for the front half
 * and one for the back half. If the number of elements is
 * odd, then the extra element goes in the front list.
 */
void
sll_front_back_split(sll *list, sll *front, sll *back)
{
  assert(list != NULL);
  assert(front != NULL);
  assert(back != NULL);
  /*size_t length = sll_length(list);
  size_t front_length = (length / 2) + (length % 2);
  *front = list;
  node *front_end = sll_ith(list, front_length - 2);
  *back = front_end->next;
  front_end->next = NULL;*/
}

/**
 * Removes duplicates from a list sorted in increasing
 * order. Traverses the list only once.
 */
void
sll_remove_duplicates(sll *list, sll_cmp_fn cmp_fn)
{
  for (node *prev = list->head, *cur = prev->next; cur != NULL; cur = prev->next) {
    if (cmp_fn(prev->data, cur->data) == 0) {
      remove_after(prev);
      if (list->free_fn != NULL) {
        list->free_fn(cur->data);
      }
    } else {
      prev = cur;
    }
  }
}

/**
 * Moves the first node of the source list to the front
 * of the destination list.
 */
void
sll_move_node(sll *dst, sll *src)
{
  assert(dst != NULL);
  assert(src != NULL);
  push(&dst->head, pop(&src->head));
}

void
sll_alternating_split(sll *list, sll *a, sll *b)
{
  while (list != NULL) {
    sll_move_node(a, list);
    if (list == NULL) break;
    sll_move_node(b, list);
  }
}

sll *
sll_shuffle_merge(sll *a, sll *b)
{
  return NULL;
}

sll *
sll_sorted_merge(sll *a, sll *b, sll_cmp_fn cmp_fn)
{
  return NULL;
}

void
sll_merge_sort(sll *list, sll_cmp_fn cmp_fn)
{

}

sll *
sll_sorted_intersect(sll *a, sll *b, sll_cmp_fn cmp_fn)
{
  return NULL;
}

void
sll_reverse(sll *list)
{
  assert(list != NULL);
  reverse(&list->head);
}

bool
sll_detect_cycle(sll *list)
{
  for (node *tortoise = &list->head, *hare = list->head; hare != NULL; 
       tortoise = tortoise->next, hare = hare->next) {
    if (tortoise == hare) return true;
    hare = hare->next;
    if (hare == NULL) break;
  }
  return false;
}
