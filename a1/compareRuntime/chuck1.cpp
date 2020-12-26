// Program to measure the time taken by the solution on site vs solution by me

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
     
clock_t start, end;
double cpu_time_used;
     

typedef struct {
   int top;
   int *body;
} stack;

stack sinit ( int n )
{
   stack S;

   S.body = (int *)malloc(n * sizeof(int));
   S.top = -1;
   return S;
}

stack spush ( stack S, int x )
{
   S.body[++(S.top)] = x;
   return S;
}

stack spop ( stack S )
{
   --(S.top);
   return S;
}

/* The following two functions generate random sequences for testing.
   These are not part of the assignment. */

/* This function is based on the bijection between the set of stacky
   sequences and the set of paths through an n x n grid. */
int *genstacky ( int n )
{
   int i, j, a, *A;
   char move;
   stack S;

   A = (int *)malloc(n * sizeof(int));
   S = sinit(n);
   i = j = 0; a = 1;
   while ((i < n) || (j < n)) {
      if (i == n) move = 'V';
      else if (i == j) move = 'H';
      else move = (rand() % 3) ? 'H' : 'V';
      if (move == 'H') {
         S = spush(S,a);
         ++a; ++i;
      } else {
         A[j] = S.body[S.top];
         S = spop(S);
         ++j;
      }
   }
   return A;
}

/* For not-so-small n, a random sequence is unalgolicious with high probability. */
int *genrand ( int n )
{
   int *A, i, j, k, t;

   A = (int *)malloc(n * sizeof(int));
   for (i=0; i<n; ++i) A[i] = i+1;
   for (k=0; k<n; ++k) {
      i = rand() % n; j = rand() % n;
      t = A[i]; A[i] = A[j]; A[j] = t;
   }
   return A;
}

/* End of input generator */


/* The O(n)-time algorithm is based on the fact that the input sequence is
   stacky if and only if it does not contain an improper placement of any
   triple. So we try to realize the input sequence using a stack. If the
   realization fails at some point, the input is not stacky. If the realization
   proceeds until completion, the input is stacky. */
int method3 ( int *A, int n )
{
   stack S;
   int i, a;

   S = sinit(n);
   a = 1;
   for (i=0; i<n; ++i) {
      while (a <= A[i]) {
         S = spush(S,a);
         ++a;
      }
      if (S.top == -1) return 0;
      if (S.body[S.top] != A[i]) return 0;
      S = spop(S);
   }
   return 1;
}

bool method4(int *s, int n) {
	bool occured[n+1];

	for (int i = 1; i <=n; i++) {
		occured[i] = false;
	}

	for (int i = 0; i < n-2; i++) {
		occured[s[i]] = true;
		if (s[i+1] > s[i]) continue;
		if (s[i] - s[i+1] == 1) continue;
		for (int p = s[i+1] + 1; p < s[i]; p++) {
			if ( occured[p] == false ) return false;
		}
	}
	return true;
}

int main ( int argc, char *argv[] )
{
   int i, n, *A, *B;

   srand((unsigned int)time(NULL));

   if (argc > 1) n = atoi(argv[1]); else scanf("%d", &n);
   printf("n = %d\n", n);

   A = genstacky(n);
   printf("\n");

   start = clock();
   int op = method3(A, n);
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("    Method 3: %s.. done in %lf secs\n", op ? "Algolicious" : "Unalgolicious", cpu_time_used);

   start = clock();
   bool po = method4(A, n);
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("    Method 4: %s.. done in %lf secs\n", po ? "Algolicious" : "Unalgolicious", cpu_time_used);

   B = genrand(n);
   printf("\n");

   start = clock();
   op = method3(B, n);
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("    Method 3: %s.. done in %lf secs\n", op ? "Algolicious" : "Unalgolicious", cpu_time_used);

   start = clock();
   po = method4(B, n);
   end = clock();
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("    Method 4: %s.. done in %lf secs\n", po ? "Algolicious" : "Unalgolicious", cpu_time_used);

   return 0;
}
