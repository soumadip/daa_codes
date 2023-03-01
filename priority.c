#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"

typedef struct
{
	int val;
	int prio;
}two_val;

int prio (void* ptr)
{
	two_val *tptr = (two_val*)ptr;
	return tptr->prio;
}

int main ()
{
	time_t t;
	srand ( (unsigned) time (&t));
	heap* hptr = get_heap(20, "min", &prio);

	for (int i = 0; i<18; i++)
	{
		two_val* ptr = (two_val*)malloc(sizeof(two_val));
		ptr->val = i;
		ptr->prio = rand()%10;
		if(add_to_heap (hptr, ptr))
			printf("%d %d inserted\n", ptr->val, ptr->prio);
	}
	//print_heap(hptr);
	do
	{
	two_val* tv = (two_val*)extract_root(hptr);
	if(tv) 
	{
		printf("%5d %5d\n", tv->val, tv->prio);
		free(tv);
	}
	else
		break;
	//print_heap(hptr);
	}while(true);
	release_heap(hptr);
	return 0;
}
