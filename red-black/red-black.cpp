#include <iostream>
#include <fstream>
using namespace std;

enum Color { RED, BLACK };

class RedBlackTree {
    struct Node {
        int data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val) {
            data = val;
            color = RED;
            left = right = parent = NULL;
        }
    };

    Node* root;

    // Left Rotate
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != NULL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NULL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Right Rotate
    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != NULL)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == NULL)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    // Fix violations after insertion
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {

            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        node = parent;
                        leftRotate(node);
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        node = parent;
                        rightRotate(node);
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }

        root->color = BLACK;
    }

    // Inorder display
    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorder(node->right);
    }

public:
    RedBlackTree() {
        root = NULL;
    }

    void insert(int value) {
        Node* node = new Node(value);

        Node* parent = NULL;
        Node* current = root;

        // BST insert
        while (current != NULL) {
            parent = current;

            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }

        node->parent = parent;

        if (parent == NULL)
            root = node;
        else if (value < parent->data)
            parent->left = node;
        else
            parent->right = node;

        fixInsert(node);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;

    ifstream file("tree.txt");

    int value;
    while (file >> value) {
        tree.insert(value);
    }

    file.close();

    cout << "Inorder (value(color)):\n";
    tree.display();

    return 0;
}