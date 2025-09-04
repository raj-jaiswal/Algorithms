#include  <bits/stdc++.h>
using namespace std;

class Node{
public:
    int m;
    vector<int> keys;
    vector<Node*> children;
    int n;

    Node(int order, int val){
        m = order;
        n = 1;
        keys.resize(m-1, INT_MIN);
        children.resize(m, nullptr);
        keys[0] = val;
    }
};

class Tree{
private:
    int m;
    Node* root;

    void findNext(Node* left, Node* right, Node* node, int idx){
        if(left){
            node->keys[idx] = left->keys[left->n-1];
            node->children[idx] = remove(node->children[idx], node->keys[idx]);
            return;
        }
        if(right){
            node->keys[idx] = right->keys[0];
            node->children[idx+1] = remove(node->children[idx+1], node->keys[idx]);
            return;
        }

        for(int i=idx+1; i<node->n; i++){
            node->keys[i-1] = node->keys[i];
            // No children exist
        }
        (node->n)--;
    }

    Node* insert(Node* node, int val){
        if(!node) return new Node(m, val);
        if(node->n < m-1){
            int i = node->n-1;
            while (i >= 0 && node->keys[i] > val) {
                node->keys[i+1] = node->keys[i];
                node->children[i+2] = node->children[i+1];
                i--;
            }
            node->keys[i+1] = val;
            node->children[i+2] = nullptr;
            node->n++;
        }
        else{
            for(int i=0; i<m-1; i++){
                if(node->keys[i] > val){
                    node->children[i] = insert(node->children[i], val);
                    return node;
                }
            }
            node->children[m-1] = insert(node->children[m-1], val);
        }

        return node;
    }

    Node* remove(Node* node, int val){
        if(!node) return node;
        for(int i=0; i<node->n; i++){
            if(node->keys[i] == val){
                findNext(node->children[i], node->children[i+1], node, i);
                if(node->n == 0) return nullptr;
                return node;
            }
        }
        
        if(val < node->keys[0]) {
            node->children[0] = remove(node->children[0], val);
            return node;
        }

        for(int i=1; i<node->n; i++){
            if(val<node->keys[i]){
                node->children[i] = remove(node->children[i], val);
                return node;
            }
        }

        node->children[node->n] = remove(node->children[node->n], val);
        return node;
    }

    void print(Node* node){
        if(!node) return;
        for(int i=0; i<node->n; i++){
            print(node->children[i]);
            cout << node->keys[i] << " ";
        }
        print(node->children[node->n]);
    }

public:
    Tree(int order){
        m = order;
        root = nullptr;
    }

    void insert(int val){
        root = insert(root, val);
    }

    void print(){
        print(root);
        cout << endl;
    }

    void remove(int val){
        root = remove(root, val);
    }
};

int main(){
    int m=5;
    Tree tree(m);
    vector<int> vals {46,5,24,27,57,53,26,56,79,32,35,85,65,45,47,66,78,55,34,67,88,23};

    for(int val: vals){
        tree.insert(val);
        tree.print();
    }
    for(int i=vals.size()-1; i>=0; i--){
        tree.remove(vals[i]);
        tree.print();
    }
    return 0;
}