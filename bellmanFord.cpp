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
    vector<Edge> edges;
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
            
            Edge E (A,B,W);
            edges.push_back(E);
            Mat[A][B] = W;
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

    void bellman(int start, vector<int>& costs, vector<int>& parents){
        costs[start] = 0;
        for(int i=0; i<nNodes; i++){
            for(int j=0; j<edges.size(); j++){
                if(costs[edges[j].a] + edges[j].weight < costs[edges[j].b]){
                    costs[edges[j].b] = costs[edges[j].a] + edges[j].weight;
                    parents[edges[j].b] = edges[j].a;
                }
            }
        }
        for(int j=0; j<edges.size(); j++){
            if(costs[edges[j].a] + edges[j].weight < costs[edges[j].b]){
                cerr << "Negative Cycle Present." << endl;
                exit(1);
            }
        }
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    Graph G(n, k);
    G.input();
    G.dfs();
    G.bfs();

    vector<int> costs (n, INT_MAX);
    vector<int> parents (n, -1);

    G.bellman(0, costs, parents);

    for(int i=0; i<n; i++){
        cout << costs[i] << " ";
    }
    cout << endl;

    for(int i=0; i<n; i++){
        cout << parents[i] << " ";
    }
    cout << endl;
    
    return 0;
}