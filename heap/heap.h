#ifndef _HEAP_H
#define _HEAP_H

typedef int (*heap_cmp_fn)(void *a, void *b);
typedef void (*heap_free_fn)(void *elem);

typedef struct heap heap_t;

heap_t *heap_init(size_t elem_size, heap_cmp_fn cmp_fn);
void heap_free(heap_t *heap, heap_free_fn free_fn);
void *heap_pop_max(heap_t *heap);
void heap_insert(heap_t *heap, void *elem);

#endif /* _HEAP_H */
