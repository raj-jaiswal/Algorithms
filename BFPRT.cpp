#include <bits/stdc++.h>
using namespace std;

void print(vector<int> vals){
    for(int i=0; i<vals.size(); i++){
        cout << vals[i] << " ";
    }
    cout << endl;
}

int BFPRT(vector<int> vals, int k){
    if(vals.size() <= 5){
        sort(vals.begin(), vals.end());
        return vals[k-1];
    }

    vector<vector<int>> groups {};
    for(int i=0; i<vals.size(); i++){
        if(i%5 == 0){
            vector<int> empty {};
            groups.push_back(empty);
        }

        groups[(int) (i/5)].push_back(vals[i]);
    }

    vector<int> medians {};
    for(int i=0; i<groups.size(); i++){
        medians.push_back(BFPRT(groups[i], groups[i].size()/2));
    }

    int pivot = BFPRT(medians, medians.size()/2);
    vector<int> left, right, equal;
    for (int v : vals) {
        if (v < pivot) left.push_back(v);
        else if (v > pivot) right.push_back(v);
        else equal.push_back(v);  // includes pivot itself
    }

    if (k <= left.size())
        return BFPRT(left, k);
    else if (k <= left.size() + equal.size())
        return pivot;  // kth element is the pivot
    else
        return BFPRT(right, k - left.size() - equal.size());
}

int main(){
    vector<int> vals {2,4,5,6,52,21,43,23,5,32,23,1,43,54,75,34,23,45,76,86,45};
    int k = 3;

    cout << BFPRT(vals, k);
}