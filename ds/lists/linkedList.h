#ifndef LinkedList_h 
#define LinkedList_h
#include "../nodes/node.h"
typedef struct LinkedList 
{
	struct Node* head;
	int length;
	struct Node * (*get)(struct LinkedList * list, int index);
	void (*print)(struct LinkedList * list);
	void (*remove)(struct LinkedList * list, int index);
	void (*insert)(struct LinkedList * list, void * data, int size, unsigned int index);
	void (*push)(struct LinkedList * list, void * data, int size);
	int (*indexof)(struct LinkedList * list, void * data, int size);
	void (*clear)(struct LinkedList * list);
	void (*free)(struct LinkedList * list);
} LinkedList;

struct LinkedList linkedListConstructor();

void linkedListDeconstructor(struct LinkedList * list);

struct Node * iterateList(struct LinkedList* list, int index);

/*retorna o indice do vlaor procurado*/
int indexofInt(int data, struct LinkedList* list);

/*atualiza a prop length da lista*/
void updateLength(struct LinkedList* list);
void printList(struct LinkedList * list);
void pushNodeToList(struct LinkedList * list, void * data, int size);
void insertNodeToList(struct LinkedList * list, void * data, int size,unsigned int index);
void removeNodeFromList(struct LinkedList * list, int index);
void clearList(struct LinkedList * list);
void freeLinkedList(struct LinkedList * list);

#endif
