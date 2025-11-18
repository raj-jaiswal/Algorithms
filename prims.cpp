#include <bits/stdc++.h>
using namespace std;

class Edge{
public:
    int a;
    int b;
    int weight;

    Edge(int a_, int b_, int w){
        a = a_;
        b = b_;
        weight = w;
    }

    bool operator<(const Edge& a_) const{
        return weight < a_.weight;
    } 

    bool operator>(const Edge& a_) const{
        return weight > a_.weight;
    } 
};

class Graph{
private:
    vector<vector<int>> Mat;
    int nNodes;
    int nEdges;

    void dfs(int node, vector<bool>& visited){
        stack<int> next;
        next.push(node);
        while (!next.empty()){
            int elm = next.top();
            cout << elm << " ";
            visited[elm] = true;
            next.pop();

            for(int i=0; i<nNodes; i++){
                if(Mat[elm][i] != INT_MAX && !visited[i]){
                    next.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    void bfs(int node, vector<bool>& visited){
        queue<int> next;
        next.push(node);
        while (!next.empty()){
            int elm = next.front();
            cout << elm << " ";
            visited[elm] = true;
            next.pop();

            for(int i=0; i<nNodes; i++){
                if(Mat[elm][i] != INT_MAX && !visited[i]){
                    next.push(i);
                    visited[i] = true;
                }
            }
        }
    }

public:
    Graph(int nn, int ne){
        nNodes = nn;
        nEdges = ne;

        for(int i=0; i<nNodes; i++){
            vector<int> arr;
            Mat.push_back(arr);
            for(int j=0; j<nNodes; j++){
                Mat[i].push_back(INT_MAX);
            }
        }

        for(int i=0; i<nNodes; i++){
            Mat[i][i] = 0;
        }
    }

    void input(){
        cout << "Enter Nodes for graph end points: " << endl;
        for(int i=0; i<nEdges; i++){
            int A, B, W;
            cin >> A >> B >> W;
            Mat[A][B] = W;
            Mat[B][A] = W;
        }
    }

    void dfs(){
        vector<bool> visited (nNodes, false);
        cout << "dfs: ";
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                dfs(i, visited);
            }
        }
        cout << endl;
    }

    void bfs(){
        vector<bool> visited (nNodes, false);
        cout << "bfs: ";
        for(int i=0; i<nNodes; i++){
            if(!visited[i]){
                bfs(i, visited);
            }
        }
        cout << endl;
    }

    void addEdge(int start, int end, int weight){
        Mat[start][end] = weight;
        Mat[end][start] = weight;
    }

    int totalCost(){
        int sum = 0;
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<i; j++){
                sum += (Mat[i][j]==INT_MAX) ? 0 : Mat[i][j];
            }
        }

        return sum;
    }

    void printMat(){
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<nNodes; j++){
                if (Mat[i][j] == INT_MAX)
                    cout << "-" << '\t';
                else
                    cout << Mat[i][j] << "\t";
            }
            cout << endl;
        }
    }

// -- visited before loop
// -- never pushed to pq
// -- priority queue not set to greater

    Graph prims(int start){
        vector<bool> visited (nNodes, false);
        Graph MST (nNodes, nNodes-1);

        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        Edge next (start, start, 0);
        pq.push(next);

        while (!pq.empty()){
            next = pq.top();
            pq.pop();
            if(visited[next.b]) continue;

            visited[next.b] = true;
            MST.addEdge(next.a, next.b, next.weight);
            start = next.b;

            for(int i=0; i<nNodes; i++){
                if(Mat[start][i]!=INT_MAX && !visited[i]){
                    Edge next (start, i, Mat[start][i]);
                    pq.push(next);
                }
            }
        }

        return MST;
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    Graph G(n, k);
    G.input();
    G.dfs();
    G.bfs();

    Graph MST = G.prims(0);
    MST.bfs();
    MST.printMat();
    cout << MST.totalCost() << endl;

    return 0;
}