#include <iostream>
#include <vector>
#include <queue>
#define INF 100000000

using namespace std;

int main()
{
    int N,M;
    cin >> N >> M;
    vector<vector<int>> edge(N,vector<int>(N,-1));
    vector<vector<int>> out(N,vector<int>());
    vector<int> inDegree(N,0);
    int start,end,time;
    for (int i = 0; i < M; ++i)
    {
        cin >> start >> end >> time;
        edge[start][end] = time;
        out[start].push_back(end);
        ++inDegree[end];
    }

    vector<int> earliestTime(N,-1);
    queue<int> todo;
    for (int i = 0; i < N; ++i)
    {
        if (inDegree[i] == 0){
            todo.push(i);
            earliestTime[i] = 0;
        }
    }

    while(!todo.empty())
    {
        int v = todo.front();
        todo.pop();
        for (int i = 0; i < out[v].size(); ++i)
        {
            int o = out[v][i];
            --inDegree[o];
            if (earliestTime[o] < earliestTime[v] + edge[v][o]){
                earliestTime[o] = earliestTime[v] + edge[v][o];
            }
            if (inDegree[o] == 0){
                todo.push(o);
            }
        }
    }

    int max = -1;
    for (int i = 0; i < N; ++i)
    {
        if (max < earliestTime[i]){
            max = earliestTime[i];
        }
        if (earliestTime[i] < 0){
            max = -1;
            break;
        }
    }
    if (max < 0){
        cout << "Impossible" << endl;
    }
    else{
        cout << max;
    }

    return 0;
}