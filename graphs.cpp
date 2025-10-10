#include <bits/stdc++.h>
using namespace std;

class Graph{
private:
    vector<vector<int>> Mat;
    int nNodes;
    int nEdges;

    void DFS(int node, vector<bool>& visited){
        stack<int> s;
        s.push(node);
        visited[node] = 1;

        while(!s.empty()){
            node = s.top();
            cout << node << " ";
            s.pop();

            for(int i=0; i<nNodes; i++){
                if(Mat[node][i] == 1 && visited[i] == 0){
                    visited[i] = 1;
                    s.push(i);
                }
            }
        }

        cout << endl;
    }

    void BFS(int node, vector<bool>& visited){
        queue<int> s;
        s.push(node);
        visited[node] = 1;

        while(!s.empty()){
            node = s.front();
            cout << node << " ";
            s.pop();

            for(int i=0; i<nNodes; i++){
                if(Mat[node][i] == 1 && visited[i] == 0){
                    visited[i] = 1;
                    s.push(i);
                }
            }
        }

        cout << endl;
    }

public:
    Graph(int nn, int ne){
        nNodes = nn;
        nEdges = ne;

        for(int i=0; i<nNodes; i++){
            vector<int> temp (nNodes, 0);
            Mat.push_back(temp);
        }
    }

    void input(){
        cout << "Enter Nodes for graph end points: " << endl;
        for(int i=0; i<nEdges; i++){
            int A, B;
            cin >> A >> B;
            Mat[A][B] = 1;
            Mat[B][A] = 1;
        }
    }

    void DFS(int node){
        vector<bool> visited (nNodes, 0);
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                DFS(i, visited);
            }
        }
    }

    void BFS(int node){
        vector<bool> visited (nNodes, 0);
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                BFS(i, visited);
            }
        }
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    Graph G(n, k);
    G.input();
    G.BFS(0);
    G.DFS(0);
    return 0;
}