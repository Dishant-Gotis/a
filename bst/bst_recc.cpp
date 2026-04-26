#include <iostream>
using namespace std;

class BST {
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int val) {
            data = val;
            left = right = NULL;
        }
    };

    Node* root;

    // INSERT
    Node* insert(Node* node, int val) {
        if (node == NULL) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);

        return node;
    }

    // FIND MIN (used in delete)
    Node* findMin(Node* node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    // 🔥 GENERAL DELETE FUNCTION
    Node* deleteNode(Node* node, int key) {
        if (node == NULL) return NULL;

        // Step 1: Find the node
        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else {
            // Node found

            // Case 1: No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }

            // Case 2: One child
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* temp = findMin(node->right); // inorder successor
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    // PREORDER
    void preorder(Node* node) {
        if (node == NULL) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // INORDER
    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // POSTORDER
    void postorder(Node* node) {
        if (node == NULL) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:
    BST() {
        root = NULL;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void showPreorder() {
        preorder(root);
        cout << endl;
    }

    void showInorder() {
        inorder(root);
        cout << endl;
    }

    void showPostorder() {
        postorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    cout << "Inorder before deletion: ";
    tree.showInorder();

    tree.remove(10);

    cout << "Inorder after deleting 10: ";
    tree.showInorder();

    return 0;
}