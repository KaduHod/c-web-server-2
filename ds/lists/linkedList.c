#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

struct Node * iterateList(struct LinkedList * list, int index)
{

	if(list == NULL) 
	{
		printf("Error:: list is null!\n");
		exit(1);
	}

	if(list->length == 0)
	{
		printf("Error:: empty list");
	}

	int count = 0;

	Node * current = list->head;

	for(int count = 0; count < index; count++)
	{
		current = current->next;
	}

	return current;
}

void pushNodeToList(struct LinkedList * list, void * data, int size)
{
	Node * current = list->head;

	if(list->head == NULL)
	{
		list->head = nodeConstructor(data, size);
		list->length++;
		return;
	}

	Node * lastItem = list->get(list, list->length -1);
	lastItem->next = nodeConstructor(data, size);
	list->length++;
}

void printList(struct LinkedList * list)
{
	if(list->length == 0)
	{
		printf("[]\n");
		return;
	}
	printf("[\n");
	int index = 0;
	Node * current = list->head;
	while(current != NULL)
	{
		printf("\t%i : %i\n", index,*(int*) current->data);
		current = current->next;
		index++;
	}
	printf("]\n");
}

void insertNodeToList(struct LinkedList * list, void * data, int size, unsigned int index)
{
	if(index > list->length || index < 0) 
	{
		printf("Error:: index out of range for this list!\n");
		exit(1);
	}

	if(index == list->length) 
	{
		pushNodeToList(list, data, size);
		return;
	}

	Node * newNode = nodeConstructor(data, sizeof(int));

	if(index == 0 )
	{
		Node * head = list->head;
		newNode->next = head;	
		list->head = newNode;
	} else {
		Node * cursor = list->get(list, index - 1);

		if(cursor->next != NULL) 
		{	
			newNode->next = cursor->next;
		}

		cursor->next = newNode;

		Node * current = list->head;
	}

	list->length++;
}

void removeNodeFromList(struct LinkedList * list, int index)
{
	if(index > list->length -1 || index < 0) 
	{
		printf("Error:: index out of range for this list!\n");
		exit(1);
	}

	if(index == 0)
	{
		Node * head = list->head;
		list->head = head->next;
//		freeNode(head);
	}

	if(index > 0) {
		Node * previous = list->get(list, index - 1);
		Node * target = previous->next;
		previous->next = target->next != NULL ? target->next : NULL; 
//		freeNode(target);
	}

	list->length--;
}

void clearList(struct LinkedList * list)
{
	if(list == NULL) {
		return;
	}

	Node * head = list->head;

	if(head == NULL)
	{
		return;
	}

	Node * current = head;
	Node * previous = head;
	while(current->next != NULL)
	{
		previous = current;
		current = current->next;
		freeNode(previous);
	}
	list->length = 0;
	freeNode(current);
}

void freeLinkedList(struct LinkedList * list)
{
	if(list->length > 0)
	{
		clearList(list);
	}

	free(list);
}

struct LinkedList linkedListConstructor()
{
	struct LinkedList list;
	list.head = NULL;
	list.length = 0;
	list.get = iterateList;
	list.remove = removeNodeFromList;
	list.insert = insertNodeToList; 
	list.push = pushNodeToList;
	list.clear = clearList;
	list.free = freeLinkedList;
	list.print = printList;
	return list;
}
