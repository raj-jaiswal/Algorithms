#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<float, float> A, pair<float, float> B){
    return A.first > B.first;
}

int main(){
    int n;
    cout << "Enter Number of items" << endl;
    cin >> n;

    vector<pair<float, float>> knapsack;

    cout << "Enter price and amt: " << endl;
    for(int i=0; i<n; i++){
        pair<float, float> item;
        int p, a;
        cin >> p >> a;
        item.first = (1.0 * p) / a;
        item.second = a;

        knapsack.push_back(item);
    }

    sort(knapsack.begin(), knapsack.end(), cmp);

    for(int i=0; i<n; i++){
        cout << "price per piece: " << knapsack[i].first << "\tamount: " << knapsack[i].second << endl;
    }

    int capacity;
    float price = 0.0;
    cout << "Enter capacity: ";
    cin >> capacity;

    int i=0;
    while(capacity != 0 && i<knapsack.size()){
        if(capacity > knapsack[i].second){
            price += knapsack[i].first * knapsack[i].second;
            capacity -= knapsack[i].second;
        }
        else{
            price += (1.0 * capacity) * knapsack[i].first;
            break;
        }
        i++;
    }

    cout << "Final Price: " << price << endl;
}