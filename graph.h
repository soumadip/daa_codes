#include<stdbool.h>
#include<stdlib.h>
#include "link.h"

#ifndef GRAPH_TOKEN__
#define GRAPH_TOKEN__
typedef struct ADJ_MATRIX_GRAPH
{
	int** adj;
	int size;
	int n_edges;
}AM_G;

typedef struct ADJ_LIST_GRAPH
{
	LL** adj;
	int size;
	int n_edges;
}AL_G;


AM_G* get_AM_graph (int n)
{
	AM_G* ptr = (AM_G*)malloc(sizeof(AM_G));

	ptr->size = n;
	ptr->adj = (int**)malloc(sizeof(int*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = (int*) calloc(ptr->size, sizeof(int));
	ptr->n_edges = 0;

	return ptr;
}

AL_G* get_AL_graph (int n)
{
	AL_G* ptr = (AL_G*)malloc(sizeof(AL_G));

	ptr->size = n;
	ptr->adj = (LL**) malloc(sizeof(LL*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = get_linked_list();
	ptr->n_edges = 0;

	return ptr;
}

bool add_AM_edge (AM_G* ptr, int u, int v)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;

	ptr->adj[u][v] = ptr->adj[v][u] = 1;
	ptr->n_edges += 2;
	return true;
}

bool add_AL_edge (AL_G* ptr, int u, int v)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;
	
	add_tail (ptr->adj[u], v);
	add_tail (ptr->adj[v], u);
	ptr->n_edges += 2;
	return true;
}

int get_neighbors_AM (AM_G* ptr, int u, int* arr)
{
	int count = 0;
	for (int i=0; i < ptr->size; i++)
		if (ptr->adj[u][i] != 0)
			arr[count++] = i;
	return count;
}

int get_neighbors_AL (AL_G* ptr, int u, int* arr)
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

void print_AM (AM_G* ptr)
{
	for (int i=0; i < ptr->size; ++i)
	{
		for (int j=0; j < ptr->size; ++j)
			printf("%d ", ptr->adj[i][j]);
		printf ("\n");
	}
}

void print_AL (AL_G* ptr)
{
	for (int i=0; i < ptr->size; ++i)
	{
		printf("[%d] ", i);
		print_LL(ptr->adj[i]);
	}
}

void release_AM_graph(AM_G* ptr)
{
	for (int i=0; i < ptr->size; i++)
		free(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}

void release_AL_graph(AL_G* ptr)
{
	for (int i=0; i < ptr->size; i++)
		release_linked_list(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}
#endif
