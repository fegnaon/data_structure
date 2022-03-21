#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char address[6];
    char next_address[6];
    int data;
    struct Node *next;
}Node;

typedef struct Head{
    int len;
    Node *head;
}Head;


void add_node(Head *head,char *address,char *next_address,int data);
Head* make_empty();
void check(Head *head,char *first_address,int *length);
void reverse_list(Head *head,int length);
void print_list(Head *head);

int main()
{   
    char first_address[6];
    int number,length;
    scanf("%s %d %d\n",first_address,&number,&length);

    Head *list = make_empty();
    list->len = number;
    int data;
    char address[6],next_address[6];
    for (; number; --number)
    {
        scanf("%s %d %s",address,&data,next_address);
        add_node(list,address,next_address,data);
    }
    check(list,first_address,&(list->len));

    reverse_list(list,length);
    print_list(list);

    return 0;
}

Head* make_empty()
{
    Head *head = (Head*)malloc(sizeof(head));
    head->head = NULL;

    return head;
}   

void add_node(Head *head,char *address,char *next_address,int data)
{
    int i;
    Node *pt = head->head,*pt2;

    Node *new = (Node*)malloc(sizeof(Node));
    strcpy(new->address,address);
    new->data = data;
    strcpy(new->next_address,next_address);
    new->next = NULL;

    if (!pt){
        head->head = new;
    }
    else{
        for (pt = head->head;pt && pt->data < data; pt2 = pt,pt = pt->next);
            if (!pt){
                pt2->next = new;
            }
            else{
                if (pt == head->head){
                    head->head = new;
                    new->next = pt;
                }
                else{
                    pt2->next = new;
                    new->next = pt;
                }
            }
    }

    return;
}

void check(Head *head,char *first_address,int *length)
{
    Node *pt = head->head;

    while (strcmp(head->head->address,first_address))
    {
        pt = head->head;
        head->head = pt->next;
        free(pt);
        -- *length;
    }

    pt = head->head;
    Node *ptn = pt->next;
    if (!ptn){
        return;
    }

    while (strcmp(ptn->next_address,"-1"))
    {
        if (strcmp(pt->next_address,ptn->address)){
            pt->next =ptn->next;
            free(ptn);
            -- *length;
        }
        else{
            pt = ptn;
        }
        ptn = pt->next;
    }

    pt = ptn->next;
    ptn->next = NULL;
    for ( ; pt;)
    {
        ptn = pt->next;
        free(pt);
        -- *length;
        pt = ptn;
    }

    return;
}

void reverse_list(Head *head,int length)
{    
    if (length == 1){
        return;
    }
    // printf("List:\n");
    // print_list(head);
    // printf("......\n");

    Node *pt1,*pt2,*pt3;
    Node *lrear = NULL,*nrear;
    int i,left = head->len;
    pt3= head->head;

    while(left >= length)
    {
        pt1 = pt3;
        pt2 = pt1->next;
        pt3 = pt2->next;

        i = 1;
        while(1)
        {
            pt2->next = pt1;
            ++ i;
            if (i == length){
                break;
            }
            pt1 = pt2;
            pt2 = pt3;
            pt3 = pt3->next;
        }

        if (lrear){
            nrear = lrear->next;
            lrear->next = pt2;
            nrear->next = pt3;
            lrear = nrear;
        }
        else{
            lrear = head->head;
            head->head->next = pt3;
            head->head = pt2;
        }

        left -= length;
    }

    // printf("List:\n");
    // print_list(head);
    // printf("......\n");

    for (pt1 = head->head;pt1->next;pt1 = pt1->next)
    {   
        strcpy(pt1->next_address,pt1->next->address);
    }
    strcpy(pt1->next_address,"-1");

    return;
}

void print_list(Head *head)
{   
    // printf("........\n");
    Node *pt = head->head;
    for (; pt; pt = pt->next)
    {
        printf("%s %d %s\n",pt->address,pt->data,pt->next_address);
    }

    return;
}