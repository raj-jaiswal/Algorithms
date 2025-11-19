#include <bits/stdc++.h>
using namespace std;

#define M 127

int power(int base, int p){
    if(p==0) return 1;
    if(p%2==0){
        int half = power(base, p/2) % M;
        return (half * half) % M;
    }

    return ((base % M) * (power(base, p-1) % M)) % M;
}

int hasher(string s, int p){
    int sum = 0;
    for(int i=0; i<s.size(); i++){
        sum += (((s[i] - 'a') % M) * power(p, s.size()-1-i)) % M;
    }
    return sum % M;
}

int main(){
    string A, B;
    int p = 29;
    cout << "Enter Strings: " << endl;
    cin >> A;
    cin >> B;

    if(B.size() > A.size()){
        cerr << "B must be smaller than A." << endl;
        exit(1);
    }

    int hashVal = hasher(B, p);

    int next = hasher(string(A.begin(), A.begin() + B.size()), p);
    cout << hashVal << endl;
    
    for(int i=0; i <= A.size()-B.size(); i++){
        if(next == hashVal){
            cout << i << ": " << string(A.begin() + i, A.begin() + B.size() + i) << endl;
        }

        next -= ((A[i] - 'a') % M * power(p, B.size()-1)) % M;
        if (next < 0) next += M;
        next = ((next) * p) % M;
        next += (A[i+B.size()] - 'a');
        next %= M;
    }

    return 0;
}