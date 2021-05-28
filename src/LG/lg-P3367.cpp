#include <iostream>

using namespace std;

const int MAX_N = 100001;

int fa[MAX_N];

void init(int n);

int find(int x);

void merge(int i, int j);

int main() {
    int n, m;
    int z, x, y;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < m; i++) {
        cin >> z >> x >> y;
        if (z == 1) {
            merge(x, y);
        } else {
            cout << (find(x) == find(y) ? "Y" : "N") << endl;
        }
    }

    return 0;
}

void init(int n) {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
}

int find(int x) { return x == fa[x] ? x : (fa[x] = find(fa[x])); }

void merge(int i, int j) { fa[find(i)] = find(j); }