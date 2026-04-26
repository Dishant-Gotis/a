#include <iostream>
#include <fstream>
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

// INSERT
Node* insert(Node* root, int val) {
    if (root == NULL)
        return new Node(val);

    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// INORDER (Recursive)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// PREORDER
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// POSTORDER
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// NON-RECURSIVE INORDER
void inorderNR(Node* root) {
    Node* stack[100];
    int top = -1;
    Node* curr = root;

    while (curr != NULL || top != -1) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        cout << curr->data << " ";
        curr = curr->right;
    }
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

// SEARCH
int search(Node* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// COUNT NODES
int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// COUNT LEAVES
int countLeaves(Node* root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaves(root->left) + countLeaves(root->right);
}

// COUNT INTERNAL
int countInternal(Node* root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL)
        return 0;

    return 1 + countInternal(root->left) + countInternal(root->right);
}

// DISPLAY LEAF
void displayLeaves(Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL)
        cout << root->data << " ";

    displayLeaves(root->left);
    displayLeaves(root->right);
}

// DISPLAY INTERNAL
void displayInternal(Node* root) {
    if (root == NULL) return;

    if (!(root->left == NULL && root->right == NULL))
        cout << root->data << " ";

    displayInternal(root->left);
    displayInternal(root->right);
}

// HEIGHT
int height(Node* root) {
    if (root == NULL) return -1;

    int l = height(root->left);
    int r = height(root->right);

    if (l > r)
        return 1 + l;
    else
        return 1 + r;
}

// BALANCE FACTOR
int balanceFactor(Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

// SUM
int sumNodes(Node* root) {
    if (root == NULL) return 0;
    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

// FIND NODE
Node* findNode(Node* root, int key) {
    if (root == NULL) return NULL;
    if (root->data == key) return root;

    if (key < root->data)
        return findNode(root->left, key);
    else
        return findNode(root->right, key);
}

// SUBTREE SUM
int subtreeSum(Node* root, int key) {
    Node* node = findNode(root, key);
    return sumNodes(node);
}

// DELETE ROOT
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteRoot(Node* root) {
    if (root == NULL) return NULL;

    if (root->left == NULL) return root->right;
    if (root->right == NULL) return root->left;

    Node* temp = findMin(root->right);
    root->data = temp->data;
    root->right = deleteRoot(root->right);

    return root;
}

// DISPLAY PARENT-CHILD
void displayStructure(Node* root) {
    if (root == NULL) return;

    cout << root->data << " - ";

    if (root->left) cout << root->left->data;
    else cout << "NULL";

    cout << " - ";

    if (root->right) cout << root->right->data;
    else cout << "NULL";

    cout << endl;

    displayStructure(root->left);
    displayStructure(root->right);
}

// MAIN
int main() {
    ifstream file("tree.txt");

    int n, val;
    file >> n;

    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        file >> val;
        root = insert(root, val);
    }

    file.close();

    cout << "Inorder: "; inorder(root);
    cout << "\nNon-Recursive Inorder: "; inorderNR(root);
    cout << "\nPreorder: "; preorder(root);
    cout << "\nPostorder: "; postorder(root);
    cout << "\nLevel Order: "; levelOrder(root);

    cout << "\nNodes: " << countNodes(root);
    cout << "\nLeaves: " << countLeaves(root);
    cout << "\nInternal: " << countInternal(root);

    cout << "\nLeaf Nodes: "; displayLeaves(root);
    cout << "\nInternal Nodes: "; displayInternal(root);

    cout << "\nHeight: " << height(root);
    cout << "\nSum: " << sumNodes(root);

    cout << "\nBalance Factor of root: " << balanceFactor(root);

    cout << "\nTree Structure:\n";
    displayStructure(root);

    return 0;
}