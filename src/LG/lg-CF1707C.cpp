#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int fa[MAX_N];

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

std::vector<int> v[MAX_N];
int dep[MAX_N], g[MAX_N], ans[MAX_N];
bool vis[MAX_N];
int tot;

void dfs1(int x, int f);

void dfs2(int x, int f);

void dfs3(int x, int f);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }

    std::vector<std::pair<int, int>> wx;
    for (int i = 1; i <= m; i++) {
        int x, y;
        read(x, y);
        if (find(x) != find(y)) {
            create(x, y);
            create(y, x);
            fa[find(x)] = find(y);
        } else {
            wx.push_back({x, y});
        }
    }

    dfs1(1, 0);
    for (auto& i : wx) {
        if (dep[i.first] < dep[i.second]) {
            std::swap(i.first, i.second);
        }
        v[i.first].push_back(i.second);
    }
    dfs2(1, 0);
    dfs3(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << (int)(ans[i] == tot);
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int f) {
    dep[x] = dep[f] + 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const int& v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs1(v, x);
    }
}

void dfs2(int x, int f) {
    g[dep[x]] = x;
    vis[x] = true;
    for (const auto& i : v[x]) {
        tot++;
        ans[x]++;
        if (vis[i]) {
            ans[1]++;
            ans[g[dep[i] + 1]]--;
        } else {
            ans[i]++;
        }
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        const int& v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs2(v, x);
    }
    vis[x] = false;
}

void dfs3(int x, int f) {
    ans[x] += ans[f];
    for (int i = head[x]; i; i = node[i].nxt) {
        const int& v = node[i].v;
        if (v == f) {
            continue;
        }
        dfs3(v, x);
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