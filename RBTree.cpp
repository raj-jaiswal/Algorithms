#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
    char color; // 'r' or 'b'

    Node(int v, Node* p){
        left = nullptr;
        right = nullptr;
        val = v;
        color = 'r';
        parent = p;
    }
};

class RBTree{
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

    // Corrected rotations: update parent pointers and root
    Node* rightRotate(Node* pivot){
        if (!pivot || !pivot->left) return pivot;
        Node* newPivot = pivot->left;
        pivot->left = newPivot->right;
        if (newPivot->right) newPivot->right->parent = pivot;

        newPivot->right = pivot;
        newPivot->parent = pivot->parent;

        if (!pivot->parent) {
            root = newPivot; // pivot was root
        } else if (pivot->parent->left == pivot) {
            pivot->parent->left = newPivot;
        } else {
            pivot->parent->right = newPivot;
        }

        pivot->parent = newPivot;
        return newPivot;
    }

    Node* leftRotate(Node* pivot){
        if (!pivot || !pivot->right) return pivot;
        Node* newPivot = pivot->right;
        pivot->right = newPivot->left;
        if (newPivot->left) newPivot->left->parent = pivot;

        newPivot->left = pivot;
        newPivot->parent = pivot->parent;

        if (!pivot->parent) {
            root = newPivot; // pivot was root
        } else if (pivot->parent->left == pivot) {
            pivot->parent->left = newPivot;
        } else {
            pivot->parent->right = newPivot;
        }

        pivot->parent = newPivot;
        return newPivot;
    }

    // CLRS-style insert-fix with null-safety and proper rotations
    void RBInsertFix(Node* Z) {
        while (Z->parent && Z->parent->color == 'r') {
            Node* gp = Z->parent->parent;
            if (!gp) break; // safety
            if (Z->parent == gp->left) {
                Node* Y = gp->right; // uncle
                if (Y && Y->color == 'r') {
                    // case 1
                    Z->parent->color = 'b';
                    Y->color = 'b';
                    gp->color = 'r';
                    Z = gp;
                } else {
                    // case 2
                    if (Z == Z->parent->right) {
                        Z = Z->parent;
                        leftRotate(Z); // rotate about old parent
                    }
                    // case 3
                    Z->parent->color = 'b';
                    gp->color = 'r';
                    rightRotate(gp); // rotate about grandparent
                }
            } else {
                // mirror case: parent is right child of grandparent
                Node* Y = gp->left; // uncle
                if (Y && Y->color == 'r') {
                    // case 1 (mirror)
                    Z->parent->color = 'b';
                    Y->color = 'b';
                    gp->color = 'r';
                    Z = gp;
                } else {
                    // case 2 (mirror)
                    if (Z == Z->parent->left) {
                        Z = Z->parent;
                        rightRotate(Z);
                    }
                    // case 3 (mirror)
                    Z->parent->color = 'b';
                    gp->color = 'r';
                    leftRotate(gp);
                }
            }
        }
        if (root) root->color = 'b';
    }

    // Core Functions
    // Modified insert: returns subtree root as before, but also provides inserted node via reference
    Node* insert(Node* node, int val, Node* parent, Node*& inserted){
        if (!node){
            inserted = new Node(val, parent);
            return inserted;
        }
        if(val < node -> val){
            node -> left = insert(node->left, val, node, inserted);
        }     
        else{
            node -> right = insert(node->right, val, node, inserted);
        }
        return node;
    }

    Node* remove(Node* node, int val, Node* parent){
        if(!node) return nullptr;

        if(node->val == val){
            if(!node->right && !node->left){
                delete node;
                return nullptr;
            }
            if(!node->right && node->left){
                Node* child = node->left;
                child->parent = parent;     // set before delete (fix use-after-free)
                delete node;
                return child;
            }
            if(node->right && !node->left){
                Node* child = node->right;
                child->parent = parent;     // set before delete
                delete node;
                return child;
            }
            
            int successor = findSucc(node->right);
            node -> val = successor;
            node -> right = remove(node->right, successor, node);
        }
        else if(val < node -> val)
            node -> left = remove(node->left, val, node);
        else
            node -> right = remove(node->right, val, node);
        return node;
    }

    void print(Node* node){
        if(!node) return;
        print(node->left);
        cout << node->val << " ";
        print(node->right);
    }

public:
    RBTree(){
        root = nullptr;
        n = 0;
    }

    void insert(int val){
        Node* inserted = nullptr;
        root = insert(root, val, nullptr, inserted);
        if (inserted) RBInsertFix(inserted);
    }

    void remove(int val){
        root = remove(root, val, nullptr);
        if (root) root->parent = nullptr;
    }

    void print(){
        print(root);
        cout << endl;
    }
};

int main(){
    RBTree tree;
    vector<int> vals {46, 23, 87, 5, 53, 64, 7, 16, 74, 15,73};
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