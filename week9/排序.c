#include <stdio.h>
// README: 去掉一条注释选择一种排序
// #define BUBBLESORT
// #define INSERTSORT
// #define SHELLSORT
// #define HEAPSORT
// #define MERGESORT_RECURSE
// #define MERGESORT_NORECURSE

typedef int ElementType;

void sort(ElementType elements[],int N);

int main()
{
    int N;
    scanf("%d",&N);

    ElementType elements[N],e;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d",&e);
        elements[i] = e;
    }
    sort(elements,N);
    for (int i = 0; i < N-1; ++i)
    {
        printf("%d ",elements[i]);
    }
    printf("%d",elements[N-1]);

    return 0;
}

#ifdef BUBBLESORT
void sort(ElementType elements[],int N)
{
    int tag,tmp;
    for (int i = N-1; i > 0; --i)
    {
        tag = 1;
        for (int j = 0; j < i; ++j)
        {
            if (elements[j] > elements[j+1]){
                tmp = elements[j];
                elements[j] = elements[j+1];
                elements[j+1] = tmp;
                tag = 0;
            }
        }
        if (tag){
            return;
        }
    }
    return;
}
#endif
#ifdef INSERTSORT
void sort(ElementType elements[],int N)
{
    int tmp,i,j;
    for (i = 0; i < N; ++i)
    {
        tmp = elements[i];
        for (j = i-1; j > -1 && elements[j] > tmp; --j)
        {
            elements[j+1] = elements[j];
        }
        elements[j+1] = tmp;
    }
    return;
}
#endif
#ifdef SHELLSORT
void sort(ElementType elements[],int N)
{
    int i,j,k;
    for (i = 1,j = 2; j-1 < N; ++i,j *= 2);
    int D[i-1],Dsize = i-1;
    for (i = Dsize - 1,j = 2; i >= 0; --i,j *= 2)
    {
        D[i] = j - 1;
    }

    int d,tmp;
    for (i = 0; i < Dsize; ++i)
    {
        d = D[i];
        for (j = d; j < N; ++j)
        {
            tmp = elements[j];
            for (k = j; k >= d && elements[k-d] > tmp; k -= d)
            {
                elements[k] = elements[k-d];
            }
            elements[k] = tmp;
        }
    }
    return;
}
#endif
#ifdef HEAPSORT
#define LS(i) (2*(i)+1)
#define RS(i) (2*(i)+2)
#define FA(i) (((i)+1)/2-1)
void percolateDown(ElementType A[],int i,int N);
void sort(ElementType elements[],int N)
{
    int i,tmp;
    for (i = N/2; i >= 0; --i)
    {
        percolateDown(elements,i,N);
    }

    for (i = N; i > 1; --i)
    {
        tmp = elements[0];
        elements[0] = elements[i-1];
        elements[i-1] = tmp;

        percolateDown(elements,0,i-1);
    }
    return;
}
inline void percolateDown(ElementType A[],int i,int N)
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
#endif
#ifdef MERGESORT_RECURSE
void MergerSort(ElementType A[],ElementType tmpA[],int start,int end);
void Merge(ElementType A[],ElementType tmpA[],int Lstart,int Rstart,int end);
void sort(ElementType elements[],int N)
{
    int tmpA[N];
    MergerSort(elements,tmpA,0,N-1);
    return;
}
void MergerSort(ElementType A[],ElementType tmpA[],int start,int end)
{
    int center = (start + end) / 2;
    if (start < end){
        MergerSort(A,tmpA,start,center);
        MergerSort(A,tmpA,center+1,end);
        Merge(A,tmpA,start,center+1,end);
    }
    return;
}
void Merge(ElementType A[],ElementType tmpA[],int Lstart,int Rstart,int end)
{
    int L = Lstart,R = Rstart,tmp = Lstart;
    while (L < Rstart && R <= end)
    {
        tmpA[tmp++] = (A[L] < A[R])?(A[L++]):(A[R++]);
    }
    for (L; L < Rstart; tmpA[tmp++] = A[L++]);
    for (R; R <= end; tmpA[tmp++] = A[R++]);

    for (tmp = Lstart; tmp <= end; ++tmp)
    {
        A[tmp] = tmpA[tmp];
    }
    return;
}
#endif
#ifdef MERGESORT_NORECURSE
void merge(ElementType A[],ElementType tmpA[],int start,int length,int N);
void sort(ElementType elements[],int N)
{
    int tmpA[N],length = 1,i;
    while(length < N)
    {
        for (i = 0; i <= N - length * 2; i += length * 2)
        {
            merge(elements,tmpA,i,length,N);
        }
        merge(elements,tmpA,i,length,N);
        length *= 2;
        for (i = 0; i <= N - length * 2; i += length * 2)
        {
            merge(tmpA,elements,i,length,N);
        }
        merge(tmpA,elements,i,length,N);
        length *= 2;
    }
    return;
}
void merge(ElementType A[],ElementType tmpA[],int start,int length,int N)
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
#endif