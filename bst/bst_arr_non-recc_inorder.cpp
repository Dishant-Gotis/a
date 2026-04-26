#include <iostream>
using namespace std;

class BST_Array {
    int* tree;
    int capacity;

public:
    BST_Array(int cap) {
        capacity = cap;
        tree = new int[capacity];
        for (int i = 0; i < capacity; i++)
            tree[i] = -1; // -1 means empty
    }

    // Insert element
    void insert(int val) {
        int i = 0;

        while (i < capacity) {
            if (tree[i] == -1) {
                tree[i] = val;
                return;
            }

            if (val < tree[i])
                i = 2 * i + 1;      // left child
            else
                i = 2 * i + 2;      // right child
        }

        cout << "Tree full or insufficient capacity\n";
    }

    // Non-recursive inorder traversal using stack
    void inorder() {
        int* stack = new int[capacity];
        int top = -1;

        int curr = 0;

        while (true) {
            // Go left
            while (curr < capacity && tree[curr] != -1) {
                stack[++top] = curr;
                curr = 2 * curr + 1;
            }

            if (top == -1) break;

            curr = stack[top--];
            cout << tree[curr] << " ";

            curr = 2 * curr + 2; // go right
        }

        cout << endl;
        delete[] stack;
    }

    ~BST_Array() {
        delete[] tree;
    }
};

int main() {
    BST_Array bst(20);

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(2);
    bst.insert(7);
    bst.insert(12);
    bst.insert(20);

    cout << "Inorder (Non-Recursive): ";
    bst.inorder();

    return 0;
}