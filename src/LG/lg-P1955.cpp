#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int x;
    int y;
    int e;

    bool operator<(const Node &n) const { return e > n.e; }
} node[MAX_N];

int fa[MAX_N], b[MAX_N << 2];

void init(int x);

int query(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int tot = -1, n = read<int>();
        bool flag = true;
        memset(fa, 0, sizeof(fa));
        memset(b, 0, sizeof(b));
        memset(node, 0, sizeof(node));

        for (int i = 1; i <= n; i++) {
            node[i].x = read<int>(), node[i].y = read<int>(),
            node[i].e = read<int>();

            b[++tot] = node[i].x;
            b[++tot] = node[i].y;
        }

        std::sort(b, b + tot);
        int r = std::unique(b, b + tot) - b;
        for (int i = 1; i <= n; i++) {
            node[i].x = std::lower_bound(b, b + r, node[i].x) - b;
            node[i].y = std::lower_bound(b, b + r, node[i].y) - b;
        }
        init(r);
        std::sort(node + 1, node + n + 1);

        for (int i = 1; i <= n; i++) {
            int f1 = query(node[i].x);
            int f2 = query(node[i].y);

            if (node[i].e) {
                fa[f1] = f2;
            } else if (f1 == f2) {
                std::cout << "NO\n";
                flag = false;
                break;
            }
        }

        if (flag) {
            std::cout << "YES\n";
        }
    }

    return 0;
}

void init(int x) {
    for (int i = 1; i <= x; i++) {
        fa[i] = i;
    }
}

int query(int x) { return fa[x] == x ? x : (fa[x] = query(fa[x])); }

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