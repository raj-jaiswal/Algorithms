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
            if (W<0){
                cerr << "Negative Edges are not Allowed." << endl;
                exit(1);
            }
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

    void dijkstras(int start, vector<int>& costs, vector<int>& parents){
        vector<bool> visited (nNodes, false);
        costs[start]=0;

        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        Edge next (start, start, 0);
        pq.push(next);
        
        while(!pq.empty()){
            Edge step = pq.top();
            pq.pop();
            if(visited[step.b]) continue;
            parents[step.b] = step.a;
            start = step.b;

            visited[start] = true;
            for(int i=0; i<nNodes; i++){
                if(Mat[start][i] != INT_MAX && !visited[i]){
                    if(step.weight + Mat[start][i] < costs[i]){
                        costs[i] = step.weight + Mat[start][i];
                        Edge next (start, i, costs[i]);
                        pq.push(next);
                    }
                }
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

    G.dijkstras(0, costs, parents);
    
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