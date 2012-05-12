#include "sll.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

/* Taken from Julie Zelenski, May 2012 */
#define NOT_YET_IMPLEMENTED printf("%s() not yet implemented!\n", __FUNCTION__); exit(1);

static node_t *
build_node(void *elem, size_t elem_size)
{
  node_t *n = calloc(1, sizeof(node_t) + elem_size);
  if (n == NULL) {
    /* TODO: handle out-of-memory error */
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

void
sll_push(sll *list, void *elem)
{
  assert(list != NULL);
  assert(elem != NULL);
  node_t *n = build_node(elem, list->elem_size);
  push(&list->head, n);
}

void *
sll_pop(sll *list)
{
  assert(list != NULL);
  node_t *n = pop(&list->head);
  void *elem = malloc(list->elem_size);
  memcpy(elem, n->data, list->elem_size);
  free(n);
  return elem;
}

void *
sll_ith(sll *list, int i)
{
  assert(list != NULL);
  assert(i >= 0);
  node_t *ith_node_t = ith(list->head, i);
  return ith_node_t->data;
}

void
sll_insert_ith(sll *list, int i, void *elem)
{
  assert(list != NULL);
  assert(i >= 0);
  assert(elem != NULL);
  node_t *n = build_node(elem, list->elem_size);
  if (i == 0) {
    push(&list->head, n);
  } else {
    node_t *prev = ith(list->head, i - 1);
    insert_after(prev, n);
  }
}

void
sll_remove_ith(sll *list, int i)
{
  assert(list != NULL);
  assert(i >= 0);
  NOT_YET_IMPLEMENTED
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
    node_t *n = pop(&list->head);
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
  for (node_t *n = list->head; n != NULL; n = n->next) {
    if (cmp_fn(n->data, elem) == 0) return n->data;
  }
  return NULL;
}

size_t
sll_elem_count(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(elem != NULL);
  assert(cmp_fn != NULL);
  size_t elem_count = 0;
  for (node_t *n = list->head; n != NULL; n = n->next) {
    if (cmp_fn(n->data, elem) == 0) elem_count++;
  }
  return elem_count;
}

void
sll_map(sll *list, sll_map_fn map_fn, void *aux_data)
{
  assert(list != NULL);
  assert(map_fn != NULL);
  for (node_t *n = list->head; n != NULL; n = n->next) {
    map_fn(n->data, aux_data);
  }
}

void
sll_bubble_sort(sll *list, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(cmp_fn != NULL);
  NOT_YET_IMPLEMENTED
}

void
sll_sorted_insert(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(elem != NULL);
  assert(cmp_fn != NULL);
  node_t *n = build_node(elem, list->elem_size);
  node_t *prev = NULL;
  for (node_t *cur = list->head; cur != NULL; prev = cur, cur = cur->next) {
    if (cmp_fn(cur->data, n->data) > 0) break;
  }
  if (prev == NULL) {
    push(&list->head, n);
  } else {
    insert_after(prev, n);
  }
}

void
sll_insert_sort(sll *list, sll_cmp_fn cmp_fn)
{
  assert(list != NULL);
  assert(cmp_fn != NULL);
  /* TODO: fix me! */
  NOT_YET_IMPLEMENTED

  /*node_t *sorted_list = NULL;
  while (list->head != NULL) {
    node_t *n = pop(&list->head);
    sorted_insert(&sorted_list, n, cmp_fn);
  }
  list->head = sorted_list;*/
}

void
sll_front_back_split(sll *list, sll *front, sll *back)
{
  assert(list != NULL);
  assert(front != NULL);
  assert(back != NULL);
  /* TODO: fix me! */
  /*size_t length = sll_length(list);
  size_t front_length = (length / 2) + (length % 2);
  *front = list;
  node_t *front_end = sll_ith(list, front_length - 2);
  *back = front_end->next;
  front_end->next = NULL;*/
  NOT_YET_IMPLEMENTED
}

void
sll_remove_duplicates(sll *list, sll_cmp_fn cmp_fn)
{
  for (node_t *prev = list->head, *cur = prev->next; cur != NULL;
      cur = prev->next) {
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
  NOT_YET_IMPLEMENTED
}

sll *
sll_sorted_merge(sll *a, sll *b, sll_cmp_fn cmp_fn)
{
  NOT_YET_IMPLEMENTED
}

void
sll_merge_sort(sll *list, sll_cmp_fn cmp_fn)
{
  NOT_YET_IMPLEMENTED
}

sll *
sll_sorted_intersect(sll *a, sll *b, sll_cmp_fn cmp_fn)
{
  NOT_YET_IMPLEMENTED
}

void
sll_reverse(sll *list)
{
  assert(list != NULL);
  node_t *reversed_list = NULL;
  while (list->head != NULL) {
    push(&reversed_list, pop(&list->head));
  }
  list->head = reversed_list;
}

void
sll_reverse_recursive(sll *list)
{
  NOT_YET_IMPLEMENTED
}

bool
sll_detect_cycle(sll *list)
{
  NOT_YET_IMPLEMENTED
  /*for (node_t *tortoise = list->head, *hare = tortoise; hare != NULL;
       tortoise = tortoise->next, hare = hare->next) {
    hare = hare->next;
    if (tortoise == hare) return true;
    hare = hare->next;
    if (hare == NULL) break;
  }
  return false;*/
}
