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

static node *
build_node(void *elem, size_t elem_size)
{
    node *n = calloc(1, sizeof(node) + elem_size);
    if (n == NULL) {
        // handle out-of-memory error
    }
    memcpy(n->data, elem, elem_size);
    return n;
}

static void
push(node **head, node *n)
{
    assert(head != NULL);
    assert(n != NULL);

    n->next = *head;
    *head = n;
}

static void
pop(node **head)
{
    assert(list != NULL);
    assert(*list != NULL);

    node *n = *list;
    *list = n->next;

    return n;
}

static void
insert_after(node *n, node *to_insert)
{
    assert(n != NULL);
    assert(to_insert != NULL);

    to_insert->next = n->next;
    n->next = to_insert;
}

static void
remove_after(node *n, sll_free_fn free_fn)
{
    assert(n != NULL);

    // TODO: implement me!
}

/* Find the last elem of a list */
static node *
last(node *head)
{
    node *last;

    for (last = head; head != NULL; head = head->next) {
        last = head;
    }

    return last;
}

static void
append(node **head, node *n)
{
    if (*head == NULL) push(head, n);
    else insert_after(last(*head), n);
}

static node *
ith(node *head, int i)
{
    for (; i > 0; i--) {
        assert(head != NULL);
        head = head->next;
    }   
}

static void
insert_ith(node **head, int i, node *n)
{
    if (i == 0) {
        push(head, n);
    } else {
        node *prev = ith(head, i - 1);
        insert_after(prev, n);
    }
}

static size_t
length(node *head)
{
    size_t len = 0;
    while (head != NULL)
    {
        head = head->next;
        len++;
    }
    return len;
}

static void
sorted_insert(node **head, node *n, sll_cmp_fn cmp_fn)
{
    node *prev = NULL;
    for (node *cur = *head; cur != NULL; prev = cur, cur = cur->next) {
        if (cmp_fn(cur->data, n->data) > 0) break;
    }

    if (prev == NULL) push(head, n);
    else insert_after(prev, n);
}

static void
reverse(node **head)
{
    node *reversed_list = NULL;

    while (*head != NULL)
    {
        sll_push(&reversed_list, pop(head));
    }

    *head = reversed_list;   
}

/**** SLL API IMPLEMENTATION ****/
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

    node *n = build_node(elem, list->elem_size);
    push(&list->head, n);
}

void *
sll_pop(sll *list)
{
    assert(list != NULL);

    node *n = pop(&list->head);

    // Need to copy the elem to safe space so that we can
    // dispose of the node
    void *elem = malloc(list->elem_size);
    memcpy(elem, n->data, elem_size);

    free(n);

    return elem;
}

void
sll_append(sll *list, void *elem)
{
    assert(list != NULL);
    assert(elem != NULL);

    node *n = build_node(elem, list->elem_size);
    append(&list->head, n);
}

void *
sll_ith(sll *list, int i)
{
    assert(list != NULL);
    assert(i >= 0);

    node *ith = ith(list->head, i);

    return ith->data;
}

void
sll_insert_ith(sll *list, int i, void *elem)
{
    assert(list != NULL);
    assert(n != NULL);
    assert(i >= 0);

    node *n = build_node(elem, list->elem_size);
    insert_ith(&list->head, i, n);
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

    while (list->head != NULL)
    {
        node *n = pop(&list->head);
        if (list->free_fn != NULL)
        {
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

    for (node *n = list->head; n != NULL; n = n->next)
    {
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

    for (node *n = list->head; n != NULL; n = n->next)
    {
        if (cmp_fn(n->data, elem) == 0) elem_count++;
    }

    return elem_count;
}

void
sll_map(sll *list, sll_map_fn map_fn, void *aux_data)
{
    assert(list != NULL);
    assert(map_fn != NULL);

    for (node *n = list->head; n != NULL; n = n->next)
    {
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

void
sll_sorted_insert(sll *list, void *elem, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(elem != NULL);
    assert(cmp_fn != NULL);

    node *n = build_node(elem, list->elem_size);
    sorted_insert(&list->head, n, cmp_fn);
}

void
sll_insert_sort(sll *list, sll_cmp_fn cmp_fn)
{
    assert(list != NULL);
    assert(cmp_fn != NULL);

    node *sorted_list = NULL;
    
    while (list->head != NULL) {
        node *n = pop(&list->head);
        sorted_insert(&sorted_list, n, cmp_fn);
    }

    list->head = sorted_list;
}

void
sll_front_back_split(sll *list, sll *front, sll *back)
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
sll_remove_duplicates(sll *list, sll_cmp_fn cmp_fn)
{

}

void
sll_move_node(sll *dst, sll *src)
{
    assert(dst != NULL);
    assert(src != NULL);

    push(&dst->head, pop(&src->head));
}

void
sll_alternating_split(sll *list, sll **a, sll **b)
{
    node **to_push = a;

    while (list != NULL) {
        sll_push(a, sll_pop(&list));
        if (list == NULL) break;
        sll_push(b, sll_pop(&list));
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

void
sll_reverse_recursive(sll *list)
{

}

bool
sll_detect_cycle(sll *list)
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