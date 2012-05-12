/**
 * stack-list.c
 * ------------
 * Author: Nate Hardison
 *
 * Implementation of a list-based stack.
 */
#include <stdlib.h>
#include <string.h>

#include "stack.h"

stack *
stack_init(size_t elem_size, size_t init_alloc, stack_free_fn free_fn)
{
    stack *s = calloc(1, sizeof(stack));
    s->elem_size = elem_size;
    s->num_elems = 0;
    s->alloc_size = (init_alloc == 0)? DEFAULT_ALLOCATION : init_alloc;
    s->free_fn = free_fn;
    s->elems = NULL;

    return s;
}

void
stack_push(stack *s, void *elem)
{
	
}

void *
stack_pop(stack *s)
{
	return NULL;
}

size_t
stack_size(stack *s)
{
	return s->num_elems;
}