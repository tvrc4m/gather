#ifndef NODE_H
#define NODE_H
// 双向链表

struct node{
	void *data;
	struct node *prev;
	struct node *next;
};

typedef struct node *node;

node url_top;

node phone_top;

node node_init(void *ele);

int node_push(node top,void *ele);

int in_node(node top,void *ele);

int node_size(node top);

void *node_pop(node top);

void node_free(node top);

#endif