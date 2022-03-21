#include <stdio.h>

int main()
{
	int size;
	scanf("%d\n",&size);
	int array[size];
	for (int i = 0;i < size;i ++)
	{	
		scanf("%d",&array[i]);
	}

	int i,j,k;
	int sum,maxsum = array[0];
	for (i = 0;i < size;i ++)
	{	
		for (j = size - 1;j > i;j --)
		{
			sum = array[i];
			for (k = i+1;k <= j;k ++)
			{
				sum += array[k];
			}
			if (sum > maxsum){
				maxsum = sum;
			}
		}
	}
	if (maxsum < 0){
		printf("0");
	}
	else{
		printf("%d\n",maxsum);
	}
}