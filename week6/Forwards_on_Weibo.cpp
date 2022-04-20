#include <iostream>
#include <vector>
#include <queue>
#include <iterator>

using namespace std;

class Net{
public:
    Net(int size):map(size,vector<int>()) {};
    void insert_line(int n1,int n2);
    int forwards(int user,int level);
private:
    vector<vector<int>> map;
};

int main()
{
    int N,L,i,j,k;
    cin >> N >> L;
    Net net(N);
    for (i = 0; i < N; ++i)
    {
        cin >> j;
        for (j; j; --j)
        {
            cin >> k;
            net.insert_line(i,k-1);
        }
    }
    
    int K,user;
    cin >> K;
    for (K; K; --K)
    {
        cin >> user;
        cout << net.forwards(user-1,L) << endl;
    }

    return 0;
}

int Net::forwards(int user,int level)
{   
    int cnt,layer,v;

    cnt = 0;
    layer = 0;
    queue<int> q;
    vector<int> visited(map.size(),0);
    visited[user] = 1;

    for (auto j = (map.begin()+user)->begin(); j != (map.begin()+user)->end(); ++j)
    {
        q.push(*j);
        visited[*j] = 1;
    }
    q.push(-1);
    
    while (layer != level && !q.empty())
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

    return cnt;
}

void Net::insert_line(int n1, int n2)
{
    map[n2].push_back(n1);
    return;
}