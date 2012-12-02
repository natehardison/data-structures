/*************************************************************************
 * stack.h
 * ------------
 * Nate Hardison <natehardison@gmail.com>
 *
 * Interface for a generic stack container.
 ************************************************************************/

#ifndef _STACK_H
#define _STACK_H

#include <stddef.h>

#define DEFAULT_ALLOCATION 10

typedef void (*stack_free_fn)(void *elem);

typedef struct
{
    size_t elem_size;
    size_t num_elems;
    size_t alloc_size;
    stack_free_fn free_fn;
    void *elems;
}
stack;

/**
 * Initializes a new stack for elements of size elem_size. The stack will
 * contain space for init_alloc elements initially. free_fn is to be used
 * when the elements are in need of special disposal upon freeing the
 * stack.
 *
 * Implementation note: We only need the stack_free_fn when calling
 * stack_free, as when we pop elements off of the stack we don't free them
 * (instead we return them to the caller). As a result, we could avoid
 * passing the free function in here and save it for stack_free. This
 * would save the overhead of the function pointer in the stack structure.
 * However, we do this for consistency with the other data structures.
 */
stack *stack_init(size_t elem_size, size_t init_alloc,
                  stack_free_fn free_fn);

/**
 * Puts a new element on the top of the stack.
 */
void stack_push(stack *s, const void *elem);

/**
 * Returns the element on the top of the stack, decrementing the stack's
 * size.
 */
void *stack_pop(stack *s);

/**
 * Returns the current size of the stack.
 */
size_t stack_size(const stack *s);

/**
 * Disposes of the stack and of all of the elements currently contained
 * within.
 */
void stack_free(stack *s);

#endif /* _STACK_H */
