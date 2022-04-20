// TODO:重写
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char character;
    int frequency;
    char *code;
}Character;

typedef struct Node{
    int frequency;
    int len;
    struct Node *left;
    struct Node *right;
}Node;

typedef struct {
    Node **Data;
    int Size;
    int MaxSize;
}MinHeap;

typedef struct {
    Node **data;
    int head;
    int rear;
    int size;
    int tag;
}Seq;

Seq* init_seq(int size);
int in_seq(Seq *seq,Node *data);
Node* out_seq(Seq *seq);
void del_seq(Seq *seq);

Node* Create_Node(int frequency);
MinHeap* MinHeap_Init(int size);
Node* MinHeap_Delete(MinHeap *heap);
void MinHeap_Insert(MinHeap *heap,Node *data);

void MakeLen(Node *tree);

int IfAmbiguous(Character *characters,int len,char *s);
int FreqOfChar(Character *refcharacters,int len,char c);

int main()
{
    int N,frequency;
    char c[2],s[100];
    scanf("%d",&N);
    Character refCharacters[N];
    for (int i = 0; i < N; ++i)
    {
        scanf("%s %d",c,&frequency);
        // printf("%c %d\n",c[0],frequency);
        refCharacters[i].character = c[0];
        refCharacters[i].frequency = frequency;
    }
//得出正确的答案
    //创建堆
    MinHeap *heap = MinHeap_Init(N);
    for (int i = 0; i < N; ++i)
    {
        MinHeap_Insert(heap,Create_Node(refCharacters[i].frequency));
    }
    //生成哈夫曼树
    Node *pt,*ptl,*ptr;
    while (heap->Size > 1)
    {
        ptl = MinHeap_Delete(heap);
        ptr = MinHeap_Delete(heap);
        pt = Create_Node(ptl->frequency + ptr->frequency);
        pt->left = ptl;
        pt->right = ptr;
        MinHeap_Insert(heap,pt);
    }
    //计算总和
    pt = MinHeap_Delete(heap);
    pt->len = 0;
    MakeLen(pt);
    int refcost = 0;
    Seq *seq = init_seq(N+1);
    in_seq(seq,pt);
    while (seq->head != seq->rear)
    {
        pt = out_seq(seq);
        if (pt->left){
            in_seq(seq,pt->left);
        }
        if (pt->right){
            in_seq(seq,pt->right);
        }

        if (!pt->left && !pt->right){
            refcost += pt->frequency * pt->len;
        }
    }
    del_seq(seq);
//判断答案对错
    int M;
    scanf("%d",&M);
    for (int i = 0; i < M; ++i)
    {
        int cost = 0,tag = 1;
        Character characters[N];
        //读入答案并检查是否是前缀码
        for (int i = 0; i < N; ++i)
        {
            scanf("%s %s",c,s);
            if (IfAmbiguous(characters,i,s)){
                tag = 0;
            }
            characters[i].character = c[0];
            characters[i].frequency = FreqOfChar(refCharacters,N,c[0]);
            characters[i].code = (char*)malloc( sizeof(int) * (strlen(s) + 1) );
            strcpy(characters[i].code,s);
        }
        //检查总权重
        for (int i = 0; i < N; ++i)
        {
            cost += characters[i].frequency * strlen(characters[i].code);
        }
        if (cost != refcost){
            tag = 0;
        }

        if (tag){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }

        for (int i = 0; i < N; ++i)
        {
            free(characters[i].code);
        }
    }

    return 0;
}

Seq* init_seq(int size)
{
    Seq *seq = (Seq*)malloc(sizeof(Seq));
    seq->data = (Node**)malloc((size) * sizeof(Node*));
    seq->head = 0;
    seq->rear = 0;
    seq->size = size;
    seq->tag = 0;

    return seq;
}

int in_seq(Seq *seq,Node *data)
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

Node *out_seq(Seq *seq)
{
    Node *data;
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

Node* Create_Node(int frequency)
{
    Node *new = (Node*)malloc(sizeof(Node));
    new->frequency = frequency;
    new->len = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

MinHeap* MinHeap_Init(int size)
{
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->Data = (Node**)malloc( (size + 1) * sizeof(Node*) );
    heap->Size = 0;
    heap->MaxSize = size;
    heap->Data[0] = Create_Node(INT_MIN);

    return heap;
}

Node* MinHeap_Delete(MinHeap *heap)
{
    Node *top = heap->Data[1];
    heap->Data[1] = heap->Data[heap->Size];
    heap->Size -= 1;
    Node *pt = heap->Data[1];
    int i = 1,left,right,min;
    while (1)
    {
        min = left = i * 2;
        right = left + 1;
        if (left > heap->Size){
            break;
        }
        if (right <= heap->Size && heap->Data[left]->frequency > heap->Data[right]->frequency){
            min = right;
        }

        if (heap->Data[min]->frequency < heap->Data[i]->frequency){
            heap->Data[i] = heap->Data[min];
            heap->Data[min] = pt;
            i = min;
        }
        else{
            break;
        }
    }

    return top;
}

void MinHeap_Insert(MinHeap *heap,Node *data)
{
    if (heap->Size == heap->MaxSize){
        printf("error: heap is full\n");
        return;
    }

    heap->Data[++heap->Size] = data;
    for (int i = heap->Size; heap->Data[i/2]->frequency > heap->Data[i]->frequency; i = i/2)
    {
        heap->Data[i] = heap->Data[i/2];
        heap->Data[i/2] = data;
    }

    return;
}

void MakeLen(Node *tree)
{
    if (tree->left){
        tree->left->len = tree->len + 1;
        MakeLen(tree->left);
    }
    if (tree->right){
        tree->right->len = tree->len + 1;
        MakeLen(tree->right);
    }

    return;
}

int IfAmbiguous(Character *characters,int len,char *s)
{
    char str[100];
    int length = strlen(s);
    for (int i = 0; i < len; ++i)
    {
        strcpy(str,characters[i].code);
        str[length] = '\0';
        if (!strcmp(str,s)){
            return 1;
        }
    }
    return 0;
}

int FreqOfChar(Character *refcharacters,int len,char c)
{
    for (int i = 0; i < len; ++i)
    {
        if (refcharacters[i].character == c){
            return refcharacters[i].frequency;
        }
    }
    return 0;
}