#include <iostream>
#include <fstream>
using namespace std;

class Graph {
    int vertices;
    int** adjacencyMatrix;

    // Find vertex with minimum key value
    int findMinKey(int key[], bool inMST[]) {
        int min = 1e9;
        int minIndex = -1;

        for (int i = 0; i < vertices; i++) {
            if (!inMST[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

public:
    Graph(const char* filename) {
        ifstream file(filename);

        file >> vertices;

        adjacencyMatrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++) {
                file >> adjacencyMatrix[i][j];
            }
        }

        file.close();
    }

    void prims() {
        int parent[100];      // stores MST
        int key[100];         // minimum weight
        bool inMST[100];      // included in MST or not

        // Initialize
        for (int i = 0; i < vertices; i++) {
            key[i] = 1e9;
            inMST[i] = false;
        }

        key[0] = 0;     // start from node 0
        parent[0] = -1; // root has no parent

        // MST will have (V-1) edges
        for (int count = 0; count < vertices - 1; count++) {
            int u = findMinKey(key, inMST);
            inMST[u] = true;

            // Update neighbors
            for (int v = 0; v < vertices; v++) {
                if (adjacencyMatrix[u][v] != 0 && !inMST[v]
                    && adjacencyMatrix[u][v] < key[v]) {

                    parent[v] = u;
                    key[v] = adjacencyMatrix[u][v];
                }
            }
        }

        cout << "Minimum Spanning Tree:\n";
        for (int i = 1; i < vertices; i++) {
            cout << parent[i] << " - " << i
                 << " : " << adjacencyMatrix[i][parent[i]] << endl;
        }
    }
};

int main() {
    Graph g("graph.txt");
    g.prims();
    return 0;
}