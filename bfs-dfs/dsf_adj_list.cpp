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

    void dfsUtil(int v, bool* visited) {
        visited[v] = true;
        cout << v << " ";

        Node* temp = adj[v];
        while (temp != NULL) {
            if (!visited[temp->data]) {
                dfsUtil(temp->data, visited);
            }
            temp = temp->next;
        }
    }

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

    void DFS(int start) {
        bool* visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        dfsUtil(start, visited);
        cout << endl;

        delete[] visited;
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
    g.DFS(0);
    return 0;
}