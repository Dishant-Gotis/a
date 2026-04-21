#include <iostream>
#include <fstream>
using namespace std;

class Graph {
    int V;
    int** adj;

    void dfsUtil(int v, bool* visited) {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < V; i++) {
            if (adj[v][i] != 0 && !visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }

public:
    Graph(const char* filename) {
        ifstream file(filename);

        file >> V;

        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            for (int j = 0; j < V; j++) {
                file >> adj[i][j];
            }
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
        for (int i = 0; i < V; i++)
            delete[] adj[i];
        delete[] adj;
    }
};

int main() {
    Graph g("graph.txt");
    g.DFS(0);
    return 0;
}