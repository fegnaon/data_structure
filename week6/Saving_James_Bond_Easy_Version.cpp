#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Lake{
public:
    Lake() {};
    void insert(int x,int y);
    int jump(int len);
private:
    typedef struct {
        int x;
        int y;
    }position;
    vector<position> crocodiles;
    int number_of_crocodile = 0;

    int distance(position p1,position p2)
    {   
        double dist = sqrt(pow((p1.x-p2.x),2) + pow((p1.y-p2.y),2));
        if (dist == int(dist)){
            return int(dist);
        }
        else{
            return int(dist+1);
        }
    }
    int distance_to_border(position p)
    {
        int a = abs(50-p.x),b = abs(-49-p.x),c = abs(50-p.y),d = abs(-49-p.y);
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
    if (lake.jump(D)){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
}

void Lake::insert(int x,int y)
{
    crocodiles.push_back(position({x,y}));
    ++number_of_crocodile;
    return;
}

int Lake::jump(int len)
{
    vector<int> visited(number_of_crocodile,-1);
    int vertex,tag,i,first = 0,escape = 0;

    if (distance_to_border(position({0,0})) <= (len+15)){
        escape = 1;
    }

    while(true)
    {   
        tag = 0;
        for ( first; first < number_of_crocodile; ++first)
        {
            if (distance(crocodiles[first],position({0,0})) <= (len + 15) && visited[first] < 0){
                tag = 1;
                break;
            }
        }
        if (!tag){
            break;
        }

        vertex = first;
        visited[first] = first;
        if (distance_to_border(crocodiles[vertex]) <= len){
            escape = 1;
        }
        while(true)
        {
            tag = 0;
            for ( i = 0; i < number_of_crocodile; ++i)
            {
                if (visited[i] < 0){
                    if (distance(crocodiles[vertex],crocodiles[i]) <= len){
                        tag = 1;
                        break;
                    }
                }
            }
            if (vertex == visited[vertex] && tag == 0){
                break;
            }
            if (tag){
                visited[i] = vertex;
                vertex = i;
                if (distance_to_border(crocodiles[vertex]) <= len){
                    escape = 1;
                }
            }
            else{
                vertex = visited[vertex];
            }
        }

    }

    return escape;
}