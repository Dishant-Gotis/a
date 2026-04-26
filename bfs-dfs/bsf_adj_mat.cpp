#include <iostream>
#include <fstream>
using namespace std;

class Graph {
    int V;
    int** adj;

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

            for (int i = 0; i < V; i++) {
                if (adj[node][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    queue[rear++] = i;
                }
            }
        }

        cout << endl;

        delete[] visited;
        delete[] queue;
    }

    ~Graph() {
        for (int i = 0; i < V; i++)
            delete[] adj[i];
        delete[] adj;
    }
};

int main() {
    Graph g("graph.txt");
    g.BFS(0);
    return 0;
}