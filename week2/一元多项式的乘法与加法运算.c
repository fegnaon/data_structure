#include <stdio.h>
#include <stdlib.h>

typedef struct Polynode{
    int index;
    int coefficient;
    struct Polynode *next;
}Polynode;

typedef struct {
    Polynode *head;
    Polynode *rear;
}Polyhead;

Polyhead* make_empty();
void add_node(Polyhead *head,int index,int coefficient);
Polyhead* poly_mul(Polyhead* poly1,Polyhead* poly2);
Polyhead* poly_sum(Polyhead* poly1,Polyhead* poly2);
void poly_print(Polyhead* poly);

int main()
{
    int cnt,index,coefficient;
    Polyhead *poly1 = make_empty();
    Polyhead *poly2 = make_empty();
    scanf("%d",&cnt);
    for (; cnt; --cnt)
    {
        scanf("%d %d",&index,&coefficient);
        add_node(poly1,index,coefficient);
    }
    scanf("%d",&cnt);
    for (; cnt; --cnt)
    {
        scanf("%d %d",&index,&coefficient);
        add_node(poly2,index,coefficient);
    }

    Polyhead *mul = poly_mul(poly1,poly2);
    poly_print(mul);
    Polyhead *sum = poly_sum(poly1,poly2);
    poly_print(sum);

    return 0;
}

Polyhead* make_empty()
{
    Polyhead *head = (Polyhead*)malloc(sizeof(Polyhead));
    head->head = NULL;
    head->rear = NULL;
    
    return head;
}

void add_node(Polyhead *head,int index,int coefficient)
{
    int i;
    Polynode *new = (Polynode*)malloc(sizeof(Polynode));
    new->index = index;
    new->coefficient = coefficient;
    new->next = NULL;

    Polynode *pt1,*pt2;
    if (head->head){
        if (head->head->coefficient < coefficient){
            new->next = head->head;
            head->head = new;
        }
        else if (head->head->coefficient == coefficient){
            free(new);
            head->head->index += index;
            if (!head->head->index)
            {   
                pt1 = head->head;
                head->head = head->head->next;
                free(pt1);
                if (!head->head){
                    head->rear = NULL;
                }
            }
        }
        else{
            for (pt1 = head->head;pt1 && pt1->coefficient >= coefficient;pt2 = pt1,pt1 = pt1->next);
            if (pt2->coefficient == coefficient){
                free(new);
                pt2->index += index;
                if (!pt2->index){
                    for (pt1 = head->head;pt1->next != pt2;pt1 = pt1->next);
                    pt1->next = pt2->next;
                    free(pt2);
                    if (!pt1->next){
                        head->rear = pt1;
                    }
                }
            }
            else{
                if (pt1){
                    pt2->next = new;
                    new->next = pt1;
                }
                else{
                    pt2->next = new;
                    head->rear = new;
                }
            }
        }
    }
    else{
        head->rear = new;
        head->head = new;
    }

    return;
}

Polyhead* poly_mul(Polyhead* poly1,Polyhead* poly2)
{
    Polyhead *mul = make_empty();
    Polynode *pt1,*pt2;
    for (pt1 = poly1->head;pt1;pt1 = pt1->next)
    {
        for (pt2 = poly2->head;pt2;pt2 = pt2->next)
        {
            add_node(mul,pt1->index * pt2->index,pt1->coefficient + pt2->coefficient);
        }
    }

    return mul;
}

Polyhead* poly_sum(Polyhead* poly1,Polyhead* poly2)
{
    Polyhead *sum = make_empty();
    Polynode *pt;
    
    for (pt = poly1->head;pt;pt = pt->next)
    {
        add_node(sum,pt->index,pt->coefficient);
    }
    for (pt = poly2->head;pt;pt = pt->next)
    {
        add_node(sum,pt->index,pt->coefficient);
    }
    return sum;
}

void poly_print(Polyhead* poly)
{
    Polynode *pt = poly->head;
    if (pt){
        for (;pt;pt = pt->next)
        {
            printf("%d %d",pt->index,pt->coefficient);
            if (pt->next){
                printf(" ");
            }
        }
        printf("\n");
    }
    else{
        printf("0 0\n");
    }
}