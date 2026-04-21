#include <iostream>
using namespace std;

class AVL {
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int val) {
            data = val;
            left = right = NULL;
            height = 1;
        }
    };

    Node* root;

    // ===== Utility =====
    int getHeight(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    int max2(int a, int b) { return (a > b) ? a : b; }

    // ===== Rotations =====
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max2(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max2(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max2(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max2(getHeight(y->left), getHeight(y->right));

        return y;
    }

    // ===== Insert =====
    Node* insert(Node* node, int key) {
        // Normal BST insert
        if (node == NULL) return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node; // no duplicates

        // Update height
        node->height = 1 + max2(getHeight(node->left), getHeight(node->right));

        // Check balance
        int balance = getBalance(node);

        // LL
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // RR
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // LR
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ===== Traversals =====
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:
    AVL() { root = NULL; }

    void insert(int key) {
        root = insert(root, key);
    }

    void showInorder() {
        inorder(root);
        cout << endl;
    }

    void showPreorder() {
        preorder(root);
        cout << endl;
    }

    void showPostorder() {
        postorder(root);
        cout << endl;
    }
};

int main() {
    AVL tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(25);
    tree.insert(5);
    tree.insert(15);

    cout << "Inorder: ";
    tree.showInorder();

    cout << "Preorder: ";
    tree.showPreorder();

    cout << "Postorder: ";
    tree.showPostorder();

    return 0;
}