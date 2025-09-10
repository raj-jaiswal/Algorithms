#include  <bits/stdc++.h>
using namespace std;

class Node{
public:
    int m;
    vector<int> keys;
    vector<Node*> children;
    int n;
    bool isLeaf;

    Node(int order, int val){
        m = order;
        n = 1;
        keys.resize(m-1, INT_MIN);
        children.resize(m, nullptr);
        keys[0] = val;
        isLeaf = true;
    }
};

class BTree{
private:
    int m;
    Node* root;

    Node* insertElem(Node* node, int val){
        if(node->n < m-1){
            int i = node->n-1;
            while(i>=0){
                if (val < node->keys[i]){
                    node->keys[i+1] = node->keys[i];
                    i--;
                }
                else break;
            }
            node->keys[i+1] = val;
            (node->n)++;
            return node;
        }
        
        
        return node;
    }

    Node* insert(Node* node, int val){
        if(!node) return new Node(m, val);

        //if it is not a leaf, find next child to insert
        if(!node->isLeaf){
            for(int i=0; i<node->n; i++){
                if(val<node->keys[i]){
                    node->children[i] = insert(node->children[i], val);
                    return node;
                }
                node->children[node->n] = insert(node->children[i], val);
                return node;
            }
        }

        // if it is leaf, insert
        else{
            node = insertElem(node, val);
        }
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
    BTree(int order){
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
};

int main(){
    int m=5;
    BTree tree(m);
    //vector<int> vals {46,5,24,27,57,53,26,56,79,32,35,85,65,45,47,66,78,55,34,67,88,23};
    vector<int> vals {46,5,24,27};

    for(int val: vals){
        tree.insert(val);
        tree.print();
    }
    return 0;
}