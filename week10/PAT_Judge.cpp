#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#define space ' '

using namespace std;

struct User{
    User(int n):perfectSlove(0),totalScore(0),problemsScore(n,-1),val(0) {}
    int ID;
    int perfectSlove;
    int totalScore;
    int val;
    vector<int> problemsScore;
};

int operator<(User u1,User u2)
{
    if (u1.totalScore == u2.totalScore){
        if (u1.perfectSlove == u2.perfectSlove){
            return u1.ID > u2.ID;
        }
        return u1.perfectSlove < u2.perfectSlove;
    }
    return u1.totalScore < u2.totalScore;
}

bool cmp(User a,User b){
    if(a.totalScore > b.totalScore){
        return true;
    }
    else if(a.totalScore == b.totalScore){
        if(a.perfectSlove > b.perfectSlove){
            return true;
        }
        else if(a.perfectSlove == b.perfectSlove){
            return a.ID < b.ID;
        }
    }
    return false;
}

int main()
{
    int numberofUsers,numberofProblems,numberofSubmissions,i,j;
    cin >> numberofUsers >> numberofProblems >> numberofSubmissions;
    vector<int> fullScore(numberofProblems+1);
    vector<User> allUser(numberofUsers+1,numberofProblems+1);
    for (i = 1; i <= numberofUsers; ++i)
    {
        allUser[i].ID = i;
    }

    int data;
    for (i = 1; i <= numberofProblems; ++i)
    {
        cin >> data;
        fullScore[i] = data;
    }

    int userID,problemID,partialScoreObtained;
    for (i = 0; i < numberofSubmissions; ++i)
    {
        cin >> userID >> problemID >> partialScoreObtained;
        if (partialScoreObtained >= 0){
            allUser[userID].val = 1;
        }
        if (allUser[userID].problemsScore[problemID] <= 0 && partialScoreObtained <= 0){
            allUser[userID].problemsScore[problemID] = 0;
            continue;
        }
        if (allUser[userID].problemsScore[problemID] >= partialScoreObtained){
            continue;
        }
        if (allUser[userID].problemsScore[problemID] != -1){
            allUser[userID].totalScore -= allUser[userID].problemsScore[problemID];
        }
        allUser[userID].totalScore += partialScoreObtained;
        allUser[userID].problemsScore[problemID] = partialScoreObtained;
        if (partialScoreObtained == fullScore[problemID]){
            ++allUser[userID].perfectSlove;
        }
    }

    // vector<int> ranklist(numberofUsers+1);
    // int tmp;
    // ranklist[1] = 1;
    // for (i = 2; i <= numberofUsers; ++i)
    // {
    //     tmp = i;
    //     for (; allUser[ranklist[tmp-1]] < allUser[i] && tmp != 1; --tmp)
    //     {
    //         ranklist[tmp] = ranklist[tmp-1];
    //     }
    //     ranklist[tmp] = i;
    // }

    sort(allUser.begin()+1,allUser.end(),cmp);

    cout << setfill('0');
    int rank = 1;
    for (i = 1; i <= numberofUsers && allUser[i].val != 0; ++i)
    {
        if (i != 1 && allUser[i].totalScore != allUser[i-1].totalScore){
            rank = i;
        }
        printf("%d %05d %d",rank,allUser[i].ID,allUser[i].totalScore);
        for (j = 1; j <= numberofProblems; ++j)
        {
            if (allUser[i].problemsScore[j] >= 0){
                printf(" %d",allUser[i].problemsScore[j]);
            }
            else{
                cout << " -";
            }
        }
        cout << "\n";
    }

    return 0;
}