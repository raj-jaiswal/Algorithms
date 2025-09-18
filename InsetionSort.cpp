#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& vals){
    for(int i=1; i<vals.size(); i++){
        int j=i-1;
        int key = vals[i];
        while(j >= 0 && vals[j] > key){
            vals[j+1] = vals[j];
            j--;
        }
        vals[j+1] = key;
    }
}

int main(){
    vector<int> vals {23,64,12,6,1,74,8,43,7};
    insertionSort(vals);

    for(int i:vals){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}