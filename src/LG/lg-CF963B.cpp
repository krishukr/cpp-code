#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int cnt;
int head[MAX_N];

void create(int u, int v);

int fa[MAX_N];

int deg[MAX_N];
bool vis[MAX_N];

void dfs1(int x);

void dfs2(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, root{};
    read(n);
    for (int i = 1; i <= n; i++) {
        read(fa[i]);
        if (fa[i] == 0) {
            root = i;
        } else {
            create(fa[i], i);
        }
    }

    dfs1(root);
    if (vis[root]) {
        std::cout << "YES" << '\n';
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                dfs2(i);
            }
        }
    } else {
        std::cout << "NO" << '\n';
    }

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x) {
    vis[x] = true;
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa[x]) {
            continue;
        }
        dfs1(v);
        vis[x] ^= vis[v];
        if (vis[v]) {
            deg[v]++;
        } else {
            deg[x]++;
        }
    }
}

void dfs2(int x) {
    deg[x]--;
    std::cout << x << '\n';
    if (!vis[x] and --deg[fa[x]] == 0) {
        dfs2(fa[x]);
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa[x]) {
            continue;
        }
        if (vis[v] and --deg[v] == 0) {
            dfs2(v);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}