#ifndef SLL_NODE_H_
#define SLL_NODE_H_

struct node_t
{
  struct node_t *next;
  char data[];
};
typedef struct node_t node;

void push(node **head, node *n);
node *pop(node **head);
void insert_after(node *n, node *to_insert);
node *remove_after(node *n);
node *last(node *head);
node *ith(node *head, int i);
size_t length(node *head);
void reverse(node **head);

#endif /* SLL_NODE_H_ */
