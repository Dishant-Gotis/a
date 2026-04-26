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

    // Non-recursive Postorder using 2 stacks
    void postorder() {
        int* s1 = new int[capacity];
        int* s2 = new int[capacity];
        int top1 = -1, top2 = -1;

        if (tree[0] == -1) return;

        s1[++top1] = 0;

        while (top1 != -1) {
            int curr = s1[top1--];
            s2[++top2] = curr;

            int left = 2 * curr + 1;
            int right = 2 * curr + 2;

            if (left < capacity && tree[left] != -1)
                s1[++top1] = left;

            if (right < capacity && tree[right] != -1)
                s1[++top1] = right;
        }

        while (top2 != -1) {
            cout << tree[s2[top2--]] << " ";
        }

        cout << endl;

        delete[] s1;
        delete[] s2;
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

    cout << "Postorder (Non-Recursive): ";
    bst.postorder();

    return 0;
}