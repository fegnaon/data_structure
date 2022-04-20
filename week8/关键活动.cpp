#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define INF 100000000

using namespace std;

int main()
{
    int N,M;
    cin >> N >> M;
    vector<vector<int>> edge(N,vector<int>(N,-1));
    vector<vector<int>> out(N,vector<int>());
    vector<int> inDegree(N,0);
    map<pair<int,int>,int> input;
    int start,end,time;
    for (int i = 0; i < M; ++i)
    {
        cin >> start >> end >> time;
        --start,--end;
        edge[start][end] = time;
        out[start].push_back(end);
        ++inDegree[end];
        input[pair<int,int>(start,end)] = i;
    }

    vector<int> earliestTime(N,-1);
    vector<vector<int>> front(N,vector<int>());
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
                front[o].clear();
                front[o].push_back(v);
            }
            else if(earliestTime[o] == earliestTime[v] + edge[v][o]){
                front[o].push_back(v);
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
            while (!todo.empty()) todo.pop();
            todo.push(i);
        }
        else if (max == earliestTime[i]){
            todo.push(i);
        }
        if (earliestTime[i] < 0){
            max = -1;
            break;
        }
    }
    if (max < 0){
        cout << 0 << endl;
    }
    else{
        cout << max << endl;

        auto f = [&input](pair<int,int> a,pair<int,int> b) -> bool
            {if (a.first == b.first) return input[a] > input[b];else return a.first < b.first;};
        set<pair<int,int>,decltype(f)> keyPath(f);
        int v;
        while (!todo.empty())
        {
            v = todo.front();
            todo.pop();
            for (int i = 0; i < front[v].size(); ++i)
            {
                keyPath.insert(pair<int,int>(front[v][i],v));
                todo.push(front[v][i]);
            }
        }
        for (auto i:keyPath)
        {
            cout << i.first+1 << "->" << i.second+1 << endl;
        }
    }

    return 0;
}