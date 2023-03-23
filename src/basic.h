#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include "link.h"

#ifndef BASICS_TOKEN___
#define BASICS_TOKEN___
void swap (int* a, int*b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

double power (double x, int n)
{
	return n==0 ? 1 : x * power(x, n-1);
}

int factorial (int n)
{
	return n==0 ? 1 : n * factorial(n-1);
} 

LL* get_binary (int n)
{
	LL* ptr = get_linked_list();
	while (n)
	{
		add_head(ptr, n%2);
		n /= 2;
	}
	//print_LL(ptr);
	return ptr;
}

int len_str (char* str)
{
	int i = 0;
	while (str[i++] != '\0');
	return --i;
}

int copy_str (char* src, char* dst)
{
	int len = len_str(src);
	for (int i = 0; i <= len; i++)
		dst[i] = src[i];
	return len;
}

char* make_lc_str (char* str)
{
	int len = len_str (str);
	for (int i =0; i < len; i++)
		if (str[i]>='A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
	return str;
}

int same_str (char* str1, char* str2)
{
	int len = len_str (str1);
        if (len != len_str (str2))
		return 0;

	for(int i=0; i < len; i++)
	{
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

int cmp_str (char* str1, char* str2)
{
	int len1 = len_str (str1);
	int len2 = len_str (str2);
	int len = len1>len2? len2 : len1;
	for(int i=0; i <= len; i++)
	{
		if (str1[i] != str2[i])
			return str1[i]-str2[i];
	}
	return 0;
}

/*int fib (int n)
{
	static int *A = (int*)malloc(n * sizeof(int));;
	if (n==1 || n==2)
		A[n] = n;
	if (!A[n])
		A[n] = fib[n-1] + fib[n-2];
	int res = A[n];
	free(A);
	return res;
}
*/
#endif
