#include <iostream>
#include <fstream>
using namespace std;

#define MAX 10
#define INF 999

int n;
int graph[MAX][MAX];

// ================= LOAD GRAPH =================
void loadGraph() {
    ifstream file("graph.txt");

    file >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> graph[i][j];
        }
    }

    file.close();
}

// =======================================================
// ================= ADJ LIST (NO STL) ====================
// =======================================================

struct Node {
    int vertex;
    Node* next;
};

Node* adjList[MAX];

void createAdjList() {

    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (graph[i][j] != 0) {

                Node* temp = new Node();
                temp->vertex = j;
                temp->next = adjList[i];
                adjList[i] = temp;
            }
        }
    }
}

// =======================================================
// ================= BFS ================================
// =======================================================

void BFS(int start) {

    int visited[MAX];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int queue[MAX];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {

        int v = queue[front++];
        cout << v << " ";

        for (int i = 0; i < n; i++) {
            if (graph[v][i] != 0 && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
}

// =======================================================
// ================= DFS ================================
// =======================================================

void DFSUtil(int v, int visited[]) {

    cout << v << " ";
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] != 0 && visited[i] == 0) {
            DFSUtil(i, visited);
        }
    }
}

void DFS(int start) {

    int visited[MAX];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    DFSUtil(start, visited);
}

// =======================================================
// ================= PRIM ===============================
// =======================================================

int minKey(int key[], int visited[]) {

    int min = INF;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (visited[i] == 0 && key[i] < min) {
            min = key[i];
            index = i;
        }
    }

    return index;
}

void primMST() {

    int parent[MAX];
    int key[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        visited[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {

        int u = minKey(key, visited);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && visited[v] == 0) {
                if (graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }
    }

    cout << "\nPrim MST:\n";
    for (int i = 1; i < n; i++) {
        cout << parent[i] << " - " << i << " = " << graph[i][parent[i]] << endl;
    }
}

// =======================================================
// ================= KRUSKAL ============================
// =======================================================

int parentArr[MAX];

int find(int i) {
    while (parentArr[i] != i)
        i = parentArr[i];
    return i;
}

void unionSet(int i, int j) {
    int a = find(i);
    int b = find(j);
    parentArr[a] = b;
}

void kruskal() {

    for (int i = 0; i < n; i++) {
        parentArr[i] = i;
    }

    int edges = 0;

    cout << "\nKruskal MST:\n";

    while (edges < n - 1) {

        int min = INF;
        int a = -1, b = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (graph[i][j] != 0) {

                    int x = find(i);
                    int y = find(j);

                    if (x != y) {
                        if (graph[i][j] < min) {
                            min = graph[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
        }

        unionSet(a, b);
        cout << a << " - " << b << " = " << min << endl;

        edges++;
    }
}

// =======================================================
// ================= DIJKSTRA ===========================
// =======================================================

void dijkstra(int src) {

    int dist[MAX];
    int visited[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {

        int min = INF, u = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && visited[v] == 0) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    cout << "\nDijkstra:\n";
    for (int i = 0; i < n; i++) {
        cout << src << " -> " << i << " = " << dist[i] << endl;
    }
}

// =======================================================
// ================= MAIN ===============================
// =======================================================

int main() {

    loadGraph();
    createAdjList();

    cout << "BFS: ";
    BFS(0);

    cout << "\nDFS: ";
    DFS(0);

    primMST();
    kruskal();
    dijkstra(0);

    return 0;
}