#include <bits/stdc++.h>
using namespace std;

string longestCommonSubsequence(string A, string B){
    vector<vector<int>> mat (A.size()+1, vector<int> (B.size()+1, 0));
    for(int i=1; i<=A.size(); i++){
        for(int j=1; j<=B.size(); j++){
            if(A[i-1] == B[j-1]){
                mat[i][j] = mat[i-1][j-1] + 1;
            }
            else{
                mat[i][j] = max(mat[i-1][j], mat[i][j-1]);
            }
        }
    }

    cout << "Subsequence Matrix: " << endl;
    for(int i=0; i<=A.size(); i++){
        for(int j=0; j<=B.size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    string LCS;
    int i=A.size();
    int j=B.size();

    while(i>0 && j>0){
        if(A[i-1] == B[j-1]){
            LCS.push_back(A[i-1]);
            i--;
            j--;
        }
        else{
            if(mat[i-1][j] > mat[i][j-1]) i--;
            else j--;
        }
    }

    reverse(LCS.begin(), LCS.end());
    return LCS;
}

int main(){
    string A, B;

    cout << "Enter the two strings: " << endl;
    cin >> A;
    cin >> B;

    cout << longestCommonSubsequence(A, B) << endl;
    return 0;
}