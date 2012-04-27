/*
 * sll-test.c
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

static void
test_find_last()
{
	printf("Testing sll_find_last()\n-----------------------\n");

	printf("Ensure last element of empty list is NULL...");
	assert(sll_find_last(NULL) == NULL);
	printf("OK!\n");

	printf("Ensure last elem of a single-elem list is that elem...");
	node n;
	n.next = NULL;
	assert(sll_find_last(&n) == &n);
	printf("OK!\n");

	printf("Ensure last elem of two-elem list is the second elem...");
	node o;
	o.next = NULL;
	n.next = &o;
	assert(sll_find_last(&n) == &o);
	printf("OK!\n");

	printf("All good with sll_find_last()!\n\n");
}

static void
test_push()
{
	printf("Testing sll_push()\n------------------\n");
            
	node *list = NULL;

	printf("Pushing 100 ints (0-99) onto the list...");
	for (int i = 0; i < 100; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}
	printf("OK!\n");

	printf("Verifying everything's in the list....");
	for (int i = 100; i-- > 0; ) {
		node *n = list;
		assert(n != NULL);
		assert(i == *(int *)n->data);
		list = list->next;
		free(n);
	}
	assert(list == NULL);
	printf("OK!\n");

	printf("All good with sll_push()!\n\n");	
}

static void
test_pop()
{
	printf("Testing sll_pop()\n-----------------\n");

	node *list = NULL;

	printf("Pushing 100 ints (0-99) onto the list...");
	for (int i = 0; i < 100; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}
	printf("OK!\n");

	printf("Popping everything out of the list...");
	for (int i = 99; i >= 0; i--) {
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
check_free(void *elem)
{

}

static void
test_free()
{
	printf("Testing sll_free()\n------------------\n");

	node *list = NULL;

	printf("Pushing 100 ints (0-99) onto the list...");
	for (int i = 0; i < 100; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}
	printf("OK!\n");

	printf("Freeing the list...");
	sll_free(list, check_free);
	printf("OK!\n");

	printf("All good with sll_free()!\n\n");
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
	for (int i = 0; i < 100; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}
	printf("OK!\n");

	printf("Ensuring length == 100...");
	assert(sll_length(list) == 100);
	printf("OK!\n");

	printf("All good with sll_length()!\n\n");
}

static void
test_insert_after()
{
	printf("Testing insert_after...");

	printf("OK!\n");
}

static void
test_append()
{
	printf("Testing append...");

	node *list = NULL;

	// Append some ints to list
	for (int i = 0; i < 100; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_append(&list, n);
	}

	// Make sure all of our ints are in there
	for (int i = 0; i < 100; i++, list = list->next) {
		assert(i == *(int *)list->data);
	}

	// Make sure we're at the end of the list
	assert(list == NULL);

	printf("OK!\n");
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
	for (int i = 0; i < 100; i++) {
		n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}

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
test_reverse()
{
	printf("Testing reverse...");

	node *list = NULL;

	// Prepend some ints to list
	for (int i = 0; i < 10; i++) {
		node *n = build_node(&i, sizeof(i));
		sll_push(&list, n);
	}

	sll_reverse_recursive(&list);
	print_list(list, print_int);

	for (int i = 0; i < 10; i++, list = list->next) {
		assert(i == *(int *)list->data);
	}

	printf("OK!\n");
}

int
main(int argc, const char *argv[])
{
	test_find_last();
	test_push();
	test_pop();
	test_append();
	test_insert_after();
	test_free();
	test_length();
	test_search();
	test_reverse();

	return 0;
}