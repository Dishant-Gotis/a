#include <iostream>
#include <fstream>
using namespace std;

// ================= STRUCT =================
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

// ================= INSERT =================
Node* insert(Node* root, int val) {

    if (root == NULL) {
        return new Node(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    }
    else {
        root->right = insert(root->right, val);
    }

    return root;
}

// =======================================================
// ================= TRAVERSALS ===========================
// =======================================================

// ---------- RECURSIVE ----------
void inorder(Node* root) {

    if (root == NULL) {
        return;
    }

    inorder(root->left);

    cout << root->data << " - ";

    if (root->left != NULL) {
        cout << root->left->data;
    }
    else {
        cout << "NULL";
    }

    cout << " - ";

    if (root->right != NULL) {
        cout << root->right->data;
    }
    else {
        cout << "NULL";
    }

    cout << endl;

    inorder(root->right);
}

void preorder(Node* root) {

    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {

    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// ---------- NON-RECURSIVE ----------
void inorderNR(Node* root) {

    Node* stack[100];
    int top = -1;
    Node* curr = root;

    while (curr != NULL || top != -1) {

        while (curr != NULL) {
            top++;
            stack[top] = curr;
            curr = curr->left;
        }

        curr = stack[top];
        top--;

        cout << curr->data << " ";

        curr = curr->right;
    }
}

void preorderNR(Node* root) {

    if (root == NULL) {
        return;
    }

    Node* stack[100];
    int top = -1;

    top++;
    stack[top] = root;

    while (top != -1) {

        Node* temp = stack[top];
        top--;

        cout << temp->data << " ";

        if (temp->right != NULL) {
            top++;
            stack[top] = temp->right;
        }

        if (temp->left != NULL) {
            top++;
            stack[top] = temp->left;
        }
    }
}

void postorderNR(Node* root) {

    if (root == NULL) {
        return;
    }

    Node* s1[100];
    Node* s2[100];
    int top1 = -1;
    int top2 = -1;

    top1++;
    s1[top1] = root;

    while (top1 != -1) {

        Node* temp = s1[top1];
        top1--;

        top2++;
        s2[top2] = temp;

        if (temp->left != NULL) {
            top1++;
            s1[top1] = temp->left;
        }

        if (temp->right != NULL) {
            top1++;
            s1[top1] = temp->right;
        }
    }

    while (top2 != -1) {
        cout << s2[top2]->data << " ";
        top2--;
    }
}

// ---------- LEVEL ORDER ----------
void levelOrder(Node* root) {

    if (root == NULL) {
        return;
    }

    Node* queue[100];
    int front = 0;
    int rear = 0;

    queue[rear] = root;
    rear++;

    while (front < rear) {

        Node* temp = queue[front];
        front++;

        cout << temp->data << " ";

        if (temp->left != NULL) {
            queue[rear] = temp->left;
            rear++;
        }

        if (temp->right != NULL) {
            queue[rear] = temp->right;
            rear++;
        }
    }
}

// ================= SEARCH =================
int search(Node* root, int key) {

    if (root == NULL) {
        return 0;
    }

    if (root->data == key) {
        return 1;
    }

    if (key < root->data) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// ================= DELETE ROOT =================
Node* findMin(Node* root) {

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

Node* deleteRoot(Node* root) {

    if (root == NULL) {
        return NULL;
    }

    if (root->left == NULL) {
        return root->right;
    }

    if (root->right == NULL) {
        return root->left;
    }

    Node* temp = findMin(root->right);

    root->data = temp->data;

    root->right = deleteRoot(root->right);

    return root;
}

// ================= COUNT =================
int countNodes(Node* root) {

    if (root == NULL) {
        return 0;
    }

    int l = countNodes(root->left);
    int r = countNodes(root->right);

    return 1 + l + r;
}

int countLeaves(Node* root) {

    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return countLeaves(root->left) + countLeaves(root->right);
}

int countInternal(Node* root) {

    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 0;
    }

    return 1 + countInternal(root->left) + countInternal(root->right);
}

// ================= DISPLAY =================
void displayLeaves(Node* root) {

    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " ";
    }

    displayLeaves(root->left);
    displayLeaves(root->right);
}

void displayInternal(Node* root) {

    if (root == NULL) {
        return;
    }

    if (!(root->left == NULL && root->right == NULL)) {
        cout << root->data << " ";
    }

    displayInternal(root->left);
    displayInternal(root->right);
}

// ================= SUM =================
int sumNodes(Node* root) {

    if (root == NULL) {
        return 0;
    }

    return root->data + sumNodes(root->left) + sumNodes(root->right);
}

// ================= SUBTREE SUM =================
Node* findNode(Node* root, int key) {

    if (root == NULL) {
        return NULL;
    }

    if (root->data == key) {
        return root;
    }

    if (key < root->data) {
        return findNode(root->left, key);
    }
    else {
        return findNode(root->right, key);
    }
}

int subtreeSum(Node* root, int key) {

    Node* node = findNode(root, key);

    if (node == NULL) {
        return 0;
    }

    return sumNodes(node);
}

// ================= HEIGHT =================
int height(Node* root) {

    if (root == NULL) {
        return -1;
    }

    int l = height(root->left);
    int r = height(root->right);

    if (l > r) {
        return 1 + l;
    }
    else {
        return 1 + r;
    }
}

// ================= HEIGHT OF NODE =================
int heightOfNode(Node* root, int key) {

    Node* node = findNode(root, key);

    if (node == NULL) {
        return -1;
    }

    return height(node);
}

// ================= BALANCE FACTOR =================
void displayBalance(Node* root) {

    if (root == NULL) {
        return;
    }

    int bf = height(root->left) - height(root->right);

    cout << root->data << " -> " << bf << endl;

    displayBalance(root->left);
    displayBalance(root->right);
}

// ================= MAIN =================
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

    cout << "\nInorder (Parent-Child):\n";
    inorder(root);

    cout << "\nPreorder: ";
    preorder(root);

    cout << "\nPostorder: ";
    postorder(root);

    cout << "\n\nInorder NR: ";
    inorderNR(root);

    cout << "\nPreorder NR: ";
    preorderNR(root);

    cout << "\nPostorder NR: ";
    postorderNR(root);

    cout << "\n\nLevel Order: ";
    levelOrder(root);

    cout << "\nNodes: " << countNodes(root);
    cout << "\nLeaves: " << countLeaves(root);
    cout << "\nInternal: " << countInternal(root);

    cout << "\nLeaf Nodes: ";
    displayLeaves(root);

    cout << "\nInternal Nodes: ";
    displayInternal(root);

    cout << "\nSum: " << sumNodes(root);
    cout << "\nSubtree Sum (30): " << subtreeSum(root, 30);

    cout << "\nHeight: " << height(root);
    cout << "\nHeight of Node 30: " << heightOfNode(root, 30);

    cout << "\n\nBalance Factors:\n";
    displayBalance(root);

    root = deleteRoot(root);

    cout << "\n\nAfter Deleting Root: ";
    preorder(root);

    return 0;
}