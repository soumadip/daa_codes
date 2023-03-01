#include<stdio.h>
#include "priority_queue.h"
#include "graph2.h"

#ifndef SPANNING_TOKEN___
#define SPANNING_TOKEN___
int prims_AM (AM_G2* g, int st)
{
	int prio (void* ptr)
	{
		edge* e = (edge*)ptr;
		return e->weight;
	}

	heap *hptr = get_heap (g->n_edges, "min", &prio);
	int* in_tree = (int*)calloc(g->size, sizeof(int));
	void** neigh = (void**)malloc(sizeof(void*)*g->size);
	int result = 0, span_size = 0;;

	printf("Prim's\n%5c %5c %5c\n", 'u', 'v', 'w');
	in_tree[st] = 1;
	int n = get_neighbors_AM2(g, st, neigh);
	for (int i = 0; i < n; i++)
	{
		edge* e = (edge*)neigh[i];
		add_to_heap (hptr, e);
	}
	int nxt = st;
	do
	{
		edge* e_min = (edge*)extract_root(hptr);
		if (in_tree[e_min->j]) //cycle
		{
			free(e_min);
			continue;
		}

		in_tree[e_min->j] = 1;
		printf("%5d %5d %5d\n", e_min->i, e_min->j, e_min->weight);
		result += e_min->weight;

		nxt = e_min->j;		
		n = get_neighbors_AM2(g, nxt, neigh);
		for (int i = 0; i < n; i++)
		{
			edge* e = (edge*)neigh[i];
			add_to_heap (hptr, e);
		}
		free(e_min);
		if (++span_size == g->size - 1)
			break;
	}while(true);

	free(in_tree);
	free(neigh);
	release_heap(hptr);
	return result;
}

void prims_AL (AL_G2* g, int st)
{
	//to-do
	printf ("To be Implemented");
}

void kruskals_AM (AM_G2* g)
{
	//to-do
	printf ("To be Implemented");
}

int kruskals_AL (AL_G2* g)
{
	int prio (void* ptr)
	{
		edge* e = (edge*)ptr;
		return e->weight;
	}

	heap* hptr = get_heap(g->n_edges, "min", &prio);
	int* comp = (int*)calloc(g->size, sizeof(int));
	int comp_count = 0, span_size = 0;
	void** neigh = (void**) malloc(sizeof(void*)*g->size);
	for (int i = 0; i < g->size; i++)
	{
		int n = get_neighbors_AL2(g, i, neigh);
		for (int i = 0; i < n; i++)
		{
			edge* e = (edge*)neigh[i];
			add_to_heap (hptr, e);
		}
	}
	free(neigh);

	printf("Kruskal's\n%5c %5c %5c\n", 'u', 'v', 'w');
	int result=0;
	do
	{
		edge* e = (edge*)extract_root(hptr);
		if(!e) 
			break;

		//printf("%d~%d~%d\n", e->i, e->j, e->weight);
		if (comp[e->i] == 0 && comp[e->j] == 0)
			comp[e->i] = comp[e->j] = ++comp_count;
		else if (comp[e->i] == 0)
			comp[e->i] = comp[e->j];
		else if (comp[e->j] == 0)
			comp[e->j] = comp[e->i];
		else if (comp[e->i] != comp[e->j])
			for(int i = 0; i < g->size; i++)
			{	
				if(comp[i] == comp[e->i])
					comp[i] = comp[e->j];
			}
		else //cycle
			continue;

		//for(int i=0; i<g->size; i++)
		//	printf("%d--", comp[i]);
		printf("%5d %5d %5d\n", e->i, e->j, e->weight);
		result += e->weight;
		free(e);
		if(++span_size == g->size - 1)
			break;
	}while(true);

	printf("Done\n");
	release_heap(hptr);
	return result;
}
#endif
