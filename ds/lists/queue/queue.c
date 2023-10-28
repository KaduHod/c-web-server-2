#include "queue.h"
#include <stdio.h>
#include "../linkedList.h"
#include <string.h>
#include <stdlib.h>

struct Queue queueConstructor()
{
	struct Queue queue;
	queue.list = linkedListConstructor();
	queue.push = pushToQueue;
	queue.pop = popFromQueue;
	return queue;
}; 

void pushToQueue(Queue * queue, void *data, int size)
{
	queue->list.insert(&queue->list, data, size, 0);
};

void * popFromQueue(Queue * queue)
{
	Node * node = queue->list.get(&queue->list, 0);
	queue->list.remove(&queue->list, 0);
	void * value = malloc(node->size);
	memcpy(value, node->data, node->size);
	freeNode(node);
	return value;
};
