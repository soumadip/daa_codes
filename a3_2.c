#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "src/stack.h"

int method0 ( int *A, int n )
{
	for (int a=1; a<=n; ++a)
		for (int b=a+1; b<=n; ++b)
			for (int c=b+1; c<=n; ++c)
			{
				int i, j, k;
				for (int x=0; x<n; ++x)
					if (A[x] == a) 
						j=x;
					else if (A[x] == b) 
						k=x;
					else if (A[x] == c) 
						i=x;
				if (i<j && j<k)
					return 0;
			}
	return 1;
}

int method1 ( int *A, int n )
{
	for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
			for (int k=j+1; k<n; ++k)
			{
				int a = A[j], b = A[k], c = A[i];
				if (a<b && b<c)
					return 0;
			}
	return 1;
}

int method2 ( int *A, int n )
{
	for(int i=0; i<n; ++i)
	{
		int last = A[i];
		for(int j=i+1; j<n; ++j)
			if(A[i] > A[j])
			{
				if (A[j] > last)
					return 0;
				last = A[j];
			}
	}
	return 1;
}

int method3 ( int *A, int n )
{
	stack* sptr = get_stack(n);
	int a=1, top;

	for (int i=0; i<n; ++i) {
		while (a <= A[i]) {
			push(sptr, a);
			++a;
		}
		if (is_stack_empty(sptr)) return 0;
		pop(sptr, &top);
		if (top != A[i]) return 0;
	}

	release_stack(sptr);
	return 1;
}

int method4 ( int *A, int n )
{
	return method3(A, n);
}

void evaluate (int* A, int n)
{
	clock_t start, end;
	double time_taken;

	printf("\n+++ Method 0\n");
	start = clock();
	printf("    Method 0: %s\n", method0(A,n) ? "Valid" : "Invalid");
	end = clock();
	time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
	printf("Method 0 took %f seconds to execute \n", time_taken);

	printf("\n+++ Method 1\n");
	printf("    Method 1: %s\n", method1(A,n) ? "Valid" : "Invalid");
	start = clock();
	end = clock();
	time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
	printf("Method 1 took %f seconds to execute \n", time_taken);

	printf("\n+++ Method 2\n");
	start = clock();
	printf("    Method 2: %s\n", method2(A,n) ? "Valid" : "Invalid");
	end = clock();
	time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
	printf("Method 2 took %f seconds to execute \n", time_taken);

	printf("\n+++ Method 3\n");
	start = clock();
	printf("    Method 3: %s\n", method3(A,n) ? "Valid" : "Invalid");
	end = clock();
	time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
	printf("Method 3 took %f seconds to execute \n", time_taken);

	printf("\n+++ Method 4\n");
	start = clock();
	printf("    Method 4: %s\n", method4(A,n) ? "Valid" : "Invalid");
	end = clock();
	time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
	printf("Method 4 took %f seconds to execute \n", time_taken);
}

int main ( int argc, char *argv[] )
{
	int i, j=0, n, t, *A;
	bool invalid = false;


	scanf("%d", &t); //t is the number of testcases, provided as first input
	while (++j<=t)
	{
		//scan the input
		scanf("%d", &n); //n is the number of elements for some testcase/sequence

		A = (int*) malloc (sizeof(int)*n);
		for (i=0; i<n; ++i) //scan n elements of the sequence
		{
			scanf(" %d", &A[i]); 
			if (A[i] > n || A[i] <= 0) invalid = true;
		}

		if (invalid)
		{
			printf("\n\nSeq(%d) <<invalid testcase>> \n", j);
			free(A);
			invalid = false;
			continue;
		}
		printf("\n\nSeq(%d)::\n", j);
		for (i=0; i<n; ++i) printf(" %d ", A[i]);
		printf("\n");

		evaluate(A, n);

		free(A);
	}
   exit(0);
}

