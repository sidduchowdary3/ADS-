#include <bits/stdc++.h>
using namespace std;

void topologicalSortUtil(int v, vector<vector<int> >& adj, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;
    for (int i : adj[v]) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }
    Stack.push(v);
}

void topologicalSort(vector<vector<int> >& adj, int V) {
    stack<int> Stack;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            topologicalSortUtil(i, adj, visited, Stack);
    }
    cout << "Topological sorting of the graph: ";
    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
    cout << endl;
}

int main() {
    int V;
    int E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);
    cout << "Enter the edges in the format \"from to\":\n";
    for (int i = 0; i < E; ++i) {
        int from, to;
        cin >> from >> to;
        adj[from].push_back(to);
    }

    topologicalSort(adj, V);

    return 0;
}
