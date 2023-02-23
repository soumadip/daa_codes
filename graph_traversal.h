#include<stdio.h>
#include "stack.h"
#include "queue.h"
#include "graph.h"

#ifndef TRAVERSAL_TOKEN___
#define TRAVERSAL_TOKEN___
void dfs_AM (AM_G* g, int st)
{
	stack *s = get_stack (g->size);
	int* visited = (int*)calloc(g->size, sizeof(int));
	int* neigh = (int*)malloc(sizeof(int)*g->size);
	push(s, st);
	visited[st] = 1;
	printf("[AM]DFS:: ");
	while(!is_stack_empty(s))
	{
		int u;
		pop(s, &u);
		int count = get_neighbors_AM (g, u, neigh);
		for (int i = 0; i <count; i++)
			if (!visited[neigh[i]])
			{
				push(s, neigh[i]);
				visited[neigh[i]] = 1;
			}
		printf("%d ", u);
	}
	printf("\n");
	free(visited);
	free(neigh);
	release_stack(s);
}

void bfs_AM (AM_G* g, int st)
{
	queue *q = get_queue (g->size);
	int* visited = (int*)calloc(g->size, sizeof(int));
	int* neigh = (int*)malloc(sizeof(int)*g->size);
	insert(q, st);
	visited[st] = 1;
	printf("[AM]BFS:: ");
	while(!is_queue_empty(q))
	{
		int u;
		delete(q, &u);
		int count = get_neighbors_AM (g, u, neigh);
		for (int i = 0; i <count; i++)
			if (!visited[neigh[i]])
			{
				insert(q, neigh[i]);
				visited[neigh[i]] = 1;
			}
		printf("%d ", u);
	}
	printf("\n");
	free(visited);
	free(neigh);
	release_queue(q);
}
void dfs_AL (AL_G* g, int st)
{
	stack *s = get_stack (g->size);
	int* visited = (int*)calloc(g->size, sizeof(int));
	int* neigh = (int*)malloc(sizeof(int)*g->size);
	push(s, st);
	visited[st] = 1;
	printf("[AL]DFS:: ");
	while(!is_stack_empty(s))
	{
		int u;
		pop(s, &u);
		int count = get_neighbors_AL (g, u, neigh);
		for (int i = 0; i <count; i++)
			if (!visited[neigh[i]])
			{
				push(s, neigh[i]);
				visited[neigh[i]] = 1;
			}
		printf("%d ", u);
	}
	printf("\n");
	free(visited);
	free(neigh);
	release_stack(s);
}

void bfs_AL (AL_G* g, int st)
{
	queue *q = get_queue (g->size);
	int* visited = (int*)calloc(g->size, sizeof(int));
	int* neigh = (int*)malloc(sizeof(int)*g->size);
	insert(q, st);
	visited[st] = 1;
	printf("[AL]BFS:: ");
	while(!is_queue_empty(q))
	{
		int u;
		delete(q, &u);
		int count = get_neighbors_AL (g, u, neigh);
		for (int i = 0; i <count; i++)
			if (!visited[neigh[i]])
			{
				insert(q, neigh[i]);
				visited[neigh[i]] = 1;
			}
		printf("%d ", u);
	}
	printf("\n");
	free(visited);
	free(neigh);
	release_queue(q);
}
#endif
