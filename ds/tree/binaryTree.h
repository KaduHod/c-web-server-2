#ifndef binarytree_h
#define binarytree_h

#include "../nodes/node.h"

typedef struct Tree 
{
	Node *head;
	int (*compare)(void * dataone, void * datatwo);
	void * (*search)(struct Tree *tree, void *data);
	void (*insert)(struct Tree *tree, void *data, int size); 
	Node * (*iterate)(struct Tree *tree, Node * cursor, void *data, int *diraction);
} Tree;


struct Tree treeConstructor(int (*compare)(void *dataone, void *datatwo));
int compareTreeInt(void *dataone, void *datatwo);
void * searchTree(struct Tree *tree, void *data);
void insertIntoTree(struct Tree *tree, void *data, int size);
struct Node * iterateTree(struct Tree *tree, struct Node *cursor, void *data, int *direction);
#endif
