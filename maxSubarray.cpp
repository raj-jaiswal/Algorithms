#include <bits/stdc++.h>
using namespace std;

class MaxRange{
private:
    int a;
    int b;

public:
    int sum;

    void set(int start, int end, int s){
        a = start;
        b = end;
        sum = s;
    }
    
    void print(vector<int> arr){
        cout << "Range: " << a << ", " << b << endl;
        cout << "Values: ";
        for(int i=a; i<=b; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "sum: " << sum << endl;
    }
};

MaxRange search(vector<int> vals, int a, int b){
    if (a==b){
        MaxRange maxObj;
        maxObj.set(a, a, vals[a]);
        return maxObj;
    }
    
    int mid = (int) ((a+b)/2);
    MaxRange left = search(vals, a, mid);
    MaxRange right = search(vals, mid+1, b);

    int start = mid;
    int end = mid+1;
    
    int maxlSum = -(int) INFINITY;
    int lsum = 0;
    for(int i = mid; i>=a; i--){
        lsum += vals[i];
        if(lsum > maxlSum){
            maxlSum = lsum;
            start = i;
        }
    }

    int maxrSum = -(int) INFINITY;
    int rsum = 0;
    for(int i = mid + 1; i<=b; i++){
        rsum += vals[i];
        if(rsum > maxrSum){
            maxrSum = rsum;
            end = i;
        }
    }

    int sum = maxlSum + maxrSum;
    if(sum > left.sum && sum > right.sum){
        MaxRange maxObj;
        maxObj.set(start, end, sum);
        return maxObj;
    }

    if (left.sum > right.sum)
        return left;
    else   
        return right;
}

int main(){
    vector<int> vals {2,4,-2,1,-2,6,-1,2,-6,-7,9,1,-4};
    MaxRange maxSubarray = search(vals, 0, vals.size()-1);
    maxSubarray.print(vals);

    return 0;
}