#include<stdbool.h>
#include<stdlib.h>
#include "link.h"

#ifndef QUEUE_TOKEN__
#define QUEUE_TOKEN__
typedef struct
{
	LL* storage;
	int max_size;
	int size;
	node* front;
	node* rear;
}queue;


queue* get_queue (int max_size)
{
	queue* ptr = (queue*) malloc (sizeof (queue));

	ptr->storage = get_linked_list();
	ptr->size = 0;
	ptr->max_size = max_size;
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;

	return ptr;
}

bool is_queue_full (queue* ptr)
{
	return ptr->size == ptr->max_size;
}

bool is_queue_empty (queue* ptr)
{
	return ptr->size == 0;
}

bool insert (queue* ptr, int val)
{
	if (is_queue_full(ptr))
		return false;

	add_tail(ptr->storage, val);
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;
	ptr->size += 1;
	return true;
}

bool delete (queue* ptr, int* ret)
{
	if (is_queue_empty(ptr))
		return false;
	
	del_head(ptr->storage, ret);
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;
	ptr->size -= 1;
	return true;
}

void release_queue(queue* ptr)
{
	free(ptr->storage);
	free(ptr);
}
#endif
