#include <stdio.h>
#include <omp.h>

int row_sum(int a[],int n);
int col_sum(int n,int a[][n],int c);
int n,tid;

void main(){
	printf("Enter the size of Array:");
	scanf("%d",&n);
	int mat[n][n];
	int i,j;
	printf("Enter the matrix elements:");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&mat[i][j]);

	int chunk=1;
	#pragma omp parallel shared(mat,n,chunk) private(i,tid)
	{
		i=0;
		tid=omp_get_thread_num();
		#pragma omp for schedule(static,chunk)
		for(i=0;i<n;i++){
			printf("tid=%d	ROWSPAN of row %d : %d\n",tid, i+1,row_sum(&mat[i][0],n));
		}
		#pragma omp for schedule(static,chunk)
		for(i=0;i<n;i++){
			printf("tid=%d	COLUMNSPAN of column %d : %d\n",tid, i+1,col_sum(n,mat,i));
		}
	}
}

int col_sum(int n,int a[][n],int c){
	int sum=0,j=0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum)
		for(j=0;j<n;j++)
			sum+=a[j][c];
	}
	return sum;
}

int row_sum(int *a,int n){
	int i=0,sum=0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum)
		for(i=0;i<n;i++)
			sum+=a[i];
	}
	return sum;
}