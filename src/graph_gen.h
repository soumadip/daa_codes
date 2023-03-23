#include<stdbool.h>
#include<stdlib.h>
#include "link_gen.h"

#ifndef GRAPH_GEN_TOKEN__
#define GRAPH_GEN_TOKEN__

typedef struct _GRAPH_NODE
{
	void* val;
	int id;
}vertex;

typedef struct ADJ_MATRIX_GRAPH_GEN
{
	vertex** adj;
	int size;
	int n_edges;
}AMG_G;

typedef struct ADJ_LIST_GRAPH
{
	LL_gen** adj;
	int size;
	int n_edges;
}ALG_G;


AMG_G* get_AMG_graph (int n)
{
	AMG_G* ptr = (AMG_G*)malloc(sizeof(AMG_G));

	ptr->size = n;
	ptr->adj = (int**)malloc(sizeof(int*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = (int*) calloc(ptr->size, sizeof(int));
	ptr->n_edges = 0;

	return ptr;
}

ALG_G* get_ALG_graph (int n)
{
	ALG_G* ptr = (ALG_G*)malloc(sizeof(ALG_G));

	ptr->size = n;
	ptr->adj = (LL_gen**) malloc(sizeof(LL_gen*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = get_linked_list_gen();
	ptr->n_edges = 0;

	return ptr;
}

bool add_AMG_edge (AMG_G* ptr, int u, int v)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;

	ptr->adj[u][v] = ptr->adj[v][u] = 1;
	ptr->n_edges += 2;
	return true;
}

bool add_ALG_edge (ALG_G* ptr, int u, int v)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;
	
	add_tail (ptr->adj[u], v);
	add_tail (ptr->adj[v], u);
	ptr->n_edges += 2;
	return true;
}

int get_neighbors_AMG (AMG_G* ptr, int u, int* arr)
{
	int count = 0;
	for (int i=0; i < ptr->size; i++)
		if (ptr->adj[u][i] != 0)
			arr[count++] = i;
	return count;
}

int get_neighbors_ALG (ALG_G* ptr, int u, int* arr)
{
	int count = 0;
	node* tmp = ptr->adj[u]->head;
	while (tmp)
	{
		arr[count++] = tmp->val;
		tmp = tmp->next;
	}
	return count;
}

void print_AMG (AMG_G* ptr)
{
	for (int i=0; i < ptr->size; ++i)
	{
		for (int j=0; j < ptr->size; ++j)
			printf("%d ", ptr->adj[i][j]);
		printf ("\n");
	}
}

void print_ALG (ALG_G* ptr)
{
	for (int i=0; i < ptr->size; ++i)
	{
		printf("[%d] ", i);
		print_LL_gen(ptr->adj[i]);
	}
}

void release_AMG_graph(AMG_G* ptr)
{
	for (int i=0; i < ptr->size; i++)
		free(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}

void release_ALG_graph(ALG_G* ptr)
{
	for (int i=0; i < ptr->size; i++)
		release_linked_list_gen(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}
#endif
