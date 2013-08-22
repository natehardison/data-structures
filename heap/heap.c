#include "heap.h"

struct heap
{
    size_t elem_size;
    size_t num_elems;
    size_t alloc_size;
    size_t head;
    heap_cmp_fn cmp_fn;
    vector_t *elems;
};

static inline void parent(size_t i)
{
    return (i - 1) / 2;
}

static inline size_t left_child(size_t i)
{
    return (i * 2) + 1;
}

static inline size_t right_child(size_t i)
{
    return (i + 1) * 2;
}

heap_t *heap_init(size_t elem_size, heap_cmp_fn cmp_fn)
{
    heap_t *heap = calloc(1, sizeof(heap_t));
    if (heap == NULL)
    {
        printf("Out of memory\n");
        exit(1);
    }

    heap->cmp_fn = cmp_fn;

    heap->elems = vector_init();
    if (heap->elems == NULL)
    {


    }

    return heap;
}

void heap_free(heap_t *heap, heap_free_fn free_fn)
{
    if (heap->elems != NULL)
    {
        vector_free(heap->elems, free_fn);
    }
    free(heap);
}

void *pop_max(heap_t *heap)
{
    
}

void heap_insert(heap_t *heap, void *elem)
{
    vector_append(heap->elems, elem);
    heapify_up(heap); 
}

static void heapify_up(heap_t *heap)
{
    // we always inserted at the end
    size_t elem_index = vector_length(heap->elems) - 1;
    while (elem_index > 0)
    {
        size_t parent_index = parent(elem_index);
        if (heap->cmp_fn() <= 0) break;
        
        elem_index = parent_index;
    }
        
    void *elem = vector_nth(heap->elems, elem_index);
    void *parent = parent_index(elem_index);
    if (heap->cmp_fn(elem, parent(elem_index)) > 0)
    {
        swap(elem, parent);
    while (heap->cmp_fn(elem, parent(elem_index)) > 0);

}

static void heapify_down(heap_t *heap)
{

}

