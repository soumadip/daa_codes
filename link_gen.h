#include<stdbool.h>
#include<stdlib.h>

#ifndef LIST_GEN_TOKEN__
#define LIST_GEN_TOKEN__
typedef struct _node_gen
{
	void* val;
	struct _node_gen* next;
}node_gen;

typedef struct
{
	node_gen* head;
	node_gen* tail;
	int size;
}LL_gen;

node_gen* get_node_gen (void* val)
{
	node_gen* ptr = (node_gen*) malloc(sizeof(node_gen));
	ptr->val = val;
	ptr->next = NULL;
}

LL_gen* get_linked_list_gen ()
{
	LL_gen* ptr = (LL_gen*)malloc (sizeof(LL_gen));
	ptr->head = ptr->tail = NULL;
	ptr->size = 0;
}

bool is_list_gen_empty (LL_gen* ptr)
{
	return ptr->size == 0;
}

bool add_head_gen (LL_gen* ptr, void* val)
{
	node_gen* tmp = ptr->head;
	node_gen* v = get_node_gen(val);
	if (!v)
		return false;
	if (is_list_gen_empty(ptr))
		ptr->head = ptr->tail = v;
	else
	{
		v->next = ptr->head;
		ptr->head = v;
	}
	ptr->size += 1;
	return true;
}

bool add_tail_gen (LL_gen* ptr, void* val)
{
	node_gen* v;

	v = get_node_gen(val);
	if (!v)
		return false;
	if (is_list_gen_empty(ptr))
		ptr->head = ptr->tail = v;
	else
	{
		ptr->tail->next = v;
		ptr->tail = v;
	}
	ptr->size += 1;
	return true;
}

bool del_head_gen (LL_gen* ptr, void** ret)
{
	if (is_list_gen_empty(ptr))
		return false;
	
	node_gen* tmp;
	*ret = ptr->head->val;
	tmp = ptr->head;
	ptr->head = ptr->head->next;
	free(tmp);
	ptr->size -= 1;
	if (ptr->head == NULL)
		ptr->tail = NULL;

	return true;
}

//O(n) operation this since singly list
bool del_tail_gen (LL_gen* ptr, void** ret)
{
	if (!is_list_gen_empty(ptr))
		return false;

	node_gen* tmp = ptr->head;
	*ret = ptr->tail->val;
	free(ptr->tail);
	if (ptr->tail == ptr->head)
		ptr->head = ptr->tail=NULL;
	else
	{
		while (tmp->next != ptr->tail)
			tmp = tmp->next;
		ptr->tail = tmp;
		ptr->tail->next = NULL;
	}
	ptr->size -= 1;
	return true;
}

void print_LL_gen(LL_gen* ptr, void(*f)(void*))
{
	node_gen* tmp = ptr->head;
	printf("--> ");
	while(tmp != ptr->tail)
	{
		(*f)(tmp->val);
		printf ("--> ");
		tmp=tmp->next;
	}
	(*f)(ptr->tail->val);
	printf("\n");
}

void release_linked_list_gen(LL_gen* ptr)
{
	node_gen* tmp = ptr->head;
	while (tmp)
	{
		tmp = ptr->head->next;
		if(ptr->head->val)
			free(ptr->head->val);
		free(ptr->head);
		ptr->head = tmp;
	}
	free(ptr);
}
#endif
