#include <iostream>
using namespace std;

class LinkedList{
private:
    struct Node{
        int val;
        Node* next;
    };

    Node* head;

public:
    LinkedList(){
        head = nullptr;
    }

    ~LinkedList(){
        Node* curr = head;
        while (curr != nullptr){
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
    }

    void insert(int val){
        if (head == nullptr){
            head = new Node;
            head->val = val;
            head->next = nullptr;
            return;
        }

        Node* newNode = new Node;
        newNode->val = val;
        newNode->next = nullptr;

        Node* curr = head;
        while(curr -> next != nullptr){
            curr = curr -> next;
        }
        curr -> next = newNode;
    }

    void print(){
        Node* curr = head;
        while (curr != nullptr){
            cout << curr->val << " ";
            curr = curr -> next;
        }
        cout << endl;
    }

    void remove(int val){
        Node* curr = head;
        if(head -> val == val){
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = head;
        curr = curr -> next;

        while (curr != nullptr){
            if (curr -> val == val){
                Node* temp = curr;
                prev -> next = curr -> next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }
};

int main(){
    LinkedList a;
    for (int i=0; i<50; i++){
        a.insert(i);
    }
    a.print();

    a.remove(5);

    a.print();
    return 0;
}