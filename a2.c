#include<stdlib.h>
#include<time.h>
#include "src/spanning.h"

void scan_graph (AM_G2** am_g, AL_G2** al_g, char fname[])
{
	FILE* fp = fopen(fname, "r");
	int u, v, n;
	fscanf(fp, "%d", &n);
	*am_g = get_AM_graph2(n);
	*al_g = get_AL_graph2(n);
	while(!feof(fp))
	{
		fscanf(fp, "%d %d", &u, &v);
		int w = 1+rand()%99;
		add_AM_edge2 (*am_g, u, v, w);
		add_AL_edge2 (*al_g, u, v, w);
	}
	print_AM2(*am_g);
	print_AL2(*al_g);
	fclose(fp);
}

int main ()
{
	time_t t;
	srand((unsigned) time (&t));

	AM_G2 *g1;
	AL_G2 *g2;

	scan_graph(&g1, &g2, "input_graph.txt");

	printf("TREE WEIGHT:: %d\n", prims_AM(g1,0));
	//kruskals_AM(g1);
	
	//prims_AL(g2,0);
	printf("TREE WEIGHT:: %d\n", kruskals_AL(g2));

	release_AM_graph2 (g1);
	release_AL_graph2 (g2);
}
