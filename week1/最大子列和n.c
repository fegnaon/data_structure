#include <stdio.h>

int cal(int size,int *array);

int main()
{
    int size;
	scanf("%d\n",&size);
	int array[size];
	for (int i = 0;i < size;i ++)
	{	
		scanf("%d",&array[i]);
	}

    int maxsum = cal(size,array);

    if (maxsum < 0){
		printf("0");
	}
	else{
		printf("%d\n",maxsum);
	}
}

int cal(int size,int *array)
{
    int i,sum = 0,max = array[0];

    for (i = 0;i < size;i ++)
    {
        sum += array[i];
        if (sum <= 0){
            sum = 0;
            continue;
        }
        if (sum > max){
            max = sum;
        }
    }

    return max;
}