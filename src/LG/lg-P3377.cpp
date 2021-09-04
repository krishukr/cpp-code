#include <cstdio>
#include <iostream>

const int MAX_N = 100001;

struct Node {
    int l;
    int r;
    int d;
    int f;
    bool vis;

    bool operator>(const Node &n) const { return d > n.d; }
    bool operator==(const Node &n) const { return d == n.d; }
} node[MAX_N];

inline int find(int x);

int merge(int x, int y);

void work(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        node[i].d = read<int>();
        node[i].l = node[i].r = -1;
        node[i].f = i;
    }

    while (m--) {
        int op = read<int>();
        if (op == 1) {
            int x = read<int>(), y = read<int>();
            if (node[x].vis or node[y].vis) {
                continue;
            }
            x = find(x), y = find(y);
            if (x == y) {
                continue;
            }

            merge(x, y);
        } else if (op == 2) {
            int x = read<int>();
            work(x);
        }
    }

    return 0;
}

inline int find(int x) {
    if (node[x].f == x) {
        return x;
    } else {
        return node[x].f = find(node[x].f);
    }
}

int merge(int x, int y) {
    if (x == -1) {
        return y;
    }
    if (y == -1) {
        return x;
    }

    if (node[x] > node[y] or (node[x] == node[y] and x > y)) {
        std::swap(x, y);
    }

    int tmp = merge(node[x].r, y);
    node[x].r = tmp;
    node[tmp].f = x;

    std::swap(node[x].l, node[x].r);
    return x;
}

void work(int x) {
    if (node[x].vis) {
        std::cout << "-1\n";
        return;
    }

    x = find(x);
    std::cout << node[x].d << '\n';
    node[x].vis = true;
    node[node[x].l].f = node[x].l;
    node[node[x].r].f = node[x].r;
    node[x].f = merge(node[x].l, node[x].r);
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}