#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 300050;
constexpr int MAX_L = 21;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

int w[MAX_N];
int f[MAX_L][MAX_N], d[MAX_N];

void dfs1(int x, int fa);

int LCA(int x, int y);

int ans[MAX_N];
std::vector<std::pair<int, int>> q1[MAX_N], q2[MAX_N];
int c1[MAX_N << 1], c2[MAX_N << 1];

void dfs2(int x);

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }
    for (int i = 1; i <= n; i++) {
        read(w[i]);
    }

    dfs1(1, 0);
    for (int i = 1; i <= m; i++) {
        int s, t;
        read(s, t);
        if (s == t) {
            ans[s] += (w[s] == 0);
            continue;
        }
        const int l = LCA(s, t);
        if (l != s and l != t) {
            q1[s].push_back({l, 0});
            q1[l].push_back({t, d[s] - d[l]});
            q2[t].push_back({l, d[s] - d[l]});
            q2[l].push_back({s, 0});
            if (d[s] - d[l] == w[l]) {
                ans[l]--;
            }
        } else {
            q1[s].push_back({t, 0});
            q2[t].push_back({s, 0});
        }
    }

    dfs2(1);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs1(int x, int fa) {
    d[x] = d[fa] + 1;
    for (int i = 0; i + 1 < MAX_L; i++) {
        f[i + 1][x] = f[i][f[i][x]];
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        f[0][v] = x;
        dfs1(v, x);
    }
}

int LCA(int x, int y) {
    if (d[x] < d[y]) {
        std::swap(x, y);
    }
    if (d[x] != d[y]) {
        for (int i = MAX_L - 1; i >= 0; i--) {
            if (d[y] <= d[f[i][x]]) {
                x = f[i][x];
            }
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = MAX_L - 1; i >= 0; i--) {
        if (f[i][x] == f[i][y]) {
            continue;
        }
        x = f[i][x];
        y = f[i][y];
    }
    return f[0][x];
}

void dfs2(int x) {
    const int us = c1[d[x] + w[x]], uf = c2[MAX_N - d[x] + w[x]];
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f[0][x]) {
            continue;
        }
        dfs2(v);
    }

    for (const auto& i : q1[x]) {
        if (d[i.first] < d[x]) {
            c1[d[x] + i.second]++;
        }
    }
    for (const auto& i : q2[x]) {
        if (d[i.first] < d[x]) {
            c2[MAX_N - d[i.first] + i.second]++;
        }
    }

    ans[x] += c1[d[x] + w[x]] - us + c2[MAX_N - d[x] + w[x]] - uf;
    for (const auto& i : q1[x]) {
        if (d[i.first] > d[x]) {
            c2[MAX_N - d[x] + i.second]--;
        }
    }
    for (const auto& i : q2[x]) {
        if (d[i.first] > d[x]) {
            c1[d[i.first] + i.second]--;
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