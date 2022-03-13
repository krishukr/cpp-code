#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 10050;

struct Node {
    int u;
    int v;
    int w;
    int nxt;

    friend std::ostream& operator<<(std::ostream& o, const Node& x) {
        o << x.u << ' ' << x.v;
        return o;
    }
} node[MAX_N];

int head[MAX_N];
int cnt;

int dis[MAX_N];
bool vis[MAX_N];

void create(int u, int v, int w);

inline void spfa(int s);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    int s = n + 5;
    std::fill(dis, dis + n + 10, 0x3f3f3f3f);

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
    }
    for (int i = 1; i <= n; i++) {
        create(s, i, 0);
    }

    spfa(s);
    for (int i = 1; i <= m; i++) {
        std::cout << node[i] << ' '
                  << dis[node[i].u] + node[i].w - dis[node[i].v] << '\n';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].u = u;
    node[cnt].w = w;
    head[u] = cnt;
}

inline void spfa(int s) {
    std::queue<int> q;
    q.push(s);
    dis[s] = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        vis[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            auto v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w) {
                dis[v] = dis[p] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
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