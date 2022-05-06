#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> year(N+1,0);
    int data;
    for (int i = 0; i < N; ++i)
    {
        cin >> data;
        ++year[data];
    }
    for (int i = 0; i <= N; ++i)
    {
        // if (year[i]){
            cout << i << ":" << year[i] << "\n";
        // }
    }
    return 0;
}