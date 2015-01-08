#ifndef NODE_H
#define NODE_H

struct node{
	void *data;
	struct node *prev;
	struct node *next;
};


typedef struct node *node;

node node_init(void *ele);

int node_push(struct node *top,void *ele);

int in_node(struct node *top,void *ele);

int node_size(struct node *top);

void *node_pop(struct node *top);

#endif