#include <iostream>
#include <limits.h>
#include <vector>
#include <math.h>

using namespace std;

struct position{
    int x;
    int y;
    int operator==(position p){return p.x == x && p.y == y;}
};

class Path{
public:
    Path() {}
    Path(vector<position> p):path(p){}
    void print_path();
private:
    vector<position> path;
};

class Lake{
public:
    Lake():crocodiles{{INT_MAX,INT_MAX}},origin{0,0} {};
    void insert(int x,int y);
    Path escape(int steplen);
private:
    vector<position> crocodiles;
    position origin;

    double distance(position p1,position p2)
    {
        double dist;
        if (p1.x == INT_MAX){
            dist = distance_to_border(p2);
        }
        else if (p2.x == INT_MAX){
            dist = distance_to_border(p1);
        }
        else{
            dist = sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
        }

        if (p1 == origin){
            return dist - 7.5;
        }
        else if (p2 == origin){
            return dist - 7.5;
        }
        else{
            return dist;
        }
    }
    int distance_to_border(position p)
    {
        int a = abs(50-p.x),b = abs(-50-p.x),c = abs(50-p.y),d = abs(-50-p.y);
        int min = (a<b?a:b)<(c<d?c:d)?(a<b?a:b):(c<d?c:d);
        return min;
    }
};

int main()
{
    Lake lake;
    int N,D,i,x,y;
    cin >> N >> D;
    for ( i = 0; i < N; ++i)
    {
        cin >> x >> y;
        lake.insert(x,y);
    }

    Path path = lake.escape(D);
    path.print_path();

    return 0;
}

void Lake::insert(int x,int y)
{
    if (distance(position({x,y}),origin) <= 0 || x >= 50 || y >= 50 || x <= -50 || y <= -50){
        return;
    }
    crocodiles.push_back(position({x,y}));
    return;
}

Path Lake::escape(int steplen)
{
    int i;
    int size = crocodiles.size();
    double minifirst = 1000;
    vector<position> p;
    int min = 1000;
    for (i = 0;i < size; ++i)
    {
        if (distance(crocodiles[i],origin) <= steplen){
            vector<int> dist(size,1000);
            vector<int> visited(size,0);
            dist[i] = 1;
            visited[i] = -i;
            int v = i,mi;

            while (true)
            {
                int i,min = 1000;
                mi = -1;
                for (i = 0; i < size; ++i)
                {
                    if(visited[i] <= 0 && dist[i] < min){
                        min = dist[i];
                        mi = i;
                    }
                }
                if (mi == -1){
                    break;
                }
                else if (mi == 0){
                    visited[mi] = -visited[mi];
                    break;
                }
                visited[mi] = -visited[mi];
                v = mi;

                for (i = 0; i < size; ++i)
                {
                    if (visited[i] <= 0 && distance(crocodiles[i],crocodiles[v]) <= steplen){
                        if (dist[v] + 1 < dist[i]){
                            dist[i] = dist[v] + 1;
                            visited[i] = -v;
                        }
                    }
                }
            }

            if (!mi){
                if (dist[0] < min || (dist[0] == min && distance(origin,crocodiles[i]) < minifirst)){
                    min = dist[0];
                    p.clear();
                    int j;
                    for (j = 0; j != visited[j]; j = visited[j],p.push_back(crocodiles[j]));
                    minifirst = distance(origin,crocodiles[i]);
                }
            }
        }
    }
    vector<position> result;
    if (min != 1000){
        result.push_back(position({0,0}));
        for (auto i = p.rbegin();i != p.rend(); ++i)
        {
            result.push_back(*i);
        }
    }
    return Path(result);
}

void Path::print_path()
{
    if (path.empty()){
        cout << 0 << endl;
    }
    else{
        cout << path.size() << endl;
        for (auto i = path.begin()+1;i != path.end(); ++i)
        {
            cout << i->x << " " << i->y << endl;
        }
    }

    return;
}