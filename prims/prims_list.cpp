#include <iostream>
#include <fstream>
using namespace std;

// Node for adjacency list
struct ListNode {
    int destination;
    int weight;
    ListNode* next;
};

class Graph {
    int vertices;
    int edges;
    ListNode** adjacencyList;

    // Find vertex with minimum key value not yet included in MST
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

        file >> vertices >> edges;

        adjacencyList = new ListNode*[vertices];
        for (int i = 0; i < vertices; i++)
            adjacencyList[i] = NULL;

        int source, destination, weight;

        // Read edges
        for (int i = 0; i < edges; i++) {
            file >> source >> destination >> weight;

            // Add edge source → destination
            ListNode* node1 = new ListNode{destination, weight, adjacencyList[source]};
            adjacencyList[source] = node1;

            // Add edge destination → source (undirected)
            ListNode* node2 = new ListNode{source, weight, adjacencyList[destination]};
            adjacencyList[destination] = node2;
        }

        file.close();
    }

    void prims() {
        int parent[100];
        int key[100];
        bool inMST[100];

        // Initialize
        for (int i = 0; i < vertices; i++) {
            key[i] = 1e9;
            inMST[i] = false;
        }

        key[0] = 0;
        parent[0] = -1;

        // Build MST
        for (int count = 0; count < vertices - 1; count++) {
            int u = findMinKey(key, inMST);
            inMST[u] = true;

            // Traverse adjacency list of u
            ListNode* temp = adjacencyList[u];
            while (temp != NULL) {
                int v = temp->destination;
                int w = temp->weight;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                }

                temp = temp->next;
            }
        }

        cout << "Minimum Spanning Tree:\n";
        for (int i = 1; i < vertices; i++) {
            cout << parent[i] << " - " << i
                 << " : " << key[i] << endl;
        }
    }

    ~Graph() {
        for (int i = 0; i < vertices; i++) {
            ListNode* temp = adjacencyList[i];
            while (temp) {
                ListNode* del = temp;
                temp = temp->next;
                delete del;
            }
        }
        delete[] adjacencyList;
    }
};

int main() {
    Graph g("list.txt");
    g.prims();
    return 0;
}