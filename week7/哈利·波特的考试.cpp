// TODO:用多源最短路重写
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Answer{
    int Animal;
    int maxlen;
};

class Map{
public:
    Map(int size):
        map( vector<vector<int>> (size,vector<int>(size,0)) ) {}
    void InsertSpell(int a1,int a2,int len);
    Answer CatchAnimal();
private:

    vector<vector<int>> map;
};

int main()
{
    int N,M;
    cin >> N >> M;
    int a1,a2,len;
    Map allspell(N);
    for (int i = 0; i < M; ++i)
    {
        cin >> a1 >> a2 >> len;
        allspell.InsertSpell(a1,a2,len);
    }
    Answer answer = allspell.CatchAnimal();
    if (answer.Animal == -1){
        cout << 0 << endl;
    }
    else{
        cout << answer.Animal+1 << " " << answer.maxlen << endl;
    }

    return 0;
}

void Map::InsertSpell(int a1,int a2,int len)
{
    map[a1-1][a2-1] = map[a2-1][a1-1] = len;
    return;
}

int comparespell(pair<int,int> a1,pair<int,int> a2)
{
    return a1.second > a2.second;
}

Answer Map::CatchAnimal()
{
    Answer answer{-1,INT_MAX};
    for (int i = 0; i < map.size(); ++i)
    {
        vector<int> collected(map.size(),0),dist(map.size(),INT_MAX);
        dist[i] = 0;
        int min,v;

        while (true)
        {
            int i;
            for (i = 0,min = INT_MAX; i < collected.size(); ++i)
            {
                if (dist[i] < min && !collected[i]){
                    min = dist[i];
                    v = i;
                }
            }
            if (min == INT_MAX){
                break;
            }
            collected[v] = 1;

            for (i = 0; i < collected.size(); ++i)
            {
                if (map[v][i]){
                    if (!collected[i] && dist[i] > dist[v] + map[v][i]){
                        dist[i] = dist[v] + map[v][i];
                    }
                }
            }
        }

        int tag = 0;
        for (int i = 0; i < collected.size(); ++i)
        {
            if (!collected[i]){
                tag = 1;
                break;
            }
        }
        if (tag){
            answer.Animal = -1;
            break;
        }

        if (dist[v] < answer.maxlen){
            answer.Animal = i;
            answer.maxlen = dist[v];
        }
    }

    return answer;
}