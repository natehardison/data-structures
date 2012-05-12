#include <stdlib.h>
#include <assert.h>
#include "node.h"

void
push(node **head, node *n)
{
  assert(head != NULL);
  assert(n != NULL);
  n->next = *head;
  *head = n;
}

node *
pop(node **head)
{
  assert(head != NULL);
  assert(*head != NULL);
  node *n = *head;
  *head = n->next;
  return n;
}

void
insert_after(node *n, node *to_insert)
{
  assert(n != NULL);
  assert(to_insert != NULL);
  to_insert->next = n->next;
  n->next = to_insert;
}

node *
remove_after(node *n)
{
  assert(n != NULL);
  node *to_remove = n->next;
  if (to_remove != NULL) {
    n->next = to_remove->next;
  }
  return to_remove;
}

node *
ith(node *head, int i)
{
  for (; i > 0; i--) {
    assert(head != NULL);
    head = head->next;
  }
  return head;
}

size_t
length(node *head)
{
  size_t len = 0;
  while (head != NULL) {
    head = head->next;
    len++;
  }
  return len;
}

void
reverse(node **head)
{
  node *reversed_list = NULL;
  while (*head != NULL) {
    push(&reversed_list, pop(head));
  }
  *head = reversed_list;   
}

void
reverse_recursive(node **head)
{
  // TODO!
}
