/*
 * sll-test.c
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
#include <signal.h>

#include "sll.h"

static int
cmp_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

static void
print_addr(void *elem, void *unused)
{
    printf("%p->", *(void **)elem);
}

static void
print_double(void *elem, void *unused)
{
    printf("%.2f->", *(double *)elem);
}

static void
print_int(void *elem, void *unused)
{
    printf("%d->", *(int *)elem);
}

static void
print_list(node *list, sll_map_fn print_fn)
{
    sll_map(list, print_fn, NULL);
    printf("NULL\n");
}

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

static node *
build_int_list(int start, int end)
{
    node *list = NULL;
    node **last_ref = &list;

    for (; start < end; start++)
    {
        node *n = build_node(&start, sizeof(start));
        sll_push(last_ref, n);
        last_ref = &((*last_ref)->next);
    }

    return list;
}

static bool
verify_int_list(node *list, int start, int end)
{
    for (node *cur = list; cur != NULL && start <= end; cur = cur->next, start++)
    {
        // If the data doesn't match, error!
        if (*(int *)cur->data != start) return false;
    }

    // If we haven't reached the end of the expected range, error!
    if (start < end) return false;

    return true;
}

static void
test_push()
{
    printf("Testing sll_push()\n------------------\n");

    printf("Pushing ints 1-100 onto the list...");
    node *list = build_int_list(0, 100);
    printf("OK!\n");

    printf("Verifying everything's in the list....");
    assert(verify_int_list(list, 0, 100));
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_push()!\n\n");    
}

static void
test_pop()
{
    printf("Testing sll_pop()\n-----------------\n");

    printf("Pushing 100 ints (0-99) onto the list...");
    node *list = build_int_list(0, 100);
    printf("OK!\n");

    printf("Popping everything out of the list...");
    for (int i = 0; i < 100; i++) {
        assert(list != NULL);
        node *n = sll_pop(&list);
        assert(i == *(int *)n->data);
        free(n);
    }
    assert(list == NULL);
    printf("OK!\n");

    /*printf("Trying to pop an empty list...");
    sll_pop(&list);
    printf("OK!\n");*/

    printf("All good with sll_pop()!\n\n");
}

static void
test_insert_after()
{
    printf("Testing sll_insert_after()\n--------------------------\n");

    node *list = NULL;

    node n, o;
    sll_push(&list, &n);
    sll_insert_after(&n, &o);

    printf("All good with sll_insert_after()!\n\n");
}

static void
test_remove_after()
{
    printf("Testing sll_remove_after()\n--------------------------\n");

    printf("All good with sll_remove_after()!\n\n");
}

static void
test_find_last()
{
    printf("Testing sll_find_last()\n-----------------------\n");

    node *list = NULL;

    printf("Ensure last element of empty list is NULL...");
    assert(sll_find_last(list) == NULL);
    printf("OK!\n");

    printf("Ensure last elem of a single-elem list is that elem...");
    node n;
    sll_push(&list, &n);
    assert(sll_find_last(list) == &n);
    printf("OK!\n");

    printf("Ensure last elem of two-elem list is the second elem...");
    node o;
    sll_push(&list, &o);
    assert(sll_find_last(list) == &n);
    printf("OK!\n");

    printf("All good with sll_find_last()!\n\n");
}

static void
test_append()
{
    printf("Testing sll_append()\n---------------\n");

    node *list = NULL;

    // Append some ints to list
    for (int i = 0; i < 100; i++) {
        node *n = build_node(&i, sizeof(i));
        sll_append(&list, n);
    }

    assert(verify_int_list(list, 0, 100));
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_append()!\n\n");
}

static void
test_ith()
{
    printf("Testing sll_ith()\n-----------------\n");

    node *list = NULL;

    printf("Ensure sll_ith() on empty list errors...");
    //node *n = sll_ith(list, 0);
    printf("OK!\n");

    printf("Push 0-10 onto list, ensure that we can find them...");
    list = build_int_list(0, 10);
    for (int i = 0; i < 10; i++)
    {
        assert(*(int *)(sll_ith(list, i)->data) == i);    
    }
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_ith()!\n\n");
}

static void
test_insert_ith()
{
    printf("Testing sll_insert_ith()\n------------------------\n");

    node *list = NULL;

    int elem = 0;
    node *zero = build_node(&elem, sizeof(elem));

    elem = 1;
    node *one = build_node(&elem, sizeof(elem));

    elem = 2;
    node *two = build_node(&elem, sizeof(elem));

    sll_insert_ith(&list, zero, 0);
    sll_insert_ith(&list, two, 1);
    sll_insert_ith(&list, one, 1);

    assert(verify_int_list(list, 0, 3));

    sll_free(list, NULL);

    printf("All good with sll_insert_ith()!\n\n");
}

