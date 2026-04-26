#include <iostream>
#include <fstream>
using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

class GraphMatrix {
    int vertices;
    int** adjacencyMatrix;

    int findParent(int parent[], int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findParent(parent, parent[node]);
    }

    void unionSets(int parent[], int node1, int node2) {
        int parent1 = findParent(parent, node1);
        int parent2 = findParent(parent, node2);
        parent[parent1] = parent2;
    }

    void sortEdges(Edge edges[], int edgeCount) {
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }

public:
    GraphMatrix(const char* filename) {
        ifstream file(filename);
        file >> vertices;

        adjacencyMatrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                file >> adjacencyMatrix[i][j];
        }
        file.close();
    }

    void kruskal() {
        Edge edges[100];
        int edgeCount = 0;

        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    edges[edgeCount++] = {i, j, adjacencyMatrix[i][j]};
                }
            }
        }

        sortEdges(edges, edgeCount);

        int parent[100];
        for (int i = 0; i < vertices; i++)
            parent[i] = i;

        cout << "MST:\n";

        for (int i = 0; i < edgeCount; i++) {
            int p1 = findParent(parent, edges[i].source);
            int p2 = findParent(parent, edges[i].destination);

            if (p1 != p2) {
                cout << edges[i].source << " - "
                     << edges[i].destination << " : "
                     << edges[i].weight << endl;

                unionSets(parent, p1, p2);
            }
        }
    }
};

int main() {
    GraphMatrix g("graph.txt");
    g.kruskal();
    return 0;
}