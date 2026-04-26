#include<iostream>
#include<fstream>
using namespace std;

#define MAX 10

struct Node {
    int vertex, weight;
    Node* next;
};

struct Edge {
    int src, dest, weight;
};

class Graph {
public:
    Node* adj[MAX];
    Edge edges[MAX * MAX];
    int V, E;

    Graph() {
        V = 0;
        E = 0;
        for(int i = 0; i < MAX; i++)
            adj[i] = NULL;
    }

    void addEdge(int u, int v, int w) {
        Node* newNode = new Node;
        newNode->vertex = v;
        newNode->weight = w;
        newNode->next = adj[u];
        adj[u] = newNode;

        newNode = new Node;
        newNode->vertex = u;
        newNode->weight = w;
        newNode->next = adj[v];
        adj[v] = newNode;

        edges[E].src = u;
        edges[E].dest = v;
        edges[E].weight = w;
        E++;
    }

    // Load from file
    void loadFromFile(const char* filename) {
        ifstream file(filename);

        if(!file) {
            cout << "Error opening file\n";
            return;
        }

        file >> V >> E;

        int u, v, w;
        E = 0; // reset

        while(file >> u >> v >> w) {
            addEdge(u, v, w);
        }

        file.close();
    }

    void display() {
        for(int i = 0; i < V; i++) {
            cout << i << " -> ";
            Node* temp = adj[i];
            while(temp) {
                cout << "(" << temp->vertex << "," << temp->weight << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

// Union-Find
int parent[MAX];

int find(int i) {
    while(parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int u, int v) {
    int a = find(u);
    int b = find(v);
    parent[a] = b;
}

void sortEdges(Edge edges[], int E) {
    for(int i = 0; i < E-1; i++) {
        for(int j = 0; j < E-i-1; j++) {
            if(edges[j].weight > edges[j+1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

void kruskal(Edge edges[], int V, int E) {
    for(int i = 0; i < V; i++)
        parent[i] = i;

    sortEdges(edges, E);

    cout << "\nMST using Kruskal:\n";
    for(int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        if(find(u) != find(v)) {
            cout << u << " - " << v << " : " << edges[i].weight << endl;
            unionSet(u, v);
        }
    }
}

int main() {
    Graph g;

    g.loadFromFile("graph.txt");

    cout << "Adjacency List:\n";
    g.display();

    kruskal(g.edges, g.V, g.E);

    return 0;
}