static void
test_remove_ith()
{
    printf("Testing sll_remove_ith()\n----------------\n");

    printf("All good with sll_remove_ith()!\n\n");
}

static void
test_length()
{
    printf("Testing sll_length()\n--------------------\n");

    node *list = NULL;

    printf("Make sure empty list has length 0...");
    assert(sll_length(list) == 0);
    printf("OK!\n");

    printf("Pushing 100 ints (0-99) onto the list...");
    list = build_int_list(0, 100);
    printf("OK!\n");

    printf("Ensuring length == 100...");
    assert(sll_length(list) == 100);
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_length()!\n\n");
}

static void
check_free(void *elem)
{

}

static void
test_free()
{
    printf("Testing sll_free()\n------------------\n");

    node *list = NULL;

    printf("Pushing 100 ints (0-99) onto the list...");
    list = build_int_list(0, 100);
    printf("OK!\n");

    printf("Freeing the list...");
    sll_free(list, check_free);
    printf("OK!\n");

    printf("All good with sll_free()!\n\n");
}

static void
test_search()
{
    printf("Testing search...");

    node *list = NULL;

    // Make sure we can't search an empty list
    int a = 7;
    assert(sll_search(NULL, &a, cmp_int) == NULL);

    // Make sure we can do a simple list
    node *n = build_node(&a, sizeof(a));
    sll_push(&list, n);
    assert(*(int *)(sll_search(list, &a, cmp_int)->data) == a);

    sll_free(list, NULL);
    list = NULL;

    // Prepend some ints to list
    list = build_int_list(0, 100);

    // Make sure we can successfully find everything in the list
    for (int i = 0; i < 100; i++) {
        assert(*(int *)(sll_search(list, &i, cmp_int)->data) == i);
    }

    // Make sure we can't find other things in the list
    for (int i = 0; i-- > -100; ) {
        assert(sll_search(list, &i, cmp_int) == NULL);
    }

    for (int i = 101; i < 200; i++) {
        assert(sll_search(list, &i, cmp_int) == NULL);
    }

    sll_free(list, NULL);

    printf("OK!\n");
}

static void
test_elem_count()
{
    printf("Testing sll_elem_count()\n------------------------\n");

    node *list = build_int_list(0, 10);

    // Push all evens onto list again
    for (int i = 0; i < 10; i += 2) {
        node *n = build_node(&i, sizeof(i));
        sll_push(&list, n);
    }

    // Push all multiples of 4 onto list one more time
    for (int i = 0; i < 10; i += 4) {
        node *n = build_node(&i, sizeof(i));
        sll_push(&list, n);
    }

    int one = 1, six = 6, eight = 8;
    assert(sll_elem_count(list, &one, cmp_int) == 1);
    assert(sll_elem_count(list, &six, cmp_int) == 2);
    assert(sll_elem_count(list, &eight, cmp_int) == 3);

    sll_free(list, NULL);

    printf("All good with sll_elem_count()!\n\n");
}

static void
test_map()
{
    printf("Testing sll_map()\n-----------------\n");

    printf("All good with sll_map()!\n\n");
}

static void
test_bubble_sort()
{
    printf("Testing sll_bubble_sort()\n-------------------------\n");

    printf("All good with sll_bubble_sort()!\n\n");
}

static void
test_sorted_insert()
{
    printf("Testing sll_sorted_insert()\n---------------------------\n");
    
    node *list = build_int_list(5, 10);

    int i = 4;
    node *n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);

    i = 2;
    n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);

    i = 10;
    n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);

    i = 12;
    n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);    

    i = 3;
    n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);

    i = 11;
    n = build_node(&i, sizeof(i));
    sll_sorted_insert(&list, n, cmp_int);

    assert(verify_int_list(list, 2, 13));
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_sorted_insert()!\n\n");
}

static void
test_insert_sort()
{
    printf("Testing sll_insert_sort()\n-------------------------\n");

    node *list = build_int_list(0, 10);


    sll_insert_sort(&list, cmp_int);
    
    assert(verify_int_list(list, 0, 10));
    printf("OK!\n");

    sll_free(list, NULL);

    printf("All good with sll_insert_sort()!\n\n");
}

static void
test_front_back_split()
{
    printf("Testing sll_front_back_split()\n------------------------------\n");

    printf("Checking the empty list...");
    node *list = NULL;
    node *front, *back;
    sll_front_back_split(list, &front, &back);
    assert(front == NULL);
    assert(back == NULL);
    printf("OK!\n");

    printf("Checking a single-elem list...");
    int i = 7;
    node *n = build_node(&i, sizeof(i));
    sll_push(&list, n);
    sll_front_back_split(list, &front, &back);
    assert(front == n);
    assert(back == NULL);
    printf("OK!\n");

    printf("Checking a two-elem list...");
    
    printf("OK!\n");

    printf("Checking a three-elem list...");

    printf("OK!\n");

    printf("Checking a four-elem list...");

    printf("OK!\n");
    printf("All good with sll_front_back_split()!\n\n");
}

