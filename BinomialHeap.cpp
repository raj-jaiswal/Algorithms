#include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int val;
    vector<Node*> children;
    int order;

    Node(int v){
        val = v;
        order = 0;
    }
};

class BHeap{
private:
    void unionHeap(BHeap* nextHeap){
        vector<Node*> newElems{};

        int a=0;
        int b=0;
        for(int i=0; i<nextHeap->elems.size() + elems.size(); i++){
            if(a>=elems.size()){
                newElems.push_back(nextHeap->elems[b++]);
                continue;
            }
            if(b>=nextHeap->elems.size()){
                newElems.push_back(elems[a++]);
                continue;
            }

            if(elems[a]->order < nextHeap->elems[b]->order){
                newElems.push_back(elems[a++]);
                continue;
            }
            newElems.push_back(nextHeap->elems[b++]);
        }

        bool done = false;
        
        while(!done){
            done = true;
            for(int i=0; i<newElems.size(); i++){
                if(i+1 < newElems.size()){
                    if(newElems[i]->order == newElems[i+1]->order && ((i+2 == newElems.size()) || newElems[i]->order != newElems[i+2]->order)){
                        if(newElems[i]->val < newElems[i+1]->val){
                            newElems[i]->children.push_back(newElems[i+1]);
                            (newElems[i]->order)++;
                            newElems.erase(newElems.begin() + i + 1);
                        }
                        else{
                            newElems[i+1]->children.push_back(newElems[i]);
                            (newElems[i+1]->order)++;
                            newElems.erase(newElems.begin() + i);
                        }
                        i=max(0, i-1);
                        done = false;
                    }
                }
            }
        }

        elems = newElems;
    }

    void printTree(Node* node, int depth) {
        if (!node) return;
        // indent according to depth
        for (int i = 0; i < depth; i++) cout << "    ";
        cout << node->val << " (order " << node->order << ")\n";

        for (auto child : node->children) {
            printTree(child, depth + 1);
        }
    }

public:
    vector<Node*> elems;

    void insert(int val){
        BHeap* newHeap = new BHeap();
        newHeap->elems.push_back(new Node(val));
        unionHeap(newHeap);
    }

    void print() {
        cout << "Binomial Heap structure:\n";
        for (auto root : elems) {
            cout << "Tree of order " << root->order << ":\n";
            printTree(root, 1);
        }
    }

    int extractMin(){
        int minV = elems[0]->val;
        int idx = 0;

        for(int i=1; i<elems.size(); i++){
            if(minV > elems[i]->val){
                idx = i;
                minV = elems[i]->val;
            }
        }

        Node* minNode = elems[idx];
        elems.erase(elems.begin() + idx);
        BHeap* newHeap = new BHeap;
        newHeap->elems = minNode->children; 
        unionHeap(newHeap);
        delete minNode;
        return minV;
    }
};

int main(){
    vector<int> vals {45,23,13,75,24,85,2,25};
    BHeap Heap;

    for(int v:vals){
        Heap.insert(v);
    }
    Heap.print();

    for(int v:vals){
        cout << Heap.extractMin() << " ";
    }
    cout << endl;
    return 0;
}