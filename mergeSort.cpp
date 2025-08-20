#include <bits/stdc++.h>
using namespace std;

void print(vector<int> v){
    for (int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

vector<int> merge(vector<int> a, vector<int> b){
    vector<int> merged {};
    int a_idx = 0;
    int b_idx = 0;

    for(int i = 0; i<(a.size() + b.size()); i++){
        if(a_idx >= a.size()){
            merged.push_back(b[b_idx++]);
        }

        else if(b_idx >= b.size()){
            merged.push_back(a[a_idx++]);
        }

        else if(a[a_idx] < b[b_idx]){
            merged.push_back(a[a_idx++]);
        }

        else{
            merged.push_back(b[b_idx++]);
        }
    }

    return merged;
}

vector<int> sort(vector<int> arr){
    if (arr.size() <= 1)
        return arr;
    int mid = (int)(arr.size()/2);
    
    vector<int> left (arr.begin(), arr.begin() + mid);
    left = sort(left);
    vector<int> right (arr.begin() + mid, arr.end());
    right = sort(right);

    return merge(left, right);
}

int main(){
    vector<int> nums = {3,5,6,3,6,8,4,8,9,5,34,65,46,65,64,23,34,65,12};
    print(nums);

    nums = sort(nums);
    print(nums);
}