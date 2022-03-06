#include <cstdio>
#include <iostream>

const int MAX_N = 300050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

bool a[MAX_N];
bool dp1[MAX_N], dp2[MAX_N];
int siz[MAX_N];

void create(int u, int v);

void dfs1(int x, int f);

void dfs2(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << (int)(dp1[i] or dp2[i]) << ' ';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    if (a[x]) {
        siz[x] = dp1[x] = true;
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs1(v, x);
        siz[x] += siz[v];
        if ((siz[v] > 1 and dp1[v]) or a[v]) {
            dp1[x] = true;
        }
    }
}

void dfs2(int x, int f) {
    if (a[f] or dp1[x]) {
        dp2[x] = true;
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        if (dp2[x] and siz[1] - siz[v] > 1) {
            dp2[v] = true;
        }
        dfs2(v, x);
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