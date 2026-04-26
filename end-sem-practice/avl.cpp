#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int getHeight(Node* n) {
    if (n == NULL) return 0;
    else return n->height;
}

int max2(int a, int b) {
    if (a > b) return a;
    else return b;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    else return getHeight(n->left) - getHeight(n->right);
}

// ROTATIONS
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

// INSERT
Node* insert(Node* node, int key) {

    if (node == NULL)
        return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max2(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1) {
        if (key < node->left->data)
            return rightRotate(node);
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balance < -1) {
        if (key > node->right->data)
            return leftRotate(node);
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// TRAVERSALS
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// LEVEL ORDER
void levelOrder(Node* root) {
    Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* temp = queue[front++];
        cout << temp->data << " ";

        if (temp->left != NULL) queue[rear++] = temp->left;
        if (temp->right != NULL) queue[rear++] = temp->right;
    }
}

int main() {
    ifstream file("avl.txt");

    int n, val;
    file >> n;

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        file >> val;
        root = insert(root, val);
    }

    file.close();

    cout << "Inorder: "; inorder(root);
    cout << "\nPreorder: "; preorder(root);
    cout << "\nPostorder: "; postorder(root);
    cout << "\nLevel Order: "; levelOrder(root);

    return 0;
}