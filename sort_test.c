#include<stdio.h>
#include "sorting.h"

void print (int* arr, int size)
{
	for (int  i=0; i<size; i++)
		printf ("%d  ", arr[i]);
	printf ("\n");
}

int main ()
{
	int arr[] = {10,25,1,5,4,16,9,8,1,5,15,1,81,9,22,5,456,6,4,56,5,5};

	int size = sizeof arr / sizeof arr[0];
	
	print (arr, size);
	//bubble_sort(arr, 0, size-1);
	//insertion_sort(arr, 0, size-1);
	//selection_sort(arr, 0, size-1);
	//counting_sort(arr, 0, size-1);
	//merge_sort(arr, 0, size-1);
	//quick_sort(arr, 0, size-1);
	heap_sort(arr, 0, size-1);
	print(arr, size);

}
