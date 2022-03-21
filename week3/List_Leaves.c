#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
}treenode;

typedef struct {
    treenode *node;
    int left;
    int right;
}rawnode;

typedef struct {
    treenode **nodes;
    int head;
    int rear;
}Seq;

treenode* create_node(int data);
treenode* init_tree(rawnode *list,int len);
void traverse_bydep(treenode *node,int *leaves,int len);

Seq* init_seq(int size);
void in(Seq *seq,treenode *node);
treenode* out(Seq *seq);
void del_seq(Seq *seq);

void print_tree(treenode *node,int dep);

int main()
{
    int cnt,i;
    char left[4],right[4];

    scanf("%d",&cnt);
    rawnode list[cnt];
    treenode *tree;
    for (i = 0;i < cnt; ++i)
    {   
        scanf("%s %s",left,right);
        list[i].node = create_node(i);
        list[i].left = strcmp(left,"-")?atoi(left):-1;
        list[i].right = strcmp(right,"-")?atoi(right):-1;
    }
    tree = init_tree(list,cnt);

    int leaves[cnt];
    traverse_bydep(tree,leaves,cnt);
    printf("%d",leaves[0]);
    for (i = 1; i < cnt; ++i)
    {
        if (leaves[i] >= 0){
            printf(" %d",leaves[i]);
        }
        else{
            break;
        }
    }

    return 0;
}

treenode* create_node(int data)
{
    treenode *new = (treenode*)malloc(sizeof(treenode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

treenode* init_tree(rawnode *list,int len)
{   
    if (len == 0){
        return NULL;
    }
    treenode *root;
    int ifroot[len];
    memset(ifroot,0,sizeof(ifroot));
    int i;
    for (i = 0;i < len; ++i)
    {   
        if (list[i].left >= 0){
            ifroot[list[i].left] = 1;
            list[i].node->left = list[list[i].left].node;
        }
        if (list[i].right >= 0){
            ifroot[list[i].right] = 1;
            list[i].node->right = list[list[i].right].node;
        }
    }

    for (i = 0;i < len; ++ i)
    {
        if (ifroot[i] == 0){
            root = list[i].node;
        }
    }

    return root;
}

void traverse_bydep(treenode *node,int *leaves,int len)
{
    Seq *seq = init_seq(len);
    treenode *pt;
    int i = 0;
    in(seq,node);
    int d = 0;

    while (seq->rear != seq->head)
    {   
        pt = out(seq);
        if (pt->left){
            in(seq,pt->left);
        }
        if (pt->right){
            in(seq,pt->right);
        }
        if ((!pt->left) && (!pt->right)){
            leaves[i++] = pt->data;
        }
    }
    leaves[i] = -1;
    del_seq(seq);

    return;
}

Seq* init_seq(int size)
{
    Seq *seq = (Seq*)malloc(sizeof(Seq));
    seq->nodes = (treenode**)malloc(sizeof(treenode*) * size);
    seq->head = -1;
    seq->rear = -1;

    return seq;
}

void in(Seq *seq,treenode *node)
{      
    seq->nodes[++seq->rear] = node;
    return;
}

treenode* out(Seq *seq)
{
    return seq->nodes[++seq->head];
}

void del_seq(Seq *seq)
{
    free(seq->nodes);
    free(seq);
    return;
}