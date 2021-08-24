#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 200050;

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1], dis[MAX_N];
bool vis[MAX_N];
int cnt;

void create(int u, int v, int w);

void spfa(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int c = read<int>(), p = read<int>(), u = read<int>(), v1 = read<int>(),
        v2 = read<int>();

    for (int i = 1; i <= c; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    int res = 0;
    spfa(u);
    res = std::min(dis[v1], dis[v2]);
    spfa(v1);

    std::cout << res + dis[v2] << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void spfa(int x) {
    std::deque<int> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    dis[x] = 0;
    q.push_front(x);

    while (!q.empty()) {
        int l = q.front();
        q.pop_front();
        vis[l] = false;

        for (int i = head[l]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (w < dis[v] - dis[l]) {
                dis[v] = dis[l] + w;
                if (vis[v]) {
                    continue;
                }

                if (q.size() and dis[v] < dis[q.front()]) {
                    q.push_front(v);
                } else {
                    q.push_back(v);
                }
                vis[v] = true;
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