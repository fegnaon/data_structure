//TODO:再写另一种解法
#include <iostream>
#include <vector>
#define INF 100000000

using namespace std;

int main()
{
    int N,M;
    cin >> N >> M;
    vector<vector<int>> cities(N,vector<int>(N,0));
    int c1,c2,cost;
    for (int i = 0; i < M; ++i)
    {
        cin >> c1 >> c2 >> cost;
        cities[c1-1][c2-1] = cities[c2-1][c1-1] = cost;
    }

    vector<int> dist(N,INF);
    dist[0] = 0;
    for (int i = 0; i < N; dist[i] = cities[0][i] ? cities[0][i] : dist[i],++i);
    int collected = 1,totalcost = 0;

    while (true)
    {
        int min = INF,mi = -1;
        for (int i = 0; i < N; ++i)
        {
            if (dist[i] && dist[i] < min){
                min = dist[i];
                mi = i;
            }
        }
        if (mi < 0) break;

        ++collected;
        totalcost += dist[mi];
        dist[mi] = 0;
        for (int i = 0; i < N; dist[i] = (cities[mi][i] && cities[mi][i] < dist[i]) ? cities[mi][i] : dist[i],++i);
    }

    cout << ((collected == N) ? totalcost : -1) << endl;
    return 0;
}