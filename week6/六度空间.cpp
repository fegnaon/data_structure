#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

class Net{
public:
    Net(int size):map(size,vector<int>()) {};
    void insert_line(int n1,int n2);
    void Do();
private:
    vector<vector<int>> map;
};

int main()
{
    int N,M,n1,n2;
    cin >> N >> M;
    Net net(N);
    for (int i = 0; i < M; ++i)
    {   
        cin >> n1 >> n2;
        net.insert_line(n1-1,n2-1);
    }
    net.Do();

    return 0;
}

void Net::Do()
{   
    int cnt,layer,v;
    for (auto i = map.begin(); i != map.end(); ++i)
    {
        cnt = 1;
        layer = 0;
        queue<int> q;
        vector<int> visited(map.size(),0);
        visited[distance(map.begin(),i)] = 1;

        for (auto j = i->begin(); j != i->end(); ++j)
        {
            q.push(*j);
            visited[*j] = 1;
        }
        q.push(-1);

        while (layer != 6 && !q.empty())
        {
            v = q.front();
            q.pop();
            if (v == -1){
                q.push(-1);
                ++layer;
                continue;
            }
            ++cnt;
            for (auto k = (map.begin()+v)->begin(),end = (map.begin()+v)->end(); k != end; ++k)
            {
                if (!visited[*k]){
                    q.push(*k);
                    visited[*k] = 1;
                }
            }
        }

        double rate = (double)cnt / (double)map.size() * 100;
        printf("%d: %.2f%\n",distance(map.begin(),i+1),rate);
    }
}

void Net::insert_line(int n1, int n2)
{
    map[n1].push_back(n2);
    map[n2].push_back(n1);
    return;
}