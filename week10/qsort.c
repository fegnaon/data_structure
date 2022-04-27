#include <stdio.h>

void sort(int A[],int N);
int findPivot(int A[],int start,int end);
void quickSort(int A[],int start,int end);
void smallSort(int A[],int N);

int main()
{
    int N;
    scanf("%d",&N);

    int A[N],e;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d",&e);
        A[i] = e;
    }
    sort(A,N);
    for (int i = 0; i < N-1; ++i)
    {
        printf("%d ",A[i]);
    }
    printf("%d\n",A[N-1]);

    return 0;
}

void sort(int A[],int N)
{
    quickSort(A,0,N-1);
    return;
}

void quickSort(int A[],int start,int end)
{
    int tmp;
    if (end - start > 200){
        int pivot = findPivot(A,start,end);
        int L = start+1,R = end - 2;
        while(1)
        {
            for (L; A[L] < pivot; ++L);
            for (R; A[R] > pivot; --R);
            if (L > R){
                break;
            }
            tmp = A[L];
            A[L] = A[R];
            A[R] = tmp;
            ++L,--R;
        }
        tmp = A[L];
        A[L] = A[end-1];
        A[end-1] = tmp;
        quickSort(A,start,L-1);
        quickSort(A,L+1,end);
    }
    else{
        smallSort(A + start,end - start + 1);
    }
    return;
}

int findPivot(int A[],int start,int end)
{
    int tmp;
    int center = (start + end) / 2;
    if (A[start] > A[center]){
        tmp = A[start];
        A[start] = A[center];
        A[center] = tmp;
    }
    if (A[center] > A[end]){
        tmp = A[center];
        A[center] = A[end];
        A[end] = tmp;
    }
    if (A[start] > A[center]){
        tmp = A[start];
        A[start] = A[center];
        A[center] = tmp;
    }
    tmp = A[center];
    A[center] = A[end-1];
    A[end-1] = tmp;

    return A[end-1];
}

void smallSort(int A[],int N)
{
    int tmp,i,j;
    for (i = 0; i < N; ++i)
    {
        tmp = A[i];
        for (j = i-1; j > -1 && A[j] > tmp; --j)
        {
            A[j+1] = A[j];
        }
        A[j+1] = tmp;
    }
    return;
}