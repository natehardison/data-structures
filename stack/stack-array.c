/*************************************************************************
 * stack-array.c
 * ------------
 * Nate Hardison <natehardison@gmail.com>
 *
 * Implementation of an array-based generic stack container.
 ************************************************************************/

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * "Grows" the stack by doubling its size.
 */
static void grow(stack *s)
{
	// TODO: check to see if s->alloc_size <= UINT_MAX?
	s->alloc_size *= 2;
	s->elems = realloc(s->elems, s->alloc_size);
	if (s->elems == NULL)
	{
		fprintf(stderr, "error: grow(): Out of heap memory\n");
		exit(1);
	}
}

/**
 * Returns the address of the ith element in the stack.
 */
static void *ith_elem(const stack *s, size_t i)
{
	return ((char *)s->elems + (i * s->elem_size));
}

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
	s->alloc_size = (init_alloc == 0)? DEFAULT_ALLOCATION : init_alloc;
	s->free_fn = free_fn;
    s->elems = calloc(init_alloc, s->elem_size);
    if (s->elems == NULL)
    {
    	fprintf(stderr, "error: stack_init(): Out of heap memory\n");
    	exit(1);
    }
    return s;
}

void stack_push(stack *s, const void *elem)
{
	if (s->num_elems == s->alloc_size)
	{
		grow(s);
	}
	memcpy(ith_elem(s, s->num_elems++), elem, s->elem_size);
}

void *stack_pop(stack *s)
{
	return ith_elem(s, --s->num_elems);
}

size_t stack_size(const stack *s)
{
	return s->num_elems;
}

void stack_free(stack *s)
{
	if (s->free_fn != NULL)
	{
		for (size_t i = 0; i < s->num_elems; i++)
		{
			s->free_fn(ith_elem(s, i));
		}
	}
	free(s->elems);
	free(s);
}
