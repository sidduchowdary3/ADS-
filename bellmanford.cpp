#include<iostream>
#include<climits>
using namespace std;

void BellmanFord(int graph[][3], int V, int E, int src) {
    int dis[V];
    for (int i = 0; i < V; i++)
        dis[i] = INT_MAX;
    dis[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];
            if (dis[u] != INT_MAX && dis[u] + weight < dis[v]) {
                dis[v] = dis[u] + weight;
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph[i][0];
        int v = graph[i][1];
        int weight = graph[i][2];
        if (dis[u] != INT_MAX && dis[u] + weight < dis[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distances from the source vertex
    cout << "Vertex Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t" << dis[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    int graph[E][3];
    cout << "Enter edges (from, to, weight):" << endl;
    for (int i = 0; i < E; i++) {
        cin >> graph[i][0] >> graph[i][1] >> graph[i][2];
    }

    int source_vertex;
    cout << "Enter the source vertex: ";
    cin >> source_vertex;

    BellmanFord(graph, V, E, source_vertex);

    return 0;
}
