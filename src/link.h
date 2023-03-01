#include<stdbool.h>
#include<stdlib.h>

#ifndef LIST_TOKEN__
#define LIST_TOKEN__
typedef struct _node
{
	int val;
	struct _node* next;
}node;

typedef struct
{
	node* head;
	node* tail;
	int size;
}LL;

node* get_node (int val)
{
	node* ptr = (node*) malloc(sizeof(node));
	ptr->val = val;
	ptr->next = NULL;
}

LL* get_linked_list ()
{
	LL* ptr = (LL*)malloc (sizeof(LL));
	ptr->head = ptr->tail = NULL;
	ptr->size = 0;
}

bool is_list_empty (LL* ptr)
{
	return ptr->size == 0;
}

bool add_head (LL* ptr, int val)
{
	node* tmp = ptr->head;
	node* v = get_node(val);
	if (!v)
		return false;
	if (is_list_empty(ptr))
		ptr->head = ptr->tail = v;
	else
	{
		v->next = ptr->head;
		ptr->head = v;
	}
	ptr->size += 1;
	return true;
}

bool add_tail (LL* ptr, int val)
{
	node* v;

	v = get_node(val);
	if (!v)
		return false;
	if (is_list_empty(ptr))
		ptr->head = ptr->tail = v;
	else
	{
		ptr->tail->next = v;
		ptr->tail = v;
	}
	ptr->size += 1;
	return true;
}

bool del_head (LL* ptr, int* ret)
{
	if (is_list_empty(ptr))
		return false;
	
	node* tmp;
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
bool del_tail (LL* ptr, int *ret)
{
	if (!is_list_empty(ptr))
		return false;

	node* tmp = ptr->head;
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

void print_LL(LL* ptr)
{
	node* tmp = ptr->head;
	printf("--> ");
	while(tmp != ptr->tail)
	{
		printf ("%d --> ", tmp->val);
		tmp=tmp->next;
	}
	printf("%d\n", ptr->tail->val);
}

void release_linked_list(LL* ptr)
{
	node* tmp = ptr->head;
	while (tmp)
	{
		tmp = ptr->head->next;
		free(ptr->head);
		ptr->head = tmp;
	}
	free(ptr);
}
#endif
