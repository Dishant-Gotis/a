#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Build tree using recursion
Node* buildTree() {
    int val;
    cin >> val;

    if (val == -1) return NULL;

    Node* root = new Node(val);

    root->left = buildTree();
    root->right = buildTree();
    

    return root;
}

// Preorder traversal
void preorder(Node* root) {
    if (root == NULL) return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    cout << "Enter tree (-1 for NULL): ";
    Node* root = buildTree();

    cout << "Preorder Traversal: ";
    preorder(root);

    return 0;
}