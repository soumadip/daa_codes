#include<stdbool.h>
#include<stdlib.h>

#ifndef SEARCHING_TOKEN___
#define SEARCHING_TOKEN___

bool linear_search (int* arr, int start, int end, int key, int* ret_idx)
{
	for (int i = start; i <= end; i++)
		if (arr[i] == key)
		{
			*ret_idx = i;
			return true;
		}
	return false;
}

bool binary_search(int* arr, int start, int end, int key, int* ret_idx)
{
	int size = end - start + 1;
	int mid = (start+end)/2;
	if (size <= 0)
		return false;
	
	if (arr[mid] == key)
	{
		*ret_idx = mid;
		return true;
	}
	
	if (arr[mid] > key)
		binary_search (arr, start, mid - 1, key, ret_idx);
	else
		binary_search (arr, mid + 1, end, key, ret_idx);
}

#endif
