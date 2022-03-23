#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define GetHeight(a) ((a)?(a->Height):0)

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef AVLTree Position;
typedef struct AVLNode{
    ElementType data;
    AVLTree Left;
    AVLTree Right;
    int Height;
}AVLNode;

Position CreateNode(ElementType data);
AVLTree Insert(AVLTree tree,ElementType data);
AVLTree LLRotation(AVLTree tree);
AVLTree RRRotation(AVLTree tree);
AVLTree LRRotation(AVLTree tree);
AVLTree RLRotation(AVLTree tree);

void Pretraverse(AVLTree tree);
void Intraverse(AVLTree tree);

int main()
{
    int N;
    scanf("%d",&N);

    ElementType data;
    AVLTree tree = NULL;
    for (N; N; --N)
    {
        scanf("%d",&data);
        tree = Insert(tree,data);
        // Pretraverse(tree);
        // printf("\n");
        // Intraverse(tree);
        // printf("\n");
    }
    printf("%d",tree->data);
}

Position CreateNode(ElementType data)
{
    AVLNode *new = (Position)malloc(sizeof(AVLNode));
    new->data = data;
    new->Left = NULL;
    new->Right = NULL;
    new->Height = 1;

    return new;
}

AVLTree Insert(AVLTree tree,ElementType data)
{
    if (!tree){
        tree = CreateNode(data);
        return tree;
    }

    if (tree->data > data){
        tree->Left = Insert(tree->Left,data);

        if (GetHeight(tree->Left) - GetHeight(tree->Right) > 1){
            if (tree->Left->data > data){
                tree = LLRotation(tree);
            }
            else{
                tree = LRRotation(tree);
            }
        }
    }
    else if (tree->data < data){
        tree->Right = Insert(tree->Right,data);

        if (GetHeight(tree->Right) - GetHeight(tree->Left) > 1){
            if (tree->Right->data < data){
                tree = RRRotation(tree);
            }
            else{
                tree = RLRotation(tree);
            }
        }
    }
    else{
        return tree;
    }

    tree->Height = MAX(GetHeight(tree->Right),GetHeight(tree->Left)) + 1;
    return tree;
}

AVLTree LLRotation(AVLTree tree)
{
    Position tmp = tree->Left;
    tree->Left = tmp->Right;
    tmp->Right = tree;
    tree = tmp;
    tree->Height = MAX(GetHeight(tree->Right),GetHeight(tree->Left)) + 1;
    tree->Right->Height = MAX(GetHeight(tree->Right->Right),GetHeight(tree->Right->Left)) + 1;

    return tree;
}
AVLTree RRRotation(AVLTree tree)
{
    Position tmp = tree->Right;
    tree->Right = tmp->Left;
    tmp->Left = tree;
    tree = tmp;
    tree->Height = MAX(GetHeight(tree->Right),GetHeight(tree->Left)) + 1;
    tree->Left->Height = MAX(GetHeight(tree->Left->Right),GetHeight(tree->Left->Left)) + 1;

    return tree;
}

AVLTree LRRotation(AVLTree tree)
{
    tree->Left = RRRotation(tree->Left);
    tree = LLRotation(tree);
    
    return tree;
}
AVLTree RLRotation(AVLTree tree)
{
    tree->Right = LLRotation(tree->Right);
    tree = RRRotation(tree);
    return tree;
}

void Pretraverse(AVLTree tree)
{
    if (!tree){
        return;
    }
    Pretraverse(tree->Left);
    printf("%d ",tree->data);
    Pretraverse(tree->Right);

    return;
}

void Intraverse(AVLTree tree)
{
    if (!tree){
        return;
    }
    printf("%d ",tree->data);
    Pretraverse(tree->Left);
    Pretraverse(tree->Right);

    return;
}