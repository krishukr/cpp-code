#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

struct Node {
    int l;
    int r;
    int d;
    int f;

    bool operator<(const Node &n) const { return d < n.d; }
    bool operator==(const Node &n) const { return d == n.d; }
} node[MAX_N];

inline int find(int x);

int merge(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    while (!std::cin.eof()) {
        int n = read<int>();

        for (int i = 1; i <= n; i++) {
            node[i].d = read<int>();
            node[i].l = node[i].r = -1;
            node[i].f = i;
        }

        int m = read<int>();
        for (int i = 1; i <= m; i++) {
            int x = read<int>(), y = read<int>();
            x = find(x), y = find(y);

            if (x == y) {
                std::cout << -1 << '\n';
            } else {
                node[x].d /= 2, node[y].d /= 2;
                node[x].f = merge(node[x].l, node[x].r);
                node[x].l = node[x].r = -1;
                node[y].f = merge(node[y].l, node[y].r);
                node[y].l = node[y].r = -1;

                int tmp = merge(node[x].f, node[y].f);
                tmp = merge(tmp, x);
                tmp = merge(tmp, y);
                node[tmp].f = node[x].f = node[y].f = tmp;

                std::cout << node[tmp].d << '\n';
            }
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

    if (node[x] < node[y] or (node[x] == node[y] and x < y)) {
        std::swap(x, y);
    }

    int tmp = merge(node[x].r, y);
    node[x].r = tmp;
    node[tmp].f = x;

    std::swap(node[x].l, node[x].r);
    return x;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    if (ch == EOF) {
        std::exit(0);
    }
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
        if (ch == EOF) {
            std::exit(0);
        }
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
        if (ch == EOF) {
            std::exit(0);
        }
    }
    return x * f;
}