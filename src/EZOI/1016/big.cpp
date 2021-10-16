#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 1000050;

struct Node {
    int x;
    int y;
    int p;
    int w;

    inline bool operator<(const Node &x) const { return w < x.w; }
} d[MAX_N];

int fa[MAX_N], ma[MAX_N], re[MAX_N], rx[MAX_N], ry[MAX_N];

void init(int x);

int find(int x);

void merge(int i, int j);

template <typename T>
T read();

int main() {
    freopen("big.in", "r", stdin);
    freopen("big.out", "w", stdout);

    int n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = read<int>(), p = (i - 1) * m + j;
            d[p] = (Node){i, j, p, x};
        }
    }
    init(n + m);
    std::sort(d + 1, d + n * m + 1);

    int j;
    for (int i = 1; i <= n * m; i = j) {
        j = i;
        while (d[j].w == d[i].w) {
            j++;
        }
        for (int k = i; k < j; k++) {
            merge(d[k].x, d[k].y + n);
        }
        for (int k = i; k < j; k++) {
            ma[find(d[k].x)] =
                std::max(ma[find(d[k].x)], std::max(rx[d[k].x], ry[d[k].y]));
        }
        for (int k = i; k < j; k++) {
            re[d[k].p] = ma[find(d[k].x)] + 1;
            rx[d[k].x] = re[d[k].p];
            ry[d[k].y] = re[d[k].p];
        }
        for (int k = i; k < j; k++) {
            ma[d[k].x] = 0;
            fa[d[k].x] = d[k].x;
            ma[d[k].x + n] = 0;
            fa[d[k].x + n] = d[k].x + n;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << re[(i - 1) * m + j] << ' ';
        }
        std::cout << '\n';
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init(int x) {
    for (int i = 1; i <= x; i++) {
        fa[i] = i;
    }
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int i, int j) { fa[find(i)] = find(j); }

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