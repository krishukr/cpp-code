#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 200050;

struct {
    int v;
    int w;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int fa[MAX_N];
ll dis[MAX_N];
bool vis[MAX_N];
int des;
ll dde;

void dfs1(int x, int f);

void dfs2(int x, int f);

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
    for (int i = 1; i < n; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }

    dfs1(1, 0);
    const auto pl = des;
    dde = dis[pl] = 0;
    dfs1(pl, 0);
    const auto pr = des;
    std::cout << dde << '\n';

    for (int i = pr; i; i = fa[i]) {
        vis[i] = true;
    }
    bool flag{};
    int l{pl}, r{pr};
    for (int i = fa[pr]; i != pl; i = fa[i]) {
        const auto dl = dis[i], dr = dis[pr] - dis[i];
        dde = dis[i] = 0;
        dfs2(i, 0);
        if (dde == dl and !flag) {
            l = i;
            flag = true;
        }
        if (dde == dr) {
            r = i;
        }
    }

    int ans{};
    for (int i = r; i != l; i = fa[i]) {
        ans++;
    }
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs1(int x, int f) {
    fa[x] = f;
    if (dde < dis[x]) {
        dde = dis[x];
        des = x;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        const auto w = node[i].w;
        if (v == f) {
            continue;
        }
        dis[v] = dis[x] + w;
        dfs1(v, x);
    }
}

void dfs2(int x, int f) {
    if (dde < dis[x]) {
        dde = dis[x];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const auto v = node[i].v;
        const auto w = node[i].w;
        if (v == f or vis[v]) {
            continue;
        }
        dis[v] = dis[x] + w;
        dfs2(v, x);
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