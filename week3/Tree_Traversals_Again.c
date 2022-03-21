#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int answer[30];
int j = 0;

typedef struct Treenode{
    int data;
    struct Treenode *left;
    struct Treenode *right;
}Treenode;

typedef struct {
    Treenode **nodes;
    int top;
}Stack;

Stack* init_stack(int size);
void push(Stack *stack,Treenode *node);
Treenode* pop(Stack *stack);
void del_stack(Stack *stack);
Treenode* create_node(int data);
int find_father(Treenode *result,Treenode *root,Treenode *father,int target);

void pre_traverse(Treenode *node);

int main()
{
    int N;
    scanf("%d",&N);

    char operation[10];
    Treenode *pt,*new,*root;
    int data;
    Stack *stack = init_stack(N);
    scanf("%s %d",operation,&data);
    root = pt = new = create_node(data);
    push(stack,new);

    for ( N = N * 2 - 1; N; --N)
    {   
        scanf("%s",operation);
        if (!strcmp(operation,"Push")){
            // printf("pt = %d\n",pt->data);
            scanf("%d",&data);
            new = create_node(data);
            push(stack,new);
            if (!(pt->left)){
                pt->left = new;
            }
            else{
                pt->right = new;
            }
            pt = new;
        }
        else{
            pt = pop(stack);
        }
    }
    del_stack(stack);
    pre_traverse(root);

    printf("%d",answer[0]);
    for (int i = 1;answer[i] > 0; ++i)
    {
        printf(" %d",answer[i]);
    }
}

Stack* init_stack(int size)
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->nodes = (Treenode**)malloc(size * sizeof(Treenode));
    stack->top = -1;

    return stack;
}

void push(Stack *stack,Treenode *node)
{
    // printf("\tPUSH:%d\n",node->data);
    stack->nodes[++stack->top] = node;
    return;
}

Treenode* pop(Stack *stack)
{   
    // printf("\tPOP:%d\n",stack->nodes[stack->top]->data);
    return stack->nodes[stack->top--];
}

Treenode* create_node(int data)
{
    Treenode* new = (Treenode*)malloc(sizeof(Treenode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

void pre_traverse(Treenode *node)
{
    if(!node){
        return;
    }
    pre_traverse(node->left);
    pre_traverse(node->right);
    answer[j++] = node->data;

    return;
}

void del_stack(Stack *stack)
{
    free(stack->nodes);
    free(stack);

    return;
}