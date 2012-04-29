#ifndef _DLL_H
#define _DLL_H

typedef struct {
	void *prev;
	void *next;
	char data[];
} node;

typedef void (*sll_map_fn)(void *elem, void *aux_data);
typedef int (*sll_cmp_fn)(const void *a, const void *b);
typedef void (*sll_free_fn)(void *elem);

void sll_push(node **list, node *n);
node *sll_pop(node **list);

#endif /* _DLL_H */