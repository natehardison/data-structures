/*************************************************************************
 * stack-list.c
 * ------------
 * Nate Hardison <natehardison@gmail.com>
 *
 * Implementation of a singly-linked list-based generic stack container.
 ************************************************************************/

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
    size_t elem_size;
    size_t num_elems;
    stack_free_fn free_fn;
    void *elems; // TODO: use sll library
};

stack *stack_init(size_t elem_size, size_t init_alloc,
                  stack_free_fn free_fn)
{
    stack *s = calloc(1, sizeof(stack));
    if (s == NULL)
    {
        fprintf(stderr, "error: stack_init(): Out of heap memory\n");
        exit(1);
    }
    s->elem_size = elem_size;
    s->num_elems = 0;
    s->free_fn = free_fn;
    s->elems = NULL;
    return s;
}

void stack_push(stack *s, const void *elem)
{
	// TODO: use sll library!
}

void *stack_pop(stack *s)
{
	return NULL;
}

size_t stack_size(const stack *s)
{
	return s->num_elems;
}

void stack_free(stack *s)
{
    // TODO
}
