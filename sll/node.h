/**
 * node.h
 * ------
 * Author: Nate Hardison
 *
 * Implementation of a generic, singly-linked list node module. This module
 * is intended to provide the primary linked list operations, nothing more.
 * Those interested in manipulating a singly-linked list of values and not
 * dropping to this level should rely on the sll module.
 */
#include <stdlib.h>

#ifndef SLL_NODE_H_
#define SLL_NODE_H_

struct node
{
  struct node *next;
  char data[];
};
typedef struct node node_t;

void push(node_t **head, node_t *n);
node_t *pop(node_t **head);
void insert_after(node_t *n, node_t *to_insert);
node_t *remove_after(node_t *n);
node_t *ith(node_t *head, int i);
size_t length(node_t *head);
void reverse(node_t **head);

#endif /* SLL_NODE_H_ */
