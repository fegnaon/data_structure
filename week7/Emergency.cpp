#include <iostream>
#include <vector>
#define INF 1000000000

using namespace std;

class city{
    friend class EmergencyMap;
    int NumerOfEmergencyTeam;
};

class EmergencyMap{
public:
    EmergencyMap(int number_of_city);
    void SetNumberOfEmergencyTeam(int city,int n);
    void SetRoad(int city1,int city2,int length);
    void Rescure(int start,int end,int &number_of_path,int &max_number_of_team);
private:
    vector<vector<int>> road;
    vector<city> cities;
};

int main()
{
    int N,M,start,end;
    cin>> N >> M >> start >> end;
    EmergencyMap map(N);
    int number_of_team;
    for (int i = 0; i < N; ++i)
    {
        cin >> number_of_team;
        map.SetNumberOfEmergencyTeam(i,number_of_team);
    }
    int city1,city2,len;
    for (int i = 0; i < M; ++i)
    {
        cin >> city1 >> city2 >> len;
        map.SetRoad(city1,city2,len);
    }

    int number_of_shortest_path,max_number_of_team;
    map.Rescure(start,end,number_of_shortest_path,max_number_of_team);
    cout<< number_of_shortest_path << " " << max_number_of_team << endl;

    return 0;
}

EmergencyMap::EmergencyMap(int number_of_city):
    road(number_of_city,vector<int>(number_of_city,0)),cities(number_of_city,city()) {}

void EmergencyMap::SetNumberOfEmergencyTeam(int city_index,int n)
{
    cities[city_index].NumerOfEmergencyTeam = n;
    return;
}
void EmergencyMap::SetRoad(int city1,int city2,int length)
{
    road[city1][city2] = road[city2][city1] = length;
    return;
}
void EmergencyMap::Rescure(int start,int end,int &number_of_path,int &max_number_of_team)
{
    int size = cities.size();
    vector<int> collected(size,0);
    vector<int> distance(size,INF);
    vector<int> path(size,0);
    vector<int> team(size,0);
    distance[start] = 0;
    path[start] = 1;
    team[start] = cities[start].NumerOfEmergencyTeam;
    int v = start;
    int min,mi,i;
    while (true)
    {
        min = INF;
        for (i = 0; i < size; ++i)
        {
            if (!collected[i] && distance[i] < min){
                min = distance[i];
                mi = i;
            }
        }
        if (mi == end){
            break;
        }
        v = mi;
        collected[v] = 1;

        for (i = 0; i < size; ++i)
        {
            if (!collected[i] && road[v][i]){
                int newdist = distance[v] + road[v][i];
                if (newdist < distance[i]){
                    path[i] = path[v];
                    distance[i] = newdist;
                    team[i] = team[v] + cities[i].NumerOfEmergencyTeam;
                }
                else if (distance[i] == newdist){
                    // TODO:这里为什么+=不是+1
                    path[i] += path[v];
                    if (team[i] <= team[v] + cities[i].NumerOfEmergencyTeam){
                        team[i] = team[v] + cities[i].NumerOfEmergencyTeam;
                    }
                }
            }
        }
    }

    number_of_path = path[mi];
    max_number_of_team = team[mi];

    return;
}