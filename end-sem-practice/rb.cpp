#include <iostream>
using namespace std;

struct Node {
    int data;
    int color; // 1 = Red, 0 = Black
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) {
        data = val;
        color = 1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

Node* root = NULL;

// INSERT
Node* insert(Node* root, int val) {

    Node* node = new Node(val);
    Node* y = NULL;
    Node* x = root;

    while (x != NULL) {
        y = x;

        if (val < x->data)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;

    if (y == NULL) {
        root = node;
    }
    else {
        if (val < y->data)
            y->left = node;
        else
            y->right = node;
    }

    node->color = 0; // root black

    return root;
}

// TRAVERSALS
void inorder(Node* root) {
    if (root == NULL) return;

    inorder(root->left);

    if (root->color == 1)
        cout << root->data << "(R) ";
    else
        cout << root->data << "(B) ";

    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;

    if (root->color == 1)
        cout << root->data << "(R) ";
    else
        cout << root->data << "(B) ";

    preorder(root->left);
    preorder(root->right);
}

int main() {

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    cout << "Inorder: ";
    inorder(root);

    cout << "\nPreorder: ";
    preorder(root);

    return 0;
}