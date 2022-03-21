#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int *data;
    int max;
    int top;
}Stack;

int push(Stack *stack,int number);
int pop(Stack *stack);

int main()
{
    Stack stack;
    int N,K;
    scanf("%d %d %d\n",&(stack.max),&N,&K);
    stack.data = (int*)malloc(stack.max * sizeof(int) + 1);
    stack.top = -1;

    int i,j,number,lmax,popnumber,tag;
    for (;K;--K)
    {   
        lmax = 0;
        tag = 0;
        for (i = N;i;--i)
        {   
            scanf("%d",&number);
            if (tag == 0){
                if (number > lmax){
                    for (j = lmax + 1;j <= number;++j)
                    {
                        if ((push(&stack,j))){
                            tag = 1;
                            break;
                        }
                    }
                    lmax = number;
                }

                popnumber = pop(&stack);
                if (popnumber != number){
                    tag = 1;
                }
            }
        }

        if (tag){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
        stack.top = -1;
    }

    return 0;
}

int push(Stack *stack,int number)
{   
    stack->top += 1;
    stack->data[stack->top] = number;
    if (stack->top == stack->max){
        return 1;
    }
    return 0;
}

int pop(Stack *stack)
{
    int number = stack->data[stack->top];
    stack->top -= 1;
    return number;
}