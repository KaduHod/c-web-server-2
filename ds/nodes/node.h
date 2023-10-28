#ifndef Node_h
#define Node_h

typedef struct Node 
{
	void * data;
	struct Node *next;	
	struct Node *previous;
	int size;
} Node;

struct Node * nodeConstructor(void *data, int size);

void freeNode(struct Node *node);

typedef struct NodeInt 
{
	int * data;
	struct NodeInt* next;
} NodeInt;

struct NodeInt * nodeIntConstructor(int data);

void freeNodeInt(struct NodeInt *node);
#endif
