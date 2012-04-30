#ifndef _STACK_H
#define _STACK_H

#define DEFAULT_ALLOCATION 10

typedef void (*stack_free_fn)(void *elem);

typedef struct
{
    size_t elem_size;
    size_t num_elems;
    size_t alloc_size;
    stack_free_fn free_fn;
    void *elems;
} stack;

stack *stack_init(size_t elem_size, size_t init_alloc, stack_free_fn free_fn);
void stack_push(stack *s, void *elem);
void *stack_pop(stack *s);
size_t stack_size(stack *s);

#endif /* _STACK_H */