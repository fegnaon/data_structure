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