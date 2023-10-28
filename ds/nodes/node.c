#include "node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node * nodeConstructor(void * data, int size)
{
	if (size < 1) 
	{
		printf("Invalid data size for node \n");
		exit(1);
	}

	Node * node = (Node *) malloc(sizeof(Node));

	node->data = malloc(size);
	memcpy(node->data, data, size);
	node->size = size;
	node->next = NULL;
	node->previous = NULL;
	return node;
}


void freeNode(struct Node *node)
{
	if(node != NULL) {
		free(node->data);
	}; 
	free(node);
}
