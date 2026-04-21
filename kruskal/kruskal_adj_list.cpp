#include <iostream>
using namespace std;

// Structure to store an edge
struct Edge {
    int source;
    int destination;
    int weight;
};

class GraphMatrix {
    int vertices;
    int** adjacencyMatrix;

    // FIND: finds parent of a node (with path compression)
    int findParent(int parent[], int node) {
        if (parent[node] == node)
            return node;

        // Path compression
        return parent[node] = findParent(parent, parent[node]);
    }

    // UNION: merges two sets
    void unionSets(int parent[], int node1, int node2) {
        int parent1 = findParent(parent, node1);
        int parent2 = findParent(parent, node2);

        // Merge the sets
        parent[parent1] = parent2;
    }

    // Sort edges using simple Bubble Sort
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
    GraphMatrix(int v) {
        vertices = v;

        // Allocate adjacency matrix
        adjacencyMatrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            adjacencyMatrix[i] = new int[vertices];
            for (int j = 0; j < vertices; j++)
                adjacencyMatrix[i][j] = 0;
        }
    }

    // Add undirected edge
    void addEdge(int source, int destination, int weight) {
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }

    // Kruskal Algorithm
    void kruskal() {
        Edge edges[vertices * vertices];
        int edgeCount = 0;

        // Step 1: Convert adjacency matrix to edge list
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    edges[edgeCount].source = i;
                    edges[edgeCount].destination = j;
                    edges[edgeCount].weight = adjacencyMatrix[i][j];
                    edgeCount++;
                }
            }
        }

        // Step 2: Sort edges by weight
        sortEdges(edges, edgeCount);

        // Step 3: Initialize parent array (each node is its own parent)
        int parent[vertices];
        for (int i = 0; i < vertices; i++)
            parent[i] = i;

        cout << "Minimum Spanning Tree:\n";

        // Step 4: Process edges
        for (int i = 0; i < edgeCount; i++) {
            int parentSource = findParent(parent, edges[i].source);
            int parentDestination = findParent(parent, edges[i].destination);

            // If parents are different → no cycle
            if (parentSource != parentDestination) {
                cout << edges[i].source << " - "
                     << edges[i].destination << " : "
                     << edges[i].weight << endl;

                // Merge the sets
                unionSets(parent, parentSource, parentDestination);
            }
        }
    }
};

int main() {
    GraphMatrix graph(4);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    graph.kruskal();

    return 0;
}