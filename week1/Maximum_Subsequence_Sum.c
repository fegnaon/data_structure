#include <stdio.h>

int cal(int size,int *array,int *start,int *end);

int main()
{
    int size;
	scanf("%d\n",&size);
	int array[size],start,end;
	for (int i = 0;i < size;i ++)
	{	
		scanf("%d",&array[i]);
	}

    int maxsum = cal(size,array,&start,&end);

    if (maxsum < 0){
		printf("0 %d %d",array[0],array[size-1]);
	}
	else{
		printf("%d %d %d",maxsum,start,end);
	}
}

int cal(int size,int *array,int *start,int *end)
{
    int i,sum = 0,max = array[0];
    int nstart = array[0];

    *start = array[0],*end = array[0];
    for (i = 0;i < size;i ++)
    {   
        sum += array[i];
        if (sum < 0){
            nstart = array[i+1];
            sum = 0;
            continue;
        }
        if (sum > max){
            *start = nstart;
            *end = array[i];
            max = sum;
        }
    }

    return max;
}