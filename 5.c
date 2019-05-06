#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 3
#define NCA 3

int main (int argc, char *argv[])
{
int    tid, nthreads, i, j, k, chunk;
double    a[NRA][NCA];

chunk = 10;
#pragma omp parallel shared(a,nthreads,chunk) private(tid,i,j,k)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Starting with %d threads\n",nthreads);
    }
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;
  printf("Thread %d starting row addition...\n",tid);
  #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    {
      double sum1=0;
    printf("Thread=%d did row=%d\n",tid,i);
    for (k=0; k<NCA; k++)
        sum1+=a[i][k];
    printf("sum of %d row is %f",i+1,sum1);
    }

    printf("Thread %d starting column...\n",tid);
    #pragma omp for schedule (static, chunk)
  for (i=0; i<NRA; i++)
    {
      double sum1=0;
    printf("Thread=%d did column=%d\n",tid,i);
    for (k=0; k<NCA; k++)
        sum1+=a[k][i];
      printf("sum of %d column is %f",i+1,sum1);
    }
  }
}