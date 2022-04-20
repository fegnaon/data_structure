//TODO:重写
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits.h>
#define LIM 1000000

using namespace std;
using Path = vector<int>;
int path_index = 0;

class RoadMap{
    friend Path FindCheapestWay(const RoadMap &roadmap,shared_ptr<vector<Path>> pathes);
    friend int CalculateToll(const RoadMap &roadmap,Path path);
    friend int CalculateDistance(const RoadMap &roadmap,Path path);
public:
    RoadMap() {}
    RoadMap(int number_of_city):
        distance(number_of_city,vector<int>(number_of_city,0)),
        toll(number_of_city,vector<int>(number_of_city,0)) {}

    RoadMap& BuildWay(int city1,int city2,int len);
    RoadMap& SetToll(int city1,int city2,int toll);
    shared_ptr<vector<Path>> FindShortestWay(int city1,int city2) const;
private:
    vector<vector<int>> distance;
    vector<vector<int>> toll;
    shared_ptr<vector<Path>> GeneratePathes(int des,int pos,const vector<vector<int>> &path,
        const vector<int> &number_of_pre,shared_ptr<vector<Path>> pathes,int path_index) const;
};
int CalculateToll(const RoadMap &roadmap,Path path);
int CalculateDistance(const RoadMap &roadmap,Path path);
Path FindCheapestWay(const RoadMap &roadmap,shared_ptr<vector<Path>> pathes);

int main()
{
    int N,M,S,D;
    cin >> N >> M >> S >> D;
    RoadMap roadmap(N);
    int city1,city2,distance,toll;
    for (int i = 0; i < M; ++i)
    {
        cin >> city1 >> city2 >> distance >> toll;
        roadmap.BuildWay(city1,city2,distance).SetToll(city1,city2,toll);
    }
    Path path = FindCheapestWay(roadmap,roadmap.FindShortestWay(S,D));
    cout << CalculateDistance(roadmap,path) << " " << CalculateToll(roadmap,path) << endl;
    return 0;
}

int CalculateToll(const RoadMap &roadmap,Path path)
{
    if (path.size() < 2)
        return -1;

    int toll = 0;
    for (auto s = path.begin(),d = path.begin()+1; d != path.end(); ++s,++d)
    {
        toll += roadmap.toll[*s][*d];
    }
    return toll;
}

int CalculateDistance(const RoadMap &roadmap,Path path)
{
    if (path.size() < 2)
        return -1;

    int distance = 0;
    for (auto s = path.begin(),d = path.begin()+1; d != path.end(); ++s,++d)
    {
        distance += roadmap.distance[*s][*d];
    }
    return distance;
}

Path FindCheapestWay(const RoadMap &roadmap,shared_ptr<vector<Path>> pathes)
{
    int cheapest = 0,cheapest_toll = CalculateToll(roadmap,(*pathes)[0]);
    int toll,i;
    for (i = 1; i < pathes->size(); ++i)
    {
        toll = CalculateToll(roadmap,(*pathes)[i]);
        if (toll < cheapest_toll){
            cheapest = i;
            cheapest_toll = toll;
        }
    }

    return (*pathes)[cheapest];
}

RoadMap& RoadMap::BuildWay(int city1,int city2,int len)
{
    distance[city1][city2] = distance[city2][city1] = len;
    return *this;
}

RoadMap& RoadMap::SetToll(int city1,int city2,int toll)
{
    this->toll[city1][city2] = this->toll[city2][city1] = toll;
    return *this;
}

shared_ptr<vector<Path>> RoadMap::FindShortestWay(int city1,int city2) const
{
    int size = distance.size();
    vector<vector<int>> visited(size,vector<int>());
    vector<int> number_of_pre(size,2);
    vector<int> dist(size,LIM);

    dist[city1] = 0;
    visited[city1].push_back(city1);

    int min,mi,i,v = city1;
    while (true)
    {
        for (min = LIM,mi = -1,i = 0; i < size; ++i)
        {
            if (visited[i].size() != number_of_pre[i] && dist[i] < min){
                min = dist[i];
                mi = i;
            }
        }
        if (mi == city2){
            --number_of_pre[mi];
            break;
        }
        else if (mi < 0){
            break;
        }
        --number_of_pre[mi];
        v = mi;

        for (i = 0; i < size; ++i)
        {
            if (visited[i].size() != number_of_pre[i] && distance[v][i]){
                if (dist[i] > dist[v] + distance[v][i]){
                    dist[i] = dist[v] + distance[v][i];
                    visited[i].clear();
                    visited[i].push_back(v);
                    number_of_pre[i] = 2;
                }
                else if (dist[i] == dist[v] + distance[v][i]){
                    visited[i].push_back(v);
                    ++number_of_pre[i];
                }
            }
        }
    }
    shared_ptr<vector<Path>> pathes = make_shared<vector<Path>>();
    path_index = 0;
    GeneratePathes(city2,city2,visited,number_of_pre,pathes,path_index);

    return pathes;
}

shared_ptr<vector<Path>> RoadMap::GeneratePathes(int des,int pos,const vector<vector<int>> &path,
    const vector<int> &number_of_pre,shared_ptr<vector<Path>> pathes,int index) const
{
    if (pathes->size() == 0){
        pathes->push_back(Path());
    }

    if (pos == path[pos][0]){
        reverse((*pathes)[index].begin(),(*pathes)[index].end());
        (*pathes)[index].push_back(des);
        return pathes;
    }

    for (int i = 1; i < number_of_pre[pos]; ++i)
    {
        pathes->push_back((*pathes)[index]);
        (*pathes)[++path_index].push_back(path[pos][i]);
        GeneratePathes(des,path[pos][i],path,number_of_pre,pathes,path_index);
    }
    (*pathes)[index].push_back(path[pos][0]);
    GeneratePathes(des,path[pos][0],path,number_of_pre,pathes,index);

    return pathes;
}