#include  <bits/stdc++.h>
using namespace std;

class Node{
public:
    int m;
    vector<int> keys;
    vector<Node*> children;
    int n;
    bool isLeaf;

    Node(int order, bool isL){
        m = order;
        n = 0;
        keys.resize(m-1, INT_MIN);
        children.resize(m, nullptr);
        isLeaf = isL;
    }
};

class BTree{
private:
    int m;
    Node* root;

    void split(Node* parent, int idx) {
        Node* child = parent->children[idx];
        Node* newNode = new Node(m, child->isLeaf);

        int mid = (m - 1) / 2;
        int midValue = child->keys[mid];

        newNode->n = (m - 1) - (mid + 1);
        for (int i = 0; i < newNode->n; i++) {
            newNode->keys[i] = child->keys[mid + 1 + i];
        }

        if (!child->isLeaf) {
            for (int i = 0; i <= newNode->n; i++) {
                newNode->children[i] = child->children[mid + 1 + i];
            }
        }

        child->n = mid;

        for (int i = parent->n; i > idx; i--) {
            parent->children[i + 1] = parent->children[i];
            parent->keys[i] = parent->keys[i - 1];
        }

        parent->children[idx + 1] = newNode;
        parent->keys[idx] = midValue;
        parent->n++;
    }

    void insertNonFull(Node* root, int val) {
        int i = root->n - 1;

        if (root->isLeaf) {
            while (i >= 0 && root->keys[i] > val) {
                root->keys[i + 1] = root->keys[i];
                i--;
            }
            root->keys[i + 1] = val;
            root->n++;
        } else {
            while (i >= 0 && root->keys[i] > val) i--;

            i++;  
            if (root->children[i]->n == m - 1) {
                split(root, i);
                if (val > root->keys[i]) i++;
            }
            insertNonFull(root->children[i], val);
        }
    }

    Node* insert(Node* root, int val) {
        if (!root) { // first insertion: create a leaf node with one key
            Node* newRoot = new Node(m, true);
            newRoot->keys[0] = val;
            newRoot->n = 1;
            return newRoot;
        }
        if (root->n == m - 1) {
            Node* newRoot = new Node(m, false);
            newRoot->children[0] = root;
            split(newRoot, 0);
            insertNonFull(newRoot, val);
            return newRoot;
        } else {
            insertNonFull(root, val);
            return root;
        }
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
    vector<int> vals {46,5,24,27,57,53,26,56,79,32,35,85,65,45,47,66,78,55,34,67,88,23};
    //vector<int> vals {46,5,24,27};

    for(int val: vals){
        tree.insert(val);
        tree.print();
    }
    return 0;
}