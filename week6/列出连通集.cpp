#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Map{
public:
    Map(unsigned int size);
    void print();
    void DFS();
    void BFS();
    int insert(int v1,int v2);
private:
    int number_of_vertex;
    vector<vector<int>> map;
};

int main()
{
    int N,E,v1,v2;
    cin >> N >> E;
    Map map(N);
    for (int i = 0; i < E; ++i)
    {
        cin >> v1 >> v2;
        map.insert(v1,v2);
    }
    map.DFS();
    map.BFS();

    return 0;
}

Map::Map(unsigned int size)           
{   
    number_of_vertex = size;
    map.insert(map.end(),size,vector<int>(size,0));
    return;
}

void Map::print()
{
    for (auto i:map)
    {
        for (auto j:i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    return;
}

int Map::insert(int v1,int v2)
{
    if (v1 > number_of_vertex || v2 > number_of_vertex || v1 < 0 || v2 < 0){
        return 0;
    }
    else{
        map[v2][v1] = map[v1][v2] = 1;
        return 1;
    }
}

void Map::DFS()
{
    vector<int> visited(number_of_vertex,-1);
    vector<int> print;
    int vertex,start;
    int i,tag;

    while (true)
    {   
        tag = 0;
        for (i = 0; i < number_of_vertex; ++i)
        {
            if (visited[i] < 0){
                tag = 1;
                break;
            }
        }
        if (!tag){
            break;
        }
        visited[i] = i;
        start = vertex = i;
        cout << "{ ";
        print.push_back(start);
        while(true)
        {   
            tag = 0;
            for (i = 0; i < number_of_vertex; ++i)
            {
                if (map[vertex][i] && visited[i] < 0){
                    tag = 1;
                    break;
                }
            }
            if (!tag && vertex == start){
                break;
            }
            if (tag){
                visited[i] = vertex;
                vertex = i;
                print.push_back(vertex);
            }
            else{
                vertex = visited[vertex];
            }
        }

        for (auto i:print)
        {
            cout << i << " ";
        }
        cout << "}" << endl;
        print.clear();
    }

    return;
}

void Map::BFS()
{
    vector<int> visited(number_of_vertex,-1);
    vector<int> print;
    int vertex,start;
    int i,tag;

    while (true)
    {   
        tag = 0;
        for (i = 0; i < number_of_vertex; ++i)
        {
            if (visited[i] < 0){
                tag = 1;
                break;
            }
        }
        if (!tag){
            break;
        }
        visited[i] = i;
        start = vertex = i;

        queue<int> q;
        q.push(start);
        cout << "{ ";
        print.push_back(start);
        while(!q.empty())
        {   
            vertex = q.front();
            q.pop();
            for (i = 0; i < number_of_vertex; ++i)
            {
                if (map[vertex][i] && visited[i] < 0){
                    visited[i] = vertex;
                    q.push(i);
                    print.push_back(i);
                }
            }
        }

        for (auto i:print)
        {
            cout << i << " ";
        }
        cout << "}" << endl;
        print.clear();
    }

    return;
}