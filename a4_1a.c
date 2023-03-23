#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "src/searching.h"

bool rotated_binary_search(int* arr, int start, int end, int key, int* ret_idx)
{
	int size = end - start + 1;
	int mid = (start + end) / 2;
	bool first_half_sorted;

	if (size <= 0)
		return false;

	if (arr[mid] == key)
	{
		*ret_idx = mid;
		return true;
	}
	else if (size == 1) 
		return false;
	else
	{
		if (arr[start] < arr[mid])
			first_half_sorted = true;
		else
			first_half_sorted = false;
		if (key > arr[mid] || key < arr[start])
			if (first_half_sorted)
				return rotated_binary_search (arr, mid+1, end, key, ret_idx);
			else
				return binary_search (arr, mid+1, end, key, ret_idx);
		else 
			if (first_half_sorted)
				return binary_search (arr, start, mid-1, key, ret_idx);
			else
				return rotated_binary_search (arr, start, mid-1, key, ret_idx);
	}
}

int main()
{
	FILE* fp = fopen("inp_arr_rotated.txt", "r");

	int n, t, key, ind;
	int *arr;
	fscanf(fp, "%d", &t); //number of testcases/search-items
	fscanf(fp, "%d", &n); //number of elements of the array;

	arr = (int*)malloc(n*sizeof(int));
	printf ("INPUT ARRAY:: ");
	for (int i=0; i<n; ++i)
	{
		fscanf(fp, "%d", &arr[i]);
		printf ("[%d] %d ", i, arr[i]);
	}
	printf("\n");

	for (int i = 1; i <= t; ++i)
	{
		fscanf (fp, "%d", &key);
		printf ("testcase #%d\n\tsearhing for %d", i, key);

		if (rotated_binary_search(arr, 0, n-1, key, &ind))
			printf("\t...item found at location %d\n", ind);
		else
			printf("\t...item not found\n");
	}

	free(arr);
	fclose(fp);
	return 1;
}
