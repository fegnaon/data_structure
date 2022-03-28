#include <stdio.h>
#include <string.h>

int main()
{
    int N;
    scanf("%d",&N);

    int computers[N+1];
    for (int i = 0; i <= N; ++i)
    {
        computers[i] = -1;
    }

    char command[2];
    int c1,c2;
    while (1)
    {
        scanf("%s",command);
        if (!strcmp(command,"S")){
            break;
        }

        scanf("%d %d",&c1,&c2);
        if (!strcmp(command,"I")){
            for (c1; computers[c1] > 0; c1 = computers[c1]);
            for (c2; computers[c2] > 0; c2 = computers[c2]);
            if (c1 != c2){
                if (computers[c1] < computers[c2]){
                    computers[c2] = c1;
                }
                else if (computers[c1] > computers[c2]){
                    computers[c1] = c2;
                }
                else{
                    computers[c2] = c1;
                    --computers[c1];
                }
            }
        }
        else{
            for (c1; computers[c1] > 0; c1 = computers[c1]);
            for (c2; computers[c2] > 0; c2 = computers[c2]);
            if (c1 == c2){
                printf("yes\n");
            }
            else{
                printf("no\n");
            }
        }
    }

    int k = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (computers[i] < 0){
            ++k;
        }
    }
    if (k == 1){
        printf("The network is connected.\n");
    }
    else{
        printf("There are %d components.\n",k);
    }

    return 0;
}