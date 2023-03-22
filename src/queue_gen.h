#include<stdbool.h>
#include<stdlib.h>
#include "link_gen.h"

#ifndef QUEUE_GEN_TOKEN__
#define QUEUE_GEN_TOKEN__
typedef struct
{
	LL_gen* storage;
	int max_size;
	int size;
	node_gen* front;
	node_gen* rear;
}queue_gen;


queue_gen* get_queue_gen (int max_size)
{
	queue_gen* ptr = (queue_gen*) malloc (sizeof (queue_gen));

	ptr->storage = get_linked_list_gen();
	ptr->size = 0;
	ptr->max_size = max_size;
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;

	return ptr;
}

bool is_queue_gen_full (queue_gen* ptr)
{
	return ptr->size == ptr->max_size;
}

bool is_queue_gen_empty (queue_gen* ptr)
{
	return ptr->size == 0;
}

bool insert_gen (queue* ptr, void* val)
{
	if (is_queue_gen_full(ptr))
		return false;

	add_tail_gen(ptr->storage, val);
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;
	ptr->size += 1;
	return true;
}

bool delete_gen (queue* ptr, void** ret)
{
	if (is_queue_gen_empty(ptr))
		return false;
	
	del_head_gen(ptr->storage, ret);
	ptr->front = ptr->storage->head;
	ptr->rear = ptr->storage->tail;
	ptr->size -= 1;
	return true;
}

void release_queue_gen(queue* ptr)
{
	release_linked_list_gen(ptr->storage);
	free(ptr);
}
#endif
