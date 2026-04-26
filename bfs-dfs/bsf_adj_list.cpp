#include <iostream>
#include <fstream>
using namespace std;

class Graph {
    int V;
    
    struct Node {
        int data;
        Node* next;
    };

    Node** adj;

public:
    Graph(const char* filename) {
        ifstream file(filename);

        file >> V;

        adj = new Node*[V];
        for (int i = 0; i < V; i++)
            adj[i] = NULL;

        int u, v;
        while (file >> u >> v) {
            Node* n1 = new Node{v, adj[u]};
            adj[u] = n1;

            Node* n2 = new Node{u, adj[v]};
            adj[v] = n2;
        }

        file.close();
    }

    void BFS(int start) {
        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        int* queue = new int[V];
        int front = 0, rear = 0;

        visited[start] = true;
        queue[rear++] = start;

        while (front < rear) {
            int node = queue[front++];
            cout << node << " ";

            Node* temp = adj[node];
            while (temp != NULL) {
                if (!visited[temp->data]) {
                    visited[temp->data] = true;
                    queue[rear++] = temp->data;
                }
                temp = temp->next;
            }
        }

        cout << endl;

        delete[] visited;
        delete[] queue;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            Node* temp = adj[i];
            while (temp) {
                Node* del = temp;
                temp = temp->next;
                delete del;
            }
        }
        delete[] adj;
    }
};

int main() {
    Graph g("graph.txt");
    g.BFS(0);
    return 0;
}