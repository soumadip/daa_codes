#include<stdbool.h>
#include<stdlib.h>
#include "link_gen.h"

#ifndef STACK_GEN_TOKEN__
#define STACK_GEN_TOKEN__
typedef struct
{
	LL_gen* storage;
	int max_size;
	int size;
	node_gen* top;
}stack_gen;


stack_gen* get_stack_gen (int max_size)
{
	stack_gen* ptr = (stack_gen*) malloc (sizeof (stack_gen));

	ptr->storage = get_linked_list_gen();
	ptr->size = 0;
	ptr->max_size = max_size;
	ptr->top = ptr->storage->head;

	return ptr;
}

bool is_stack_gen_full (stack_gen* ptr)
{
	return ptr->size == ptr->max_size;
}

bool is_stack_gen_empty (stack_gen* ptr)
{
	return ptr->size == 0;
}

bool push_gen (stack_gen* ptr, void* val)
{
	if (is_stack_gen_full(ptr))
		return false;
	add_head_gen(ptr->storage, val);
	ptr->top = ptr->storage->head;
	ptr->size += 1;
	//printf("%d pushed\n", val);
	return true;
}

bool pop_gen (stack_gen* ptr, void** ret)
{
	if (is_stack_gen_empty(ptr))
		return false;
	del_head_gen(ptr->storage, ret);
	ptr->top = ptr->storage->head;
	ptr->size -= 1;
	//printf("%d popped\n", *ret);
	return true;
}

void release_stack_gen(stack_gen* ptr)
{
	release_linked_list_gen(ptr->storage);
	free(ptr);
}
#endif
