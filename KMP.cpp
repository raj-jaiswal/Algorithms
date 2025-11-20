#include <bits/stdc++.h>
using namespace std;

vector<int> buildLPS(const string &pat){
    int m = pat.size();
    vector<int> lps(m, 0);

    int len = 0;          // length of the previous longest prefix suffix
    int i = 1;            // lps[0] is always 0

    while(i < m){
        if(pat[i] == pat[len]){
            len++;
            lps[i] = len;
            i++;
        }else{
            if(len != 0){
                len = lps[len - 1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

int main(){
    string A, B;
    cout << "Enter Strings: " << endl;
    cin >> A;
    cin >> B;

    if(B.size() > A.size()){
        cerr << "B must be smaller than A." << endl;
        exit(1);
    }

    vector<int> lps = buildLPS(B);

    int n = A.size();
    int m = B.size();

    int i = 0;  // index for A
    int j = 0;  // index for B

    while(i < n){
        if(A[i] == B[j]){
            i++;
            j++;
        }

        if(j == m){
            int start = i - j;
            cout << start << ": " 
                 << string(A.begin() + start, A.begin() + start + m) 
                 << endl;
            j = lps[j - 1];
        }else if(i < n && A[i] != B[j]){
            if(j != 0){
                j = lps[j - 1];
            }else{
                i++;
            }
        }
    }

    return 0;
}
