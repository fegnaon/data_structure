#include <stdio.h>
#define LS(i) (2*(i)+1)
#define RS(i) (2*(i)+2)
#define FA(i) (((i)+1)/2-1)

int isSame(int ref[],int A[],int N);
void percolateDown(int A[],int i,int N);

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

    int tmpA[N];
    for (int i = 0; i < N; ++i)
    {
        tmpA[i] = A[i];
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
    //不是插入就是堆排序
    printf("Heap Sort\n");

    for (i = N/2; i >= 0; --i)
    {
        percolateDown(tmpA,i,N);
    }

    for (i = N; i > 1; --i)
    {
        tmp = tmpA[0];
        tmpA[0] = tmpA[i-1];
        tmpA[i-1] = tmp;

        percolateDown(tmpA,0,i-1);
        if (isSame(tmpA,input,N)){
            --i;
            break;
        }
    }

    tmp = tmpA[0];
    tmpA[0] = tmpA[i-1];
    tmpA[i-1] = tmp;

    percolateDown(tmpA,0,i-1);

    //输出
    for (int i = 0; i < N-1; ++i)
    {
        printf("%d ",tmpA[i]);
    }
    printf("%d\n",tmpA[N-1]);

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

inline void percolateDown(int A[],int i,int N)
{
    int tmp,maxson;
    tmp = A[i];
    while(1)
    {
        if (LS(i) > N-1){
            break;
        }
        if (LS(i) == N-1){
            if (A[LS(i)] > tmp){
                A[i] = A[LS(i)];
                A[LS(i)] = tmp;
            }
            return;
        }

        if (A[LS(i)] > A[RS(i)]){
            maxson = LS(i);
        }
        else{
            maxson = RS(i);
        }

        if (tmp > A[maxson]){
            A[i] = tmp;
            break;
        }
        else{
            A[i] = A[maxson];
            i = maxson;
            A[i] = tmp;
        }
    }
}