#include "graph_traversal.h"

void scan_graph (AM_G** am_g, AL_G** al_g)
{
	FILE* fp = fopen("input_graph.txt", "r");
	int u, v, n;
	fscanf(fp, "%d", &n);
	*am_g = get_AM_graph(n);
	*al_g = get_AL_graph(n);
	while(!feof(fp))
	{
		fscanf(fp, "%d %d", &u, &v);
		//if (add_AM_edge (*am_g, u, v))
		//	printf("AM edge %d -- %d added\n", u, v);
		//if (add_AL_edge (*al_g, u, v))
		//	printf("AL edge %d -- %d added\n", u, v);
		add_AM_edge (*am_g, u, v);
		add_AL_edge (*al_g, u, v);
	}
	print_AM(*am_g);
	print_AL(*al_g);
	fclose(fp);
}

int main ()
{
	AM_G *g1;
	AL_G *g2;

	scan_graph(&g1, &g2);

	dfs_AM(g1,0);
	bfs_AM(g1,0);
	
	dfs_AL(g2,0);
	bfs_AL(g2,0);

	release_AM_graph(g1);
	release_AL_graph(g2);
}
