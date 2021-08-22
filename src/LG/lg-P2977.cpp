#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N], ind[MAX_N];
int cnt, n, k, ans;

void create(int u, int v);

void dfs(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), k = read<int>();

    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }
    if (n == 2) {
        std::cout << "1\n";
        return 0;
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();

        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        if (ind[i] - 1) {
            dfs(i, 0);
            std::cout << ans << '\n';
            return 0;
        }
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    ind[v]++;
}

void dfs(int x, int f) {
    if (ind[x] == 1) {
        w[x] = 1;
        return;
    }
    int res = 0;

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x);
        w[x] += w[v];
    }

    res = std::min(k, w[x] / 2);
    if (res < k and w[x] > (res * 2)) {
        w[x] = 1;
    } else {
        w[x] = 0;
    }

    ans += res;
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