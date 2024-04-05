#include <iostream>
#include <vector>
using namespace std;
int find(vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    int parentNode = parent[x];
     return parentNode;
}
void unionSets(vector<int>& parent, int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);
    if (xRoot != yRoot) {
        if (xRoot < yRoot) {
            parent[yRoot] = xRoot;
        } else {
            parent[xRoot] = yRoot;
        }
    }
}
int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int choice;
    do {
        cout << "\nMenu:\n1. Find\n2. Union\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int x;
                cout << "Enter the element: ";
                cin >> x;
                int root = find(parent, x);
   cout << "Parent of " << x << " is " <<root << endl;
                break;
            }
            case 2: {
                int x, y;
                cout << "Enter two elements to union: ";
                cin >> x >> y;
                unionSets(parent, x, y);
                cout << "Union performed." << endl;
                break;
            }
            case 3:
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
