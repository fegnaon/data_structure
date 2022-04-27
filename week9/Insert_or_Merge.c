#include <stdio.h>

int isSame(int ref[],int A[],int N);
void merge(int A[],int tmpA[],int start,int length,int N);

int main()
{
    int N,i;
    scanf("%d",&N);
    int A[N],data;
    for (i = 0; i < N; ++i)
    {
        scanf("%d",&data);
        A[i] = data;
    }
    int input[N];
    for (i = 0; i < N; ++i)
    {
        scanf("%d",&data);
        input[i] = data;
    }
    //检查是否是插入
    int tag = 0;
    int tmp,j;
    for (i = 1; i < N; ++i)
    {
        tmp = A[i];
        for (j = i-1; j > -1 && A[j] > tmp; --j)
        {
            A[j+1] = A[j];
        }
        A[j+1] = tmp;
        if (tag) break;
        if (isSame(A,input,N)){
            tag = 1;
        }
    }
    if (tag){
        printf("Insertion Sort\n")  ;
        for (int i = 0; i < N-1; ++i)
        {
            printf("%d ",A[i]);
        }
        printf("%d\n",A[N-1]);
        return 0;
    }
    //不是插入就是合并
    printf("Merge Sort\n");
    int length = 1;
    for (i = 0; i < N-1 && input[i] < input[i+1]; ++length,++i);
    int k;
    while(1)
    {
        k = 1,tag = 0;
        for (i = 0; i < N-1; ++i)
        {
            if (input[i] < input[i+1]){
                ++k;
                if (k == length){
                    k = 1;
                    i += 1;
                }
            }
            else{
                break;
            }
        }
        if (i >= N-1){
            break;
        }
        else{
            length /= 2;
        }
    }

    for (i = 0; i <= N - length * 2; i += length * 2)
    {
        merge(input,A,i,length,N);
    }
    merge(input,A,i,length,N);

    for (int i = 0; i < N-1; ++i)
    {
        printf("%d ",A[i]);
    }
    printf("%d\n",A[N-1]);

    return 0;
}

int isSame(int A[],int B[],int N)
{
    for (int i = 0; i < N; ++i)
    {
        if (A[i] != B[i]){
            return 0;
        }
    }
    return 1;
}
void merge(int A[],int tmpA[],int start,int length,int N)
{
    if (start >= N){
        return;
    }
    int L = start,Lend,R = start + length,end = R + length,tmp = L;
    if (N <= end){
        end = N;
    }
    if (N <= R){
        R = end = N;
    }
    Lend = R;

    while (L < Lend && R < end)
    {
        tmpA[tmp++] = (A[L] < A[R])?(A[L++]):(A[R++]);
    }
    for (L; L < Lend; tmpA[tmp++] = A[L++]);
    for (R; R < end; tmpA[tmp++] = A[R++]);
    return;
}