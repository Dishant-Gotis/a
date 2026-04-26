#include <iostream>
#include <fstream>
using namespace std;

int heap[100];
int size = 0;

// INSERT
void insert(int val) {

    heap[size] = val;
    int i = size;
    size++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] < heap[i]) {
            int temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;
            i = parent;
        }
        else {
            break;
        }
    }
}

// DELETE ROOT
void deleteRoot() {

    heap[0] = heap[size - 1];
    size--;

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size) {
            if (heap[left] > heap[largest])
                largest = left;
        }

        if (right < size) {
            if (heap[right] > heap[largest])
                largest = right;
        }

        if (largest != i) {
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            i = largest;
        }
        else {
            break;
        }
    }
}

// DISPLAY
void display() {
    for (int i = 0; i < size; i++)
        cout << heap[i] << " ";
}

int main() {

    ifstream file("heap.txt");

    int n, val;
    file >> n;

    for (int i = 0; i < n; i++) {
        file >> val;
        insert(val);
    }

    file.close();

    cout << "Heap: ";
    display();

    deleteRoot();

    cout << "\nAfter Delete: ";
    display();

    return 0;
}



//min heap
// 
#include <iostream>
#include <fstream>
using namespace std;

int heap[100];
int size = 0;

// ================= INSERT =================
void insert(int val) {

    heap[size] = val;
    int i = size;
    size++;

    while (i > 0) {

        int parent = (i - 1) / 2;

        // MIN HEAP condition
        if (heap[parent] > heap[i]) {

            int temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;

            i = parent;
        }
        else {
            break;
        }
    }
}

// ================= DELETE ROOT =================
void deleteRoot() {

    if (size == 0) {
        cout << "Heap is empty\n";
        return;
    }

    heap[0] = heap[size - 1];
    size--;

    int i = 0;

    while (1) {

        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size) {
            if (heap[left] < heap[smallest]) {
                smallest = left;
            }
        }

        if (right < size) {
            if (heap[right] < heap[smallest]) {
                smallest = right;
            }
        }

        if (smallest != i) {

            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;

            i = smallest;
        }
        else {
            break;
        }
    }
}

// ================= DISPLAY =================
void display() {

    if (size == 0) {
        cout << "Heap is empty\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << heap[i] << " ";
    }
}

// ================= MAIN =================
int main() {

    ifstream file("heap.txt");

    if (!file) {
        cout << "Error opening file\n";
        return 0;
    }

    int n, val;
    file >> n;

    for (int i = 0; i < n; i++) {
        file >> val;
        insert(val);
    }

    file.close();

    cout << "Min Heap: ";
    display();

    deleteRoot();

    cout << "\nAfter deleting root: ";
    display();

    return 0;
}