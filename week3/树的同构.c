#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode{
    char data;
    struct treenode *left;
    struct treenode *right;
}treenode;

typedef struct {
    treenode *node;
    int left;
    int right;
}rawnode;

treenode* create_node(char data);
treenode* init_tree(rawnode *list,int len);
int ifiso(treenode *tree1,treenode *tree2);

int main()
{
    int cnt,i;
    char data[4];
    char left[4],right[4];

    scanf("%d",&cnt);
    rawnode list1[cnt];
    treenode *tree1;
    for (i = 0;i < cnt; ++i)
    {   
        scanf("%s %s %s",data,left,right);
        list1[i].node = create_node(data[0]);
        list1[i].left = strcmp(left,"-")?atoi(left):-1;
        list1[i].right = strcmp(right,"-")?atoi(right):-1;
    }
    tree1 = init_tree(list1,cnt);

    scanf("%d",&cnt);
    rawnode list2[cnt];
    treenode *tree2;
    for (i = 0;i < cnt; ++i)
    {   
        scanf("%s %s %s",data,left,right);
        list2[i].node = create_node(data[0]);
        list2[i].left = strcmp(left,"-")?atoi(left):-1;
        list2[i].right = strcmp(right,"-")?atoi(right):-1;
    }
    tree2 = init_tree(list2,cnt);

    if (ifiso(tree1,tree2)){
        printf("Yes");
    }
    else{
        printf("No");
    }
}

treenode* create_node(char data)
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

int ifiso(treenode *tree1,treenode *tree2)
{
    if (tree1 == NULL && tree2 == NULL){
        return 1;
    }
    else if ((tree1 == NULL && tree2 != NULL) || (tree1 != NULL && tree2 == NULL)){
        return 0;
    }
    if (tree1->data != tree2->data){
        return 0;
    }
    
    if (ifiso(tree1->left,tree2->left)){
        if (ifiso(tree1->right,tree2->right)){
            return 1;
        }
        return 0;
    }
    else if (ifiso(tree1->left,tree2->right)){
        if (ifiso(tree1->right,tree2->left)){
            return 1;
        }
        return 0;
    }
}