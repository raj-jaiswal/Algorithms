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
            Mat[B][A] = V;
        }
    }

    void setEdge(int a, int b, int w){
        Mat[a][b] = w;
        Mat[b][a] = w;
    }

    void DFS(int node){
        vector<bool> visited (nNodes, 0);
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                DFS(i, visited);
            }
        }
        cout << endl;
    }

    void BFS(int node){
        vector<bool> visited (nNodes, 0);
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                BFS(i, visited);
            }
        }
        cout << endl;
    }

    Graph prins(int v){
        vector<bool> visited (nNodes, false);
        visited[v] = true;
        int visited_count = 1;
        int sum=0;

        Graph MST(nNodes, nNodes-1);
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        for(int i=0; i<nNodes; i++){
            if(Mat[v][i])
                pq.push({Mat[v][i], v, i});
        }

        while(!pq.empty() && visited_count != nNodes){
            Edge e=pq.top();
            pq.pop();
            if(!visited[e.b]){
                MST.setEdge(e.a, e.b, e.w);
                visited[e.b] = true;
                sum += e.w;
                visited_count++;

                for(int i=0; i<nNodes; i++){
                    if(Mat[e.b][i] && !visited[i])
                        pq.push({Mat[e.b][i], e.b, i});
                }
            }
        }

        cout << "Total cost:" << sum << endl;
        return MST;
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    Graph G(n, k);
    G.input();
    G.BFS(0);
    G.DFS(0);

    Graph MST = G.prins(0);
    MST.DFS(0);
    return 0;
}