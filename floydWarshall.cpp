#include <bits/stdc++.h>
using namespace std;

#define INF 10000000

struct Edge {
    int w, a, b;
    bool operator>(const Edge& other) const {
        return w > other.w;
    }
};

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
                if(Mat[node][i] != 0 && visited[i] == 0){
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
                if(Mat[node][i] != 0 && visited[i] == 0){
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
            int A, B, V;
            cin >> A >> B >> V;
            Mat[A][B] = V;
        }
    }

    void setEdge(int a, int b, int w){
        Mat[a][b] = w;
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

    void floydWarshall() {
        vector<vector<int>> dist (nNodes, vector<int> (nNodes, INF));
        vector<vector<int>> next (nNodes, vector<int> (nNodes, -1));

        // Initialization
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<nNodes; j++){
                if(i == j) {
                    dist[i][j] = 0;
                    next[i][j] = j;
                } else if(Mat[i][j] != 0) {
                    dist[i][j] = Mat[i][j];
                    next[i][j] = j;
                }
            }
        }

        // Floyd–Warshall core
        for(int k=0; k<nNodes; k++){
            for(int i=0; i<nNodes; i++){
                for(int j=0; j<nNodes; j++){
                    if(dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        // Print distance matrix
        cout << "\nShortest Distance Matrix:\n";
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<nNodes; j++){
                if (dist[i][j] == INF)
                    cout << "- ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << endl;
        }

        // Print next matrix
        cout << "\nNext Matrix:\n";
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<nNodes; j++){
                cout << next[i][j] << " ";
            }
            cout << endl;
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

    G.floydWarshall();
    return 0;
}