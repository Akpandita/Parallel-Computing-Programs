#include <stdio.h>
#include <omp.h>

void main(){
	int n;
	float p_s,inc,i_s;
	printf("Enter the no. of employees:");
	scanf("%d",&n);
	int emp[n][2];
	for(int i=0;i<n;i++){
		printf("Enter employee %d data:\n",i);
		scanf("%d %d",&emp[i][0],&emp[i][1]);
	}
	#pragma omp parallel for shared(emp)
	for(int i=0;i<n;i++){
		p_s=(float)emp[i][1];
		inc=p_s*6/100;
		if(inc>5000){
			inc=inc-inc*2/100;
		}
		i_s=p_s+inc;
		printf("Employee %d,final salary:%f\n",emp[i][0],i_s);
	}
}