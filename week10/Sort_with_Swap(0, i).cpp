#include <iostream>
#include <vector>

using namespace std;

void swap(int &a,int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

int main()
{
    int N;
    cin >> N;
    vector<int> input(N,0);
    int number;
    for (int i = 0; i < N; ++i)
    {
        cin >> number;
        input[i] = number;
    }

    int step = 0,i,tmp;

    vector<int> visited(N,0);
    for (i = 0; i < N; ++i)
    {
        if (input[i] != i && !visited[i]){
            int len = 0;
            for (tmp = i; !visited[tmp]; tmp = input[tmp])
            {
                visited[tmp] = 1;
                ++len;
            }
            step += len + 1;
        }
    }
    if (input[0] != 0 && step != 0){
        step -= 2;
    }

    cout << step;

    return 0;
}