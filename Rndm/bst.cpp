#include<iostream>
using namespace std;

struct Node{
    int val;
    Node *left, *right;
    
    Node(int val){
    left = right = NULL;
    }
};

class BST{
    private:
    Node *
};



#include <iostream>

using namespace std;

struct node {
    int val;
    node *left, *right;
    node(int value) {
        left = right = NULL;
        val = value;
    }
};

class BST {
    private:
        node *root;
        void displayRec(node *n) {
            if (!n) return;

            displayRec(n->left);
            cout << n->val << " ";
            displayRec(n->right);
            return;
        }

        void swap(node *n1, node *n2) {
            int temp = n1->val;
            n2->val = n1->val;
            n1->val = temp;
        }

        node* getInSuc(node *n) {
            node *ptr = n;
            
        }
    
    public:
        BST() {
            root = NULL;
        }

        void insert(int key);
        void display();
        node* search(int key);
        void remove(int key);
};

int main() {
    BST b;
    b.insert(20);
    b.insert(10);
    b.insert(50);
    b.insert(87);
    b.insert(1);
    b.insert(2);
    b.display();
    cout << endl << b.search(21) << endl;
    return 0;
}

void BST :: insert(int key) {

    // Making a new node
    node *nn = new node(key);
    if (!nn) return;

    // Empty tree edge case
    if (!root) {
        root = nn;
        return;    
    }

    node *ptr = root;
    while (true) {
        if (ptr->val == key) {
            delete nn;
            return;
        }
        else if (ptr->val > key) {
            if(ptr->left) ptr = ptr->left;
            else {
                ptr->left = nn;
                break;
            }
        }
        else  {
            if(ptr->right) ptr = ptr->right;
            else {
                ptr->right = nn;
                break;
            }
        }
    }

    return;
}

void BST :: display() {
    displayRec(root);
}

node* BST :: search(int key) {
    
    node *ptr = root;
    while(ptr) {
        if (ptr->val == key) return ptr;
        else if (ptr->val > key) ptr = ptr->left;
        else ptr = ptr->right;
    }

    return NULL;
}

void BST :: remove(int key) {
    node *n = search(key);

    if (!n) return;
}
