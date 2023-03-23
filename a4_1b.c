#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<stdbool.h>
#include "src/searching.h"
#include "src/basic.h"


bool unbounded_search(double (*f) (int), int target, int* ret)
{
	int i = rand();
	double tmp, prev;
	int start, end;
	bool start_found = false, end_found = false;
	while (true)
	{
		tmp = (*f)(i);
		if (tmp == target)
		{
			*ret = tmp;
			return true;
		}
		if(tmp > target) 
			(end_found = true) && (end = i) && (i /= 2);
		else 
			(start_found = true) && (start = i) && (i *= 2);
		if (start_found && end_found)
			break;
	}
	//do binary search now
	while (true)
	{
		if (end < start)
			return false;
		int mid = (start + end)/2;
		tmp = (*f)(mid); 
		prev = (*f)(mid-1); 
		if (prev < target && tmp >= target)
		{
			*ret = mid;
			return true;
		}
		else if (target > tmp)
			start = mid+1;
		else if (target < tmp)
			end = mid-1;		
	}
}

int main ()
{
	time_t t;
	int ret;
	srand((unsigned) time(&t));

	double fn (int x)
	{
		return power (x, 3) - 10 * power (x, 2) - 15 * x - 20;
	}

	if (unbounded_search (&fn, 1000, &ret))
		printf ("Found at %d", ret);
	else
		printf ("Not found");
}
