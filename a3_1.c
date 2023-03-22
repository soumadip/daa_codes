#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
   double hi;
   double lo;
} two_val;

double lorec ( int n );

double hirec ( int n )
{
	return n==0 ? 1 : 2*hirec(n-1)+lorec(n-1);
}

double lorec ( int n )
{
	return n==0 ? 0 : hirec(n-1)+lorec(n-1);
}

two_val hilorec ( int n )
{
   two_val N, ret;
   if (n==0)
   {
	   ret.hi = 1;
	   ret.lo = 0;
   }
   else
   {
	   N = hilorec(n-1);
	   ret.hi = 2*N.hi + N.lo;
	   ret.lo = N.hi + N.lo;
   }
   return ret;
}

two_val hiloformula ( int n )
{
   two_val ret;

   double sqrt5 = sqrt(5);
   ret.hi = (5+sqrt5)/10*pow((3-sqrt5)/2, n+1) + (5-sqrt5)/10*pow((3+sqrt5)/2, n+1);
   ret.lo = (-5-3*sqrt5)/10*pow((3-sqrt5)/2, n+1) + (-5+3*sqrt5)/10*pow((3+sqrt5)/2, n+1);

   return ret;
}

int main ( int argc, char *argv[] )
{
   two_val N1, N2, N3;
   int n;

   clock_t start, end;
   double time_taken;

   scanf("%d", &n);
   printf("n = %d\n", n);

   printf("\n+++ Method 0\n");
   start = clock();
   N1.hi = hirec(n); N1.lo = lorec(n);
   end = clock();
   printf("    hi(%d) = %.10le, lo(%d) = %.10le\n", n, N1.hi, n, N1.lo);
   time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
   printf("Method 0 took %f seconds to execute \n", time_taken);

   printf("\n+++ Method 1\n");
   start = clock();
   N2 = hilorec(n);
   end = clock();
   printf("    hi(%d) = %.10le, lo(%d) = %.10le\n", n, N2.hi, n, N2.lo);
   time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
   printf("Method 1 took %f seconds to execute \n", time_taken);

   printf("\n+++ Method 2\n");
   start = clock();
   N3 = hiloformula(n);
   end = clock();
   printf("    hi(%d) = %.10le, lo(%d) = %.10le\n", n, N3.hi, n, N3.lo);
   time_taken = ((double) (end - start))/CLOCKS_PER_SEC;
   printf("Method 2 took %f seconds to execute \n", time_taken);

   exit(0);
}

