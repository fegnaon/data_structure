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
        sum = array[i];
        if (sum > maxsum){
            maxsum = sum;
        }
		for (j = i + 1;j < size;j ++)
		{
            sum += array[j];
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