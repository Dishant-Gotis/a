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
            tree[i] = -1; // empty
    }

    void insert(int val) {
        int i = 0;

        while (i < capacity) {
            if (tree[i] == -1) {
                tree[i] = val;
                return;
            }

            if (val < tree[i])
                i = 2 * i + 1;
            else
                i = 2 * i + 2;
        }

        cout << "Tree full\n";
    }

    // Non-recursive Preorder using stack
    void preorder() {
        if (tree[0] == -1) return;

        int* stack = new int[capacity];
        int top = -1;

        stack[++top] = 0;

        while (top != -1) {
            int curr = stack[top--];
            cout << tree[curr] << " ";

            int right = 2 * curr + 2;
            int left  = 2 * curr + 1;

            // Push right first so left is processed first
            if (right < capacity && tree[right] != -1)
                stack[++top] = right;

            if (left < capacity && tree[left] != -1)
                stack[++top] = left;
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

    cout << "Preorder (Non-Recursive): ";
    bst.preorder();

    return 0;
}