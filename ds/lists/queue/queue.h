#ifndef queue_h
#define queue_h
#include "../linkedList.h"

typedef struct Queue
{
	LinkedList list;

	void (*push)(struct Queue *queue, void *data, int size);
	void *(*pop)(struct Queue *queue);
} Queue;

struct Queue queueConstructor();
void pushToQueue(Queue *queue, void *data, int size);
void * popFromQueue(Queue* queue);
#endif