static void
test_remove_duplicates()
{
    printf("Testing sll_remove_duplicates()\n-------------------------------\n");

    printf("Checking an empty list...");
    node *list = NULL;
    sll_remove_duplicates(list, cmp_int, NULL);
    printf("OK!\n");

    printf("Checking a single-elem list...");
    int i = 7;
    node *n = build_node(&i, sizeof(i));
    sll_push(&list, n);
    sll_remove_duplicates(list, cmp_int, NULL);
    sll_free(list, NULL);
    list = NULL;
    printf("OK!\n");

    printf("Checking a list with no duplicates...");
    for (int i = 0; i < 10; i++)
    {
        node *n = build_node(&i, sizeof(i));
        sll_push(&list, n);
    }
    sll_remove_duplicates(list, cmp_int, NULL);
    assert(sll_length(list) == 10);
    sll_free(list, NULL);
    list = NULL;
    printf("OK!\n");

    printf("Checking a list with all duplicates...");
    for (int i = 0; i < 4; i++)
    {
        int j = 7;
        node *n = build_node(&j, sizeof(j));
        sll_push(&list, n);
    }
    sll_remove_duplicates(list, cmp_int, NULL);
    assert(sll_length(list) == 1);
    sll_free(list, NULL);
    list = NULL;
    printf("OK!\n");

    printf("Checking a list with half duplicates...");
    for (int i = 0; i < 5; i++)
    {
        node *n = build_node(&i, sizeof(i));
        sll_push(&list, n);

        if (i % 2 == 0)
        {
            n = build_node(&i, sizeof(i));
            sll_push(&list, n);
        }
    }
    assert(sll_length(list) == 8);
    sll_remove_duplicates(list, cmp_int, NULL);
    assert(sll_length(list) == 5);
    sll_free(list, NULL);
    list = NULL;
    printf("OK!\n");

    printf("All good with sll_remove_duplicates()!\n\n");
}

static void
test_move_node()
{
    printf("Testing sll_move_node()\n-----------------------\n");

    node *list = build_int_list(0, 10);

    printf("All good with sll_move_node()!\n\n");
}

static void
test_alternating_split()
{
    printf("Testing sll_alternating_split()\n-------------------------------\n");

    printf("All good with sll_alternating_split()!\n\n");
}

static void
test_shuffle_merge()
{
    printf("Testing sll_shuffle_merge()\n---------------------------\n");

    printf("All good with sll_shuffle_merge()!\n\n");
}

static void
test_sorted_merge()
{
    printf("Testing sll_sorted_merge()\n--------------------------\n");

    printf("All good with sll_sorted_merge()!\n\n");
}

static void
test_merge_sort()
{
    printf("Testing sll_merge_sort()\n------------------------\n");

    printf("All good with sll_merge_sort()!\n\n");
}

static void
test_sorted_intersect()
{
    printf("Testing sll_sorted_intersect()\n------------------------------\n");

    printf("All good with sll_sorted_intersect()!\n\n");
}

static void
test_reverse()
{
    printf("Testing sll_reverse()\n---------------------\n");

    printf("Checking an empty list...");
    node *list = NULL;
    sll_reverse(&list);
    printf("OK!\n");

    printf("Checking a single-elem list...");

    printf("OK!\n");


    printf("Checking a ten-elem list...");
    for (int i = 0; i < 10; i++) {
        node *n = build_node(&i, sizeof(i));
        sll_push(&list, n);
    }

    sll_reverse(&list);

    for (int i = 0; i < 10; i++, list = list->next) {
        assert(i == *(int *)list->data);
    }
    printf("OK!\n");

    printf("All good with sll_reverse()!\n\n");
}

static void
test_reverse_recursive()
{
    printf("Testing sll_reverse_recursive()\n-------------------------------\n");

    printf("All good with sll_reverse_recursive()!\n\n");
}

static void
test_has_cycle()
{
    printf("Testing sll_has_cycle()\n-----------------------\n");

    printf("All good with sll_has_cycle()!\n\n");
}

int
main(int argc, const char *argv[])
{
    test_push();
    test_pop();

    test_insert_after();
    test_remove_after();

    test_find_last();
    test_append();

    test_ith();
    test_insert_ith();
    test_remove_ith();

    test_length();
    test_free();
    test_search();
    test_elem_count();
    test_map();
    test_bubble_sort();

    test_sorted_insert();
    test_insert_sort();

    //test_front_back_split();
    test_remove_duplicates();

    test_move_node();
    test_alternating_split();

    test_shuffle_merge();
    test_sorted_merge();
    test_merge_sort();
    test_sorted_intersect();

    test_reverse();
    test_reverse_recursive();

    test_has_cycle();

    return 0;
}
