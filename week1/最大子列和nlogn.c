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
    if (size == 1){
        return array[0];
    }
    int lsize,rsize;
    int lmax,tmax,rmax;
    lsize = size / 2;
    rsize = size - lsize;
    
    int i;
    int sum = 0;
    tmax = array[0];
    for (i = 0;i < size;i ++)
    {
        sum += array[i];
        if (sum > tmax){
            tmax = sum;
        }
    }
    lmax = cal(lsize,array);
    rmax = cal(rsize,array + lsize);

    if (tmax > rmax){
        if (tmax > lmax){
            return tmax;
        }
        else{
            return lmax;
        }
    }
    else{
        if (rmax > lmax){
            return rmax;
        }
        else{
            return lmax;
        }
    }
}