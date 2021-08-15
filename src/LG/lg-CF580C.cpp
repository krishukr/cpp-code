#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N], ind[MAX_N];
int cnt, ans, n, m;

void create(int u, int v);

void dfs(int x, int f, int s);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs(1, 0, w[1]);
    std::cout << ans << '\n';
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
    ind[v]++;
}

void dfs(int x, int f, int s) {
    if (ind[x] == 1 and x != 1) {
        if (s <= m) {
            ans++;
        }
        return;
    } else {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (v == f) {
                continue;
            }
            if (!w[v]) {
                dfs(v, x, 0);
            } else if (s + 1 <= m) {
                dfs(v, x, s + 1);
            }
        }
    }
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