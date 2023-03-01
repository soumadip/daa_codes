#include<stdbool.h>
#include<stdlib.h>
#include "link_gen.h"

#ifndef GRAPH2_TOKEN__
#define GRAPH2_TOKEN__
typedef struct ADJ_MATRIX_GRAPH2
{
	int** adj;
	int size;
	int n_edges;
}AM_G2;

typedef struct ADJ_LIST_GRAPH2
{
	LL_gen** adj;
	int size;
	int n_edges;
}AL_G2;

typedef struct
{
	int i, j, weight;
}edge;

AM_G2* get_AM_graph2 (int n)
{
	AM_G2* ptr = (AM_G2*)malloc(sizeof(AM_G2));

	ptr->size = n;
	ptr->adj = (int**)malloc(sizeof(int*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = (int*) calloc(ptr->size, sizeof(int));
	ptr->n_edges = 0;

	return ptr;
}

AL_G2* get_AL_graph2 (int n)
{
	AL_G2* ptr = (AL_G2*)malloc(sizeof(AL_G2));

	ptr->size = n;
	ptr->adj = (LL_gen**) malloc(sizeof(LL_gen*) * ptr->size);
	for (int i=0; i<n; ++i)
		ptr->adj[i] = get_linked_list_gen();
	ptr->n_edges = 0;

	return ptr;
}

bool add_AM_edge2 (AM_G2* ptr, int u, int v, int w)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;

	ptr->adj[u][v] = ptr->adj[v][u] = w;
	ptr->n_edges += 2;
	return true;
}

bool add_AL_edge2 (AL_G2* ptr, int u, int v, int w)
{
	if (u>=ptr->size || v>=ptr->size)
		return false;
	
	edge* e1 = (edge*)malloc(sizeof(edge));
	edge* e2 = (edge*)malloc(sizeof(edge));
	e1->i = u;	e2->i = v;
	e1->j = v;	e2->j = u;
	e1->weight = w;	e2->weight = w;
	add_tail_gen (ptr->adj[u], e1);
	add_tail_gen (ptr->adj[v], e2);
	ptr->n_edges += 2;
	return true;
}

int get_neighbors_AM2 (AM_G2* ptr, int u, void* arr[])
{
	int count = 0;
	for (int i=0; i < ptr->size; i++)
		if (ptr->adj[u][i] != 0)
		{
			edge* e = (edge*)malloc(sizeof(edge));
			e->i = u;
			e->j = i;
			e->weight = ptr->adj[u][i];
			arr[count++] = e;
		}
	return count;
}

int get_neighbors_AL2 (AL_G2* ptr, int u, void* arr[])
{
	int count = 0;
	node_gen* tmp = ptr->adj[u]->head;
	while (tmp)
	{
		arr[count++] = tmp->val;
		tmp = tmp->next;
	}
	return count;
}

void print_AM2 (AM_G2* ptr)
{
	for (int i=0; i < ptr->size; ++i)
	{
		for (int j=0; j < ptr->size; ++j)
			printf("%4d ", ptr->adj[i][j]);
		printf ("\n");
	}
}

void print_AL2 (AL_G2* ptr)
{
	void print_edge(void* val)
	{
		edge* ptr = (edge*)val;
		printf ("(%2d, %2d, %3d)", ptr->i, ptr->j, ptr->weight);
	}
	for (int i=0; i < ptr->size; ++i)
	{
		printf("[%d] ", i);
		print_LL_gen(ptr->adj[i], &print_edge);
	}
}

void release_AM_graph2 (AM_G2* ptr)
{
	for (int i=0; i < ptr->size; i++)
		free(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}

void release_AL_graph2 (AL_G2* ptr)
{
	for (int i=0; i < ptr->size; i++)
		release_linked_list_gen(ptr->adj[i]);
	free(ptr->adj);
	free(ptr);
}
#endif
