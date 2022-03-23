#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void pre_traverse(BinTree BST);

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );
void Clear(BinTree BST);
int Ifsame(BinTree BST1,BinTree BST2);

int main()
{
    int N,L,i;
    ElementType data;

    while (1)
    {
        scanf("%d",&N);
        if (!N){
            break;
        }
        scanf("%d",&L);

        BinTree rBST = NULL;
        for (i = 0; i < N; ++i)
        {
            scanf("%d",&data);
            rBST = Insert(rBST,data);
        }
        // pre_traverse(rBST);
        // printf("\n");
        for (L; L; --L)
        {
            BinTree BST = NULL;
            for (i = 0; i < N; ++i)
            {
                scanf("%d",&data);
                BST = Insert(BST,data);
            }
            // pre_traverse(BST);
            // printf("\n");

            if (Ifsame(rBST,BST)){
                printf("Yes\n");
            }
            else{
                printf("No\n");
            }
            Clear(BST);
        }
        Clear(rBST);

    }
    return 0;
}

BinTree Insert( BinTree BST, ElementType X )
{
    if (!BST){
        struct TNode *new = (struct TNode*)malloc(sizeof(struct TNode));
        new->Data = X;
        new->Left = NULL;
        new->Right = NULL;
        BST = new;
    }
    if (BST->Data > X){
        BST->Left = Insert(BST->Left,X);
    }
    else if (BST->Data < X){
        BST->Right = Insert(BST->Right,X);
    }
    
    return BST;
}

BinTree Delete( BinTree BST, ElementType X )
{
    if (!BST){
        printf("Not Found\n");
    }
    else if (BST->Data > X){
        BST->Left = Delete(BST->Left,X);
    }
    else if (BST->Data < X){
        BST->Right = Delete(BST->Right,X);
    }
    else{
        if ((!BST->Left) && (!BST->Right)){
            free(BST);
            BST = NULL;
        }
        else if (BST->Left && (!BST->Right)){
            BinTree tmp = BST->Left;
            free(BST);
            BST = tmp;
        }
        else if ((!BST->Left) && BST->Right){
            BinTree tmp = BST->Right;
            free(BST);
            BST = tmp;
        }
        else{
            Position tmp = FindMax(BST->Left);
            BST->Data = tmp->Data;
            BST->Left = Delete(BST->Left,tmp->Data);
        }
    }
    return BST;
}

Position Find( BinTree BST, ElementType X )
{
    if (!BST){
        return NULL;
    }
    if (BST->Data > X){
        return Find(BST->Left,X);
    }
    else if (BST->Data < X){
        return Find(BST->Right,X);
    }
    else{
        return BST;
    }
}

Position FindMin( BinTree BST )
{   
    if (!BST || !BST->Left){
        return BST;
    }
    else{
        return FindMin(BST->Left); 
    }
}

Position FindMax( BinTree BST )
{
    if (!BST || !BST->Right){
        return BST;
    }
    else{
        return FindMax(BST->Right); 
    }
}

void Clear(BinTree BST)
{
    if (!BST){
        return;
    }
    if ((!BST->Left) && (!BST->Right)){
        free(BST);
        return;
    }
    if (BST->Left){
        Clear(BST->Left);
    }
    if (BST->Right){
        Clear(BST->Right);
    }
    free(BST);
    return;
}

int Ifsame(BinTree BST1,BinTree BST2)
{   
    if ((!BST1) && (!BST2)){
        return 1;
    }
    else if ((!BST1) && BST2){
        return 0;
    }
    else if (BST1 && (!BST2)){
        return 0;
    }

    if (BST1->Data != BST2->Data){
        return 0;
    }
    if (!Ifsame(BST1->Left,BST2->Left)){
        return 0;
    }
    if (!Ifsame(BST1->Right,BST2->Right)){
        return 0;
    }
    return 1;
}

void pre_traverse(BinTree BST)
{
    if(!BST){
        return;
    }
    pre_traverse(BST->Left);
    printf("%d ",BST->Data);
    pre_traverse(BST->Right);

    return;
}