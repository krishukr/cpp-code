#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

const int MAX_N = 1050;
const int MAX_M = 10050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_M], revn[MAX_M];

int cnt, ret;
int head[MAX_N], revd[MAX_N];

int dis[MAX_N];
bool vis[MAX_N];

int n, m, k;

void create(int u, int v, int w);

void spfa();

void astar();

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>(), k = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
    }

    spfa();
    astar();

    while (k--) {
        std::cout << -1 << '\n';
    }

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;

    revn[++ret].v = u;
    revn[ret].nxt = revd[v];
    revn[ret].w = w;
    revd[v] = ret;
}

void spfa() {
    std::queue<int> q;
    q.push(1);
    std::fill(dis + 2, dis + n + 1, 0x3f3f3f3f);
    auto& head = revd;
    auto& node = revn;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;

        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (dis[v] > dis[x] + w) {
                dis[v] = dis[x] + w;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

void astar() {
    struct P {
        int x;
        int l;

        bool operator<(const P& a) const { return l + dis[x] > a.l + dis[a.x]; }
    };
    std::priority_queue<P> q;
    q.push({n, 0});

    while (!q.empty()) {
        const auto& p = q.top();
        auto x = p.x, l = p.l;
        q.pop();

        if (x == 1) {
            std::cout << l << '\n';
            if (!(--k)) {
                return;
            }
        }

        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            q.push({v, l + w});
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