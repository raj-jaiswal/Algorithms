#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> A, pair<int, int> B){
    if (A.first != B.first){
        return A.first < B.first;
    }

    return A.second > B.second;
}

int findMin(vector<pair<int, int>> tasks, int n){
    int idx = 0;
    int min = tasks[0].second;
    int t=1;

    for(int i=0; i<tasks.size(); i++){
        if(t>n) break;
        if(tasks[i].second < min){
            idx = i;
            min = tasks[i].second;
        }
        t++;
    }
    return idx;
}

int main(){
    vector<pair<int, int>> tasks;
    vector<pair<int, int>> chosen;
    vector<pair<int, int>> skipped;
    int n;

    cout << "Enter number of tasks: ";
    cin >> n;

    cout << "Enter tasks (deadline reward): " << endl;
    for(int i=0; i<n; i++){
        pair<int, int> task;
        cin >> task.first >> task.second;

        tasks.push_back(task);
    }
    sort(tasks.begin(), tasks.end(), cmp);

    int t=1;
    for(int i=0; i<tasks.size(); i++){
        if(tasks[i].first >= t){
            chosen.push_back(tasks[i]);
            t++;
        }
        else{
            skipped.push_back(tasks[i]);
        }
    }

    for(int i=0; i<skipped.size(); i++){
        pair<int, int> task = skipped[i];
        int replaceIdx = findMin(chosen, task.first);
        if(chosen[replaceIdx].second < task.second){
            chosen[replaceIdx] = task;
        }
    }

    int sum = 0;
    for(int i=0; i<chosen.size(); i++){
        cout << "time: " << i+1 << "\tdeadline: " << chosen[i].first << "\treward: " << chosen[i].second << endl;
        sum += chosen[i].second;
    }

    cout << "total reward: " << sum << endl;
    return 0;
}