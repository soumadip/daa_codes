#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include "basic.h"


#ifndef SORTING_TOKEN___
#define SORTING_TOKEN___

int partition(int* arr, int start, int end)
{
	int pivot = arr[end];
	int i = start - 1;
	for (int j = start; j<= end; ++j)
		if (arr[j] < pivot)
		{
			i++;
			swap (&arr[i], &arr[j]);
		}
	swap (&arr[i+1], &arr[end]);
	return i+1;
}

void quick_sort (int* arr, int start, int end)
{
	if (start < end)
	{
		int pivot = partition (arr, start, end);
		quick_sort(arr, start, pivot-1);
		quick_sort(arr, pivot+1, end);
	}
}

#define Left(i) ((2*(i))+1)
#define Right(i) ((2*(i))+2)
#define Parent(i) ((i)/2)
void heapify(int* arr, int size, int pos)
{
	int min = pos;
	if (Left(pos) < size && arr[Left(pos)] < arr[min])
		min = Left(pos);
	if (Right(pos) < size && arr[Right(pos)] < arr[min])
		min = Right(pos);
	if (min != pos)
	{
		swap (&arr[pos], &arr[min]);
		heapify (arr, size, min);
	}
}

void heap_sort (int* arr, int start, int end)
{
	int size = end - start + 1;

	for (int i=size/2-1; i >= 0; --i)
		heapify(arr, size, i);
	for (int i=size-1; i >= 0; --i)
	{
		swap (&arr[0], &arr[i]);
		heapify (arr, i, 0);
	}
}
#undef Left
#undef Right
#undef Parent

void merge (int* arr, int start1, int end1, int start2, int end2)
{
	int size1 = end1 - start1 + 1;
	int size2 = end2 - start2 + 1;
	int *tmp = (int*) malloc(sizeof(int)*(size1+size2));
	int i=start1, j=start2, k=0;
	do
		if (arr[i]<=arr[j])
			tmp[k++]= arr[i++];
		else
			tmp[k++]= arr[j++];
	while(i<=end1 && j <=end2);

	if (i > end1)
		while(j <= end2)
			tmp[k++]= arr[j++];
	else
		while(i <= end1)
			tmp[k++]= arr[i++];
	for (k=0; k < size1+size2; ++k)
		arr[start1+k] = tmp[k];
	free(tmp);
}
void merge_sort (int* arr, int start, int end)
{
	int size = end - start + 1;
	if (size == 1)
		return;
	else if (size == 2)
	{
		if (arr[start] > arr[end])
			swap(&arr[start], &arr[end]);
		return;
	}
	else
	{
		merge_sort(arr, start, start+size/2);
		merge_sort(arr, start+size/2+1, end);
		merge (arr, start, start+size/2, start+size/2+1, end);
	}
}

void bubble_sort (int* arr, int start, int end)
{
	for (int i=start; i<=end-1; i++)
		for (int j=start; j<=end-1-i; j++)
			if (arr[j] > arr[j+1])
				swap (&arr[j], &arr[j+1]);
}

void selection_sort (int* arr, int start, int end)
{
	for (int i=start; i<=end; i++)
	{
		int min = i;
		for (int j=i+1; j<=end; j++)
			if (arr[j] < arr[min])
				min = j;
		if (min != i)
			swap (&arr[min], &arr[i]);
	}
}

void insertion_sort (int* arr, int start, int end)
{
	for (int i=start; i<=end; i++)
	{
		int k = arr[i];
		int j = i-1;
		while (j>=0 && arr[j] > k)
		{
			arr[j+1] = arr[j];
			--j;
		}
		arr[j+1] = k;
	}
}

void counting_sort (int* arr, int start, int end)
{
	int min = INT_MAX, max = INT_MIN;
	for (int i=start; i<=end; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}
	int* A = (int*) calloc(max - min + 1,sizeof(int));
	int* O = (int*) malloc((max - min + 1)*sizeof(int));
	for (int i = start; i<=end; ++i)
		++A[arr[i] - min];
	for (int i = 1; i<=max-min+1; ++i)
		A[i] += A[i-1];
	for (int i = start; i<=end; ++i)
	{
		O[A[arr[i]-min]-1] = arr[i];
		--A[arr[i]-min];
	}
	for (int i = start; i<=end; ++i)
		arr[i] = O[i];
	free(O);
	free(A);
}

/*
void radix_custom_counting_sort (int* arr, int start, int end, int place)
{
	int size = end - start + 1;
	int min = INT_MAX, max = INT_MIN;
	for (int i=start; i<end; i++)
		if (arr[i] < min)
			min = arr[i];
		else if (arr[i] > max)
			max = arr[i];
	int* A = (int*) calloc(max - min + 1,sizeof(int));
	int* O = (int*) malloc((max - min + 1)*sizeof(int));
	for (int i = start; i<end; ++i)
		++A[arr[i]-min];
	for (int i = start+1; i<end; ++i)
		A[i-min] += A[i-1-min];
	for (int i = start; i<end; ++i)
	{
		O[A[arr[i]-min]-1] = arr[i];
		--A[arr[i]-min];
	}
	for (int i = start; i<end; ++i)
		arr[i] = O[i];
	free(O);
	free(A);
}
void radix_sort (int* arr, int start, int end)
{
	int max = INT_MIN;
	int size = end - start + 1;
	for (int i = start; i<end; ++i)
		if(max < arr[i])
			max = arr[i];
	int place = 1;
	while (max/place > 0)
	{
		radix_custom_counting_sort(arr, start, end, place);
		place *= 10;
	}
}
*/
#endif
