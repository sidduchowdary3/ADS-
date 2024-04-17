#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;
vector<int> ranks;

void initialize(int n) {
    parent.resize(n);
    ranks.resize(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int findPar(int node) {
    if (node == parent[node]) {
        return node;
    }
    return parent[node] = findPar(parent[node]); // Path compression
}

void simpleunion(int u, int v) {
    u = findPar(u);
    v = findPar(v);
    if (ranks[u] < ranks[v]) {
        parent[u] = v;
    } else if (ranks[v] < ranks[u]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        ranks[u]++;
    }
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    initialize(n);

    char choice;
    do {
        cout << "Enter 'u' for union or 'f' for find operation, or 'q' to quit: ";
        cin >> choice;

        if (choice == 'u') {
            int u, v;
            cout << "Enter values for u and v (separated by space) for union operation: ";
            cin >> u >> v;
            simpleunion(u, v);
        } else if (choice == 'f') {
            int node;
            cout << "Enter the value of the node for find operation: ";
            cin >> node;
            cout << "Parent of " << node << ": " << findPar(node) << endl;
        }

    } while (choice != 'q');

    return 0;
}
