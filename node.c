#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"


node node_init(void *ele){
	node top=(node)malloc(sizeof(struct node));
	top->next=top->prev=top;
	top->data=ele;
	return top;
}

int node_push(node top,void *ele){
	if(!in_node(top,ele)){
		node next=top->next;
		node new_node=(node)malloc(sizeof(struct node));
		new_node->data=ele;
		if(next==top){
			new_node->prev=new_node->next=top;
			top->prev=top->next=new_node;

		}else{
			top->prev->next=new_node;
			new_node->next=top;
			new_node->prev=top->prev;
			top->prev=new_node;
		}
	}
	return node_size(top);
}

void *node_pop(node top){
	node bottom=top->prev;
	if(bottom==top) return NULL;
	bottom->prev->next=top;
	top->prev=bottom->prev;
	return bottom->data;
}

int in_node(node top,void *ele){
	node next=top->next;
	while(next!=top){
		if(!strcmp(next->data,ele)){
			return 1;
		}
		next=next->next;
	}
	return 0;
}

int node_size(node top){
	node next=top->next;
	int i=0;
	while(next!=top){
		i++;
		next=next->next;
	}
	return i;
}

void node_free(node top){
	node next=top->next;
	while(next!=top){
		next=next->next;
		free(next->prev);
	}
	free(top);
}
