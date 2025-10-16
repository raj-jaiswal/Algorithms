#include <bits/stdc++.h>
using namespace std;

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

    vector<int> dijkstra(int src) {
        vector<int> dist(nNodes, INT_MAX);
        dist[src] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, src});

        while(!pq.empty()){
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if(d > dist[u]) continue;

            for(int v = 0; v < nNodes; v++){
                if(Mat[u][v] && dist[v] > dist[u] + Mat[u][v]){
                    dist[v] = dist[u] + Mat[u][v];
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest distances from " << src << ":\n";
        for(int i=0; i<nNodes; i++)
            cout << i << " -> " << dist[i] << endl;

        return dist;
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    Graph G(n, k);
    G.input();
    G.BFS(0);
    G.DFS(0);

    vector<int> shortest_distances = G.dijkstra(0);
    return 0;
}