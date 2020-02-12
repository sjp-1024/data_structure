/***********************************************************
*       &Author: ShijinPeng     
*       &E-mail: 878491983@qq.com
*       &Motto: Believe in yourself.
*       &File Name: 12.unstable_sort.cpp
*       &Created Time: 19Century 2019年08月17日 星期六 10时45分12秒 
*                          CST  Day/229 and Week/32 of this year
*       &Description:
*
*
***********************************************************/


#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define swap(a,b){\
	__typeof(a) __temp=a;\
	a=b, b=__temp;\
}

#define TEST(arr,n,func,args...){\
	int *num=(int *)malloc(sizeof(int)* n);\
	memcpy(num,arr,sizeof(int) *n);\
	output(num,n);\
	printf("%s= ",#func);\
	func(args);\
	output(num,n);\
	free(num);\
}

void select_sort(int *num,int n){
	for(int i=0;i<n;i++){
		int ind=i;
		for(int j=i+1;j<n;j++){
			if(num[ind]>num[j]) ind=j;
		}
		swap(num[i],num[ind]);
	}
	return ;
}

void quick_sort(int *num,int l,int r){
	if(r<=l) return ;
	int x=l,y=r,z=num[l];
	while(x<y){
		while(x<y  && num[y]>=z) --y;
		if(x<y) num[x++]=num[y];
		while(x<y  && num[x]<=z) ++x;
		if(x<y) num[y--]=num[x];
	}
	num[x]=z;
	quick_sort(num,l,x-1);
	quick_sort(num,x+1,r);

}

void randint(int *num,int n){
	while(n--) num[n]=rand()%100;
	return ;
}

void output(int *num,int n){
	printf("[");
	for(int i=0;i<n;i++){
	printf(" %d",num[i]);
	}
	printf("]\n");
	return ;
}

int main(){
	srand(time(0));
	#define MAX_OP 20
	int arr[MAX_OP ];
	randint(arr,MAX_OP);
	TEST(arr,MAX_OP,select_sort,num,MAX_OP);
	TEST(arr,MAX_OP,quick_sort,num,0,MAX_OP-1);
	return 0;
}
