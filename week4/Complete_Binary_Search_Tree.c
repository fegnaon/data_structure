#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

typedef struct {
    BinTree *data;
    int head;
    int rear;
    int size;
    int tag;
}Seq;

Seq* init_seq(int size);
int in_seq(Seq *seq,BinTree data);
BinTree out_seq(Seq *seq);
void del_seq(Seq *seq);

Position CreateNode(ElementType data);
BinTree MakeCBT(int size);
BinTree FillCBT(BinTree CBT,ElementType *datas,int size);
void height_traverse(BinTree BST,int size);
void pre_traverse(BinTree BST);
int compare(const void *a,const void *b);
int cnt = 0;

int main()
{
    int N,i;
    scanf("%d",&N);
    int datas[N];
    for (i = 0; i < N; ++i)
    {
        scanf("%d",&datas[i]);
    }
    qsort(datas,N,sizeof(int),compare);

    BinTree CBT = MakeCBT(N);
    // pre_traverse(CBT);
    // printf("\n");
    FillCBT(CBT,datas,N);
    // pre_traverse(CBT);
    // printf("\n");

    height_traverse(CBT,N);
    return 0;
}

Seq* init_seq(int size)
{
    Seq *seq = (Seq*)malloc(sizeof(Seq));
    seq->data = (BinTree*)malloc((size) * sizeof(BinTree));
    seq->head = 0;
    seq->rear = 0;
    seq->size = size;
    seq->tag = 0;
    
    return seq;
}

int in_seq(Seq *seq,BinTree data)
{   
    if (seq->tag && seq->rear == seq->head){
        printf("head: %d rear: %d\n",seq->head,seq->rear);
        printf("error: seq is full\n");
        return 0;
    }
    // printf("IN ");
    seq->data[seq->rear] = data;
    seq->rear = seq->rear==seq->size-1?0:seq->rear+1;
    seq->tag = 1;

    return 1;
}

BinTree out_seq(Seq *seq)
{
    BinTree data;
    if (!seq->tag){
        printf("head: %d rear: %d\n",seq->head,seq->rear);
        printf("error: seq is empty\n");
        return NULL;
    }
    // printf("OUT ");
    data = seq->data[seq->head];
    seq->head = seq->head==seq->size-1?0:seq->head+1;
    if (seq->head == seq->rear){
        seq->tag = 0;
    }

    return data;
}

void del_seq(Seq *seq)
{
    free(seq->data);
    free(seq);

    return;
}

Position CreateNode(ElementType data)
{
    Position new = (Position)malloc(sizeof(struct TNode));
    new->Data = data;
    new->Left = NULL;
    new->Right = NULL;

    return new;
}

BinTree MakeCBT(int size)
{
    int n,t;
    for (n = 0; ((int)pow(2,n) - 1) < size; ++n);
    --n;
    t = size - (pow(2,n) - 1);

    Seq *seq = init_seq((int)pow(2,n));

    int i,j,k;
    BinTree CBT,tmp,l,r;
    CBT = CreateNode(0);
    in_seq(seq,CBT);
    // printf("n = %d,t = %d\n",n,t);
    for (i = 1; i < n; ++i)
    {   
        k = (int)pow(2,i-1);
        for (j = 0; j < k; ++j)
        {
            tmp = out_seq(seq);
            l = CreateNode(0);
            r = CreateNode(0);
            tmp->Left = l;
            tmp->Right = r;
            in_seq(seq,l);
            in_seq(seq,r);
        }
    }
    if (n){
        while (1)
        {   
            tmp = out_seq(seq);
            l = CreateNode(0);
            tmp->Left = l;
            if (!--t){
                break;
            }
            r = CreateNode(0);
            tmp->Right = r;
            if (!--t){
                break;
            }
        }
    }
    del_seq(seq);

    return CBT;
}

BinTree FillCBT(BinTree CBT,ElementType *datas,int size)
{
    if (!CBT){
        return NULL;
    }
    FillCBT(CBT->Left,datas,size);
    CBT->Data = datas[cnt];
    cnt += 1;
    FillCBT(CBT->Right,datas,size);

    return CBT;
}

void pre_traverse(BinTree BST)
{   
    if (!BST){
        return;
    }
    pre_traverse(BST->Left);
    printf("%d ",BST->Data);
    pre_traverse(BST->Right);

    return;
}

void height_traverse(BinTree BST,int size)
{
    Seq *seq = init_seq(size);
    printf("%d",BST->Data);
    if (BST->Left){
        in_seq(seq,BST->Left);
    }
    if (BST->Right){
        in_seq(seq,BST->Right);
    }
    BinTree tmp;
    while(seq->tag)
    {   
        printf(" ");
        tmp = out_seq(seq);
        printf("%d",tmp->Data);
        if (tmp->Left){
            in_seq(seq,tmp->Left);
        }
        if (tmp->Right){
            in_seq(seq,tmp->Right);
        }
    }

    return;
}

int compare(const void *a,const void *b)
{
    return *(int*)a - *(int*)b;
}