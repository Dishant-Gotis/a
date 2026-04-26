#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int main() {
    ifstream file("input.txt");

    int n;
    file >> n;

    int adj[10][10];

    // read matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> adj[i][j];

    queue<int> q;
    bool visited[10] = {false};

    q.push(0);          // start from node 0
    visited[0] = true;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        cout << x << " ";

        for (int i = 0; i < n; i++) {
            if (adj[x][i] == 1 && visited[i] == false) {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    return 0;
}