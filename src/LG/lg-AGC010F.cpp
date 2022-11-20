#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 3050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int a[MAX_N];
bool vis[MAX_N];

void dfs(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        dfs(i, 0);
        if (vis[i]) {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f) {
    vis[x] = false;
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs(v, x);
        if (!vis[v] and a[x] > a[v]) {
            vis[x] = true;
        }
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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