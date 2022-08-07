#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 100050;

struct {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

int deg[MAX_N];
int dis[2][MAX_N];
bool vis[MAX_N], vid[MAX_N];

void spfa(int s, int _kk);

int n, m, k;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, m, k);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        read(x, y, z);
        create(x, y, z);
        create(y, x, z);
    }

    deg[1] = deg[n] = 0x3f3f3f3f;
    for (int i = 2; i < n; i++) {
        std::fill(vid, vid + n + 10, false);
        for (int j = head[i]; j; j = node[j].nxt) {
            const auto v = node[j].v;
            if (vid[v]) {
                continue;
            }
            vid[v] = true;
            deg[i]++;
        }
    }

    spfa(1, 0);
    spfa(n, 1);
    int mn = dis[0][n], sn{0x3f3f3f3f};
    for (int i = 1; i <= n; i++) {
        if (k > deg[i]) {
            continue;
        }
        for (int j = head[i]; j; j = node[j].nxt) {
            const auto v = node[j].v, w = node[j].w;
            if (mn < dis[0][i] + dis[1][v] + w and k <= deg[v]) {
                sn = std::min(sn, dis[0][i] + dis[1][v] + w);
            }
        }
    }
    std::cout << (sn == 0x3f3f3f3f ? -1 : sn) << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void spfa(int s, int _kk) {
    for (int i = 1; i <= n; i++) {
        dis[_kk][i] = 0x3f3f3f3f;
    }
    std::fill(vis, vis + n + 10, false);
    std::queue<int> q;
    q.push(s);
    dis[_kk][s] = 0;

    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        vis[p] = false;
        for (int i = head[p]; i; i = node[i].nxt) {
            const auto v = node[i].v, w = node[i].w;
            if (dis[_kk][v] > dis[_kk][p] + w and k <= deg[v]) {
                dis[_kk][v] = dis[_kk][p] + w;
                if (!vis[v]) {
                    q.push(v);
                }
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}