#include <iostream>
#include <fstream>
using namespace std;

int tree[100];

// ================= INSERT =================
void insert(int val, int index) {

    if (tree[index] == 0) {
        tree[index] = val;
        return;
    }

    if (val < tree[index]) {
        insert(val, 2 * index);
    }
    else {
        insert(val, 2 * index + 1);
    }
}

// ================= NON-RECURSIVE PREORDER =================
void preorderNR() {

    int stack[100];
    int top = -1;

    // push root index
    top++;
    stack[top] = 1;

    while (top != -1) {

        int index = stack[top];
        top--;

        if (tree[index] == 0)
            continue;

        cout << tree[index] << " ";

        // push right first
        if (2 * index + 1 < 100) {
            top++;
            stack[top] = 2 * index + 1;
        }

        // push left
        if (2 * index < 100) {
            top++;
            stack[top] = 2 * index;
        }
    }
}

// ================= COUNT LEAVES =================
int countLeaves(int index) {

    if (tree[index] == 0)
        return 0;

    if (tree[2 * index] == 0 && tree[2 * index + 1] == 0)
        return 1;

    int left = countLeaves(2 * index);
    int right = countLeaves(2 * index + 1);

    return left + right;
}

// ================= MAIN =================
int main() {

    ifstream file("tree.txt");

    int n, val;
    file >> n;

    for (int i = 0; i < n; i++) {
        file >> val;
        insert(val, 1);   // root index = 1
    }

    file.close();

    cout << "Preorder (Non-Recursive): ";
    preorderNR();

    cout << "\nLeaf Nodes Count: " << countLeaves(1);

    return 0;
}