#include<stdbool.h>
#include<stdlib.h>
#include "link.h"

#ifndef STACK_TOKEN__
#define STACK_TOKEN__
typedef struct
{
	LL* storage;
	int max_size;
	int size;
	node* top;
}stack;


stack* get_stack (int max_size)
{
	stack* ptr = (stack*) malloc (sizeof (stack));

	ptr->storage = get_linked_list();
	ptr->size = 0;
	ptr->max_size = max_size;
	ptr->top = ptr->storage->head;

	return ptr;
}

bool is_stack_full (stack* ptr)
{
	return ptr->size == ptr->max_size;
}

bool is_stack_empty (stack* ptr)
{
	return ptr->size == 0;
}

bool push (stack* ptr, int val)
{
	if (is_stack_full(ptr))
		return false;
	add_head(ptr->storage, val);
	ptr->top = ptr->storage->head;
	ptr->size += 1;
	//printf("%d pushed\n", val);
	return true;
}

bool pop (stack* ptr, int* ret)
{
	if (is_stack_empty(ptr))
		return false;
	del_head(ptr->storage, ret);
	ptr->top = ptr->storage->head;
	ptr->size -= 1;
	//printf("%d popped\n", *ret);
	return true;
}

void release_stack(stack* ptr)
{
	release_linked_list(ptr->storage);
	free(ptr);
}
#endif
