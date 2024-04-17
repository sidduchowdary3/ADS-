#include <bits/stdc++.h>
using namespace std;

vector<int> topologicalSort(vector<vector<int> >& adj, int V) {
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        for (auto it : adj[node]) {
            indegree[it]--;
            if (indegree[it] == 0) {
                q.push(it);
            }
        }
    }

    if (result.size() != V) {
        cout << "Graph contains cycle!" << endl;
        return {};
    }

    return result;
}

int main() {
    int n; // Number of vertices
    int e; // Number of edges

    cout << "Enter the number of vertices: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> e;

    vector<vector<int>> adj(n);
    cout << "Enter the edges in the format 'from to' (zero-indexed):" << endl;
    for (int i = 0; i < e; i++) {
        int from, to;
        cin >> from >> to;
        adj[from].push_back(to);
    }

    cout << "Topological sorting of the graph: ";
    vector<int> result = topologicalSort(adj, n);

    for (auto i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
