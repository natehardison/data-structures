#include "node.h"

#include <stdlib.h>
#include <assert.h>

void push(node_t **head, node_t *n)
{
  assert(head != NULL);
  assert(n != NULL);
  n->next = *head;
  *head = n;
}

node_t *pop(node_t **head)
{
  assert(head != NULL);
  assert(*head != NULL);
  node_t *n = *head;
  *head = n->next;
  return n;
}

void insert_after(node_t *n, node_t *to_insert)
{
  assert(n != NULL);
  assert(to_insert != NULL);
  to_insert->next = n->next;
  n->next = to_insert;
}

node_t *remove_after(node_t *n)
{
  assert(n != NULL);
  node_t *to_remove = n->next;
  if (to_remove != NULL) {
    n->next = to_remove->next;
  }
  return to_remove;
}

node_t *ith(node_t *head, int i)
{
  for (; i > 0; i--) {
    assert(head != NULL);
    head = head->next;
  }
  return head;
}

size_t length(node_t *head)
{
  size_t len = 0;
  while (head != NULL) {
    head = head->next;
    len++;
  }
  return len;
}
