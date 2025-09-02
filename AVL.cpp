#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int val;
    int h;
    Node* left;
    Node* right;

    Node(int v){
        left = nullptr;
        right = nullptr;
        val = v;
        h = 1;
    }
};

class AVL{
private:
    Node* root;
    int n;

    // Helpers
    int findSucc(Node* node){
        Node* curr = node;
        while(curr -> left){
            curr = curr->left;
        }
        return curr -> val;
    }

    int height(Node* node){
        if (!node) return 0;
        return node->h;
    }

    Node* rightRotate(Node* pivot){
        Node* newPivot = pivot -> left;
        pivot -> left = newPivot -> right;
        newPivot -> right = pivot;

        pivot->h = 1 + max(height(pivot->left), height(pivot->right));
        newPivot->h = 1 + max(height(newPivot->left), height(newPivot->right));
        return newPivot;
    }

    Node* leftRotate(Node* pivot){
        Node* newPivot = pivot -> right;
        pivot -> right = newPivot -> left;
        newPivot -> left = pivot;

        pivot->h = 1 + max(height(pivot->left), height(pivot->right));
        newPivot->h = 1 + max(height(newPivot->left), height(newPivot->right));
        return newPivot;
    }

    // Core Functions
    Node* insert(Node* node, int val){
        if (!node) return new Node(val);
        if(val < node -> val)
            node -> left = insert(node->left, val);
        else
            node -> right = insert(node->right, val);

        // Balancing
        node->h = 1 + max(height(node -> left), height(node -> right));
        int bf = height(node->left) - height(node->right);

        if(bf > 1){
            if(val < node->left->val)
                node = rightRotate(node);
            else{
                node -> left = leftRotate(node -> left);
                node = rightRotate(node);
            }
        }
        else if (bf < -1){
            if(val > node->right->val)
                node = leftRotate(node);
            else{
                node -> right = rightRotate(node -> right);
                node = leftRotate(node);
            }
        }
        return node;
    }

    Node* remove(Node* node, int val){
        if(!node) return nullptr;

        if(node->val == val){
            if(!node->right && !node->left){
                delete node;
                return nullptr;
            }
            if(!node->right && node->left){
                delete node;
                return node -> left;
            }
            if(node->right && !node->left){
                delete node;
                return node -> right;
            }
            
            int successor = findSucc(node->right);
            node -> val = successor;
            node -> right = remove(node->right, successor);
        }
        else if(val < node -> val)
            node -> left = remove(node->left, val);
        else
            node -> right = remove(node->right, val);

        // Balancing
        node->h = 1 + max(height(node -> left), height(node -> right));
        int bf = height(node->left) - height(node->right);

        if(bf > 1){
            if(val < node->left->val)
                node = rightRotate(node);
            else{
                node -> left = leftRotate(node -> left);
                node = rightRotate(node);
            }
        }
        else if (bf < -1){
            if(val > node->right->val)
                node = leftRotate(node);
            else{
                node -> right = rightRotate(node -> right);
                node = leftRotate(node);
            }
        }
        return node;
    }

    void print(Node* node){
        if(!node) return;
        print(node->left);
        cout << node->val << " ";
        print(node->right);
    }

public:
    AVL(){
        root = nullptr;
        n = 0;
    }

    void insert(int val){
        root = insert(root, val);
    }

    void remove(int val){
        root = remove(root, val);
    }

    void print(){
        print(root);
        cout << endl;
    }
};

int main(){
    AVL tree;
    vector<int> vals {46, 23, 87, 5, 15, 85, 36, 26, 86};
    for(int val:vals){
        tree.insert(val);
    }
    tree.print();

    for(int val:vals){
        tree.remove(val);
        tree.print();
    }
    return 0;
}