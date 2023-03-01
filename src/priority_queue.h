#include "basic.h"


typedef struct _heap_node
{
	void* data;
	struct _heap_node* parent;
	struct _heap_node* left;
	struct _heap_node* right;
}heap_node;

typedef struct 
{
	heap_node* ROOT;
	heap_node** next_pos;
	heap_node* next_pos_parent;
	int (*eval_priority)(void*);
	int height;
	int size;
	int max_size;
	char type_of_heap[8]; //min, max
}heap;

heap_node* get_heap_node (void* data)
{
	heap_node* ptr = (heap_node*)malloc(sizeof(heap_node));
	ptr->data = data;
	ptr->left = ptr->right = ptr->parent = NULL;

	return ptr;
}

heap* get_heap(int max_size, char type[], int(*eval)(void*))
{
	heap* ptr = (heap*) malloc(sizeof(heap));
	ptr->max_size = max_size;
	ptr->eval_priority = eval;
	ptr->size = 0;
	ptr->height = 0;
	ptr->ROOT = NULL;
	ptr->next_pos = NULL;
	ptr->next_pos_parent = NULL;
	copy_str (make_lc_str (type), ptr->type_of_heap);

	return ptr;
}

void release_heap (heap* ptr)
{
	void del(heap_node* ptr)
	{
		if(ptr->left)
			del(ptr->left);
		if(ptr->right)
			del(ptr->right);
		free(ptr->data);
		free(ptr);
	}
	if(ptr && ptr->ROOT)
		del(ptr->ROOT);
	free(ptr);
}

void print_pre_order(heap_node* ptr, int(*f)(void*), int level)
{
	if(ptr)
	{
		printf(" %d(%d) ", (*f)(ptr->data), level);
		print_pre_order(ptr->left, f, level+1);
		print_pre_order(ptr->right, f, level+1);
	}
}

void print_heap(heap* ptr)
{
	int(*fun)(void*) = ptr->eval_priority;
	print_pre_order(ptr->ROOT, fun, 0);
	printf("\n");
}

void find_next_pos(heap* ptr)
{
	ptr->next_pos = &(ptr->ROOT);
	LL* lptr = get_binary(ptr->size + 1);
	node* tmp_lptr = lptr->head->next;
	while (tmp_lptr)
	{
		ptr->next_pos_parent = *(ptr->next_pos);
		ptr->next_pos = tmp_lptr->val ? &(ptr->next_pos_parent->right) :  &(ptr->next_pos_parent->left);
		tmp_lptr = tmp_lptr->next;
	}
	release_linked_list (lptr);
}

void min_heapify_upward (heap* ptr)
{
	int(*fun)(void*) = ptr->eval_priority;

	heap_node* tmp = *(ptr->next_pos);
	while (tmp->parent)
	{
		if((*fun)(tmp->data) < (*fun)(tmp->parent->data))
		{
			void* tmp_data = tmp->data;
			tmp->data = tmp->parent->data;
			tmp->parent->data = tmp_data;
			tmp = tmp->parent;
		}
		else
			break;
	}
}

void min_heapify_downward (heap* ptr)
{
	int(*fun)(void*) = ptr->eval_priority;

	heap_node* tmp = ptr->ROOT;
	heap_node* target;
	while (tmp)
	{
		if(tmp->left && (*fun)(tmp->data) > (*fun)(tmp->left->data))
		{
			if(tmp->right && (*fun)(tmp->left->data) > (*fun)(tmp->right->data))
				target = tmp->right;
			else
				target = tmp->left;
		}
		else if(tmp->right && (*fun)(tmp->data) > (*fun)(tmp->right->data))
			target = tmp->right;
		else
			target = NULL;

		if(target)
		{
			void* tmp_data = tmp->data;
			tmp->data = target->data;
			target->data = tmp_data;
			tmp = target;
		}
		else
			break;
	}
}

bool add_to_heap (heap* ptr, void* data)
{
	if (ptr->size == ptr->max_size)
		return false;
	if (ptr->next_pos)
	{
		*(ptr->next_pos) = get_heap_node (data);
		(*(ptr->next_pos))->parent = ptr->next_pos_parent;
		if (same_str(ptr->type_of_heap, "min"))
				min_heapify_upward (ptr);
	}
	else
	{
		ptr->ROOT = get_heap_node(data);
	}
	ptr->size += 1;
	if (ptr->size == power (2, ptr->height))
		ptr->height += 1;
	find_next_pos (ptr);
	return true;
}

void* extract_root (heap* ptr)
{
	if (ptr->ROOT == NULL)
		return NULL;
	void* ret = ptr->ROOT->data;
	heap_node *last = ptr->ROOT, *last_par;
	LL* lptr = get_binary(ptr->size);
	node* tmp_lptr = lptr->head->next;
	while (tmp_lptr)
	{
		last_par = last;
		last = tmp_lptr->val ? last_par->right : last_par->left;
		tmp_lptr = tmp_lptr->next;
	}
	release_linked_list (lptr);
	ptr->ROOT->data = last->data;
	if (same_str(ptr->type_of_heap, "min"))
			min_heapify_downward(ptr);
	ptr->size -= 1;
	if (last_par->left == last)
		last_par->left = NULL;
	else
		last_par->right = NULL;
	if (ptr->size == 0)
		ptr->ROOT = NULL;
	free(last);
	find_next_pos(ptr);
	return ret;
}
