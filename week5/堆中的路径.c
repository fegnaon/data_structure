#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *Data;
    int Size;
    int MaxSize;
}MinHeap;

void MinHeap_Init(MinHeap *heap,int size);
void MinHeap_Insert(MinHeap *heap,int data);
// int MinHeap_Delete(MinHeap *heap);
void MinHeap_PrintRoute(MinHeap *heap,int index);

int main()
{
    int N,M,data;
    MinHeap heap;
    scanf("%d %d",&N,&M);
    MinHeap_Init(&heap,N);
    for (N; N; --N)
    {   
        scanf("%d",&data);
        MinHeap_Insert(&heap,data);
    }
    for (M; M; --M)
    {
        scanf("%d",&data);
        MinHeap_PrintRoute(&heap,data);
    }

    return 0;   
}

void MinHeap_Init(MinHeap *heap,int size)
{
    heap->Data = (int*)malloc( (size + 1) * sizeof(int) );
    heap->Size = 0;
    heap->MaxSize = size;
    heap->Data[0] = INT_MIN;

    return;
}

void MinHeap_Insert(MinHeap *heap,int data)
{
    if (heap->Size == heap->MaxSize){
        printf("error: heap is full\n");
        return;
    }

    heap->Data[++heap->Size] = data;
    for (int i = heap->Size; heap->Data[i/2] > heap->Data[i]; i = i/2)
    {
        heap->Data[i] = heap->Data[i/2];
        heap->Data[i/2] = data;
    }

    return;
}

// int MinHeap_Delete(MinHeap *heap);

void MinHeap_PrintRoute(MinHeap *heap,int index)
{   
    while (1)
    {
        printf("%d",heap->Data[index]);
        index /= 2;
        if (index){
            printf(" ");
        }
        else{
            return;
        }
    }
    printf("\n");

    return;
}