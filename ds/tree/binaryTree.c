#include "binaryTree.h"
#include "../nodes/entry/entry.h"
#include <stdio.h>

struct Tree treeConstructor(int (*compare)(void *dataone, void *datatwo))
{
	struct Tree tree;
	tree.head = NULL;
	tree.compare = compare;
	tree.search = searchTree;
	tree.insert = insertIntoTree;
	tree.iterate = iterateTree;
	return tree;
};

int compareTreeInt(void *currentValue, void *newValue){
	int curr = (*(int*)currentValue);
	int new = (*(int*)newValue);
	if(new > curr) {
		return 1;
	} 
	
	if(new == curr) {
		return 0;
	}

	return -1;
};

void * searchTree(struct Tree *tree, void *data)
{
	int *direction;
	struct Node *cursor = tree->iterate(tree, tree->head, data, direction);
	if(*direction == 0) {
		return cursor->data;
	}

	return NULL;
};

void insertIntoTree(struct Tree *tree, void *data, int size)
{
	if(tree->head == NULL) {
		tree->head = nodeConstructor(data, size);
		return;
	}

	int direction;
	struct Node * cursor = tree->iterate(tree, tree->head, data, &direction);

	if(direction == 0) {
		printf("Value %i already in tree\n", *(int*)cursor->data);
		return;
	}

	struct Node *newNode = nodeConstructor(data, size);

	if(direction == 1) {
		cursor->next = newNode;
	}

	if(direction == -1) {
		cursor->previous = newNode;
	}
};

struct Node * iterateTree(struct Tree *tree, struct Node *cursor, void *data, int *direction)
{
	int compareResult = tree->compare(cursor->data, data);
	if(compareResult == 0) {
		*direction = 0;
		return cursor;
	}

	if(compareResult == 1) {
		if(cursor->next) {
			return tree->iterate(tree, cursor->next, data, direction);
		} 
		*direction = 1;
		return cursor;
	} 

	if(compareResult == -1)
	{
		if(cursor->previous) {
			return tree->iterate(tree, cursor->previous, data, direction);
		} 
		*direction = -1;
		return cursor;
	} 
	return NULL;
};
