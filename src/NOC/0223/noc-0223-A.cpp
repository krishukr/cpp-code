#include <cstdio>
#include <iostream>

const int MAX_N = 150050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

bool vis[MAX_N], gru[MAX_N];

void create(int u, int v);

void dfs(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i);
    }

    for (int i = 1; i <= n; i++) {
        std::cout << gru[i] + 1 << ' ';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    int sme = 0;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (!vis[v]) {
            vis[v] = true;
            gru[v] = !gru[x];
            dfs(v);
        }
        if (gru[v] == gru[x]) {
            sme++;
        }
    }

    if (sme > 1) {
        gru[x] = !gru[x];
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
