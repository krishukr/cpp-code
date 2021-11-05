#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 50050;

struct Node {
    int v;
    int nxt;
    int w;
    int c;
} node[MAX_N];

int head[MAX_N];
int cnt = 1;

int dis[MAX_N], flw[MAX_N], pre[MAX_N];
bool vis[MAX_N];
int s, t;

void create(int u, int v, int w, int c);

bool spfa();

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    s = 0, t = 2 * n + 1;

    int t1 = read<int>(), t2 = read<int>(), p = read<int>(), c1 = read<int>(),
        c2 = read<int>();
    t1++, t2++;

    for (int i = 1; i <= n; i++) {
        create(s, i + n, 0x3f3f3f3f, p);
        create(i + n, s, 0, -p);

        if (i + 1 <= n) {
            create(i, i + 1, 0x3f3f3f3f, 0);
            create(i + 1, i, 0, 0);
        }
        if (i + t1 <= n) {
            create(i, i + n + t1, 0x3f3f3f3f, c1);
            create(i + n + t1, i, 0, c1);
        }
        if (i + t2 <= n) {
            create(i, i + n + t2, 0x3f3f3f3f, c2);
            create(i + n + t2, i, 0, -c2);
        }
    }

    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        create(s, i, x, 0);
        create(i, s, 0, 0);
        create(i + n, t, x, 0);
        create(t, i + n, 0, 0);
    }

    long long c = 0;
    while (spfa()) {
        int x = t;
        c += dis[x] * flw[x];

        for (int i; x != s; x = node[i ^ 1].v) {
            i = pre[x];
            node[i].w -= flw[t];
            node[i ^ 1].w += flw[t];
        }
    }

    std::cout << c << '\n';

    return 0;
}

void create(int u, int v, int w, int c) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    node[cnt].c = c;
    head[u] = cnt;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    std::queue<int> q;
    q.push(s);
    vis[s] = true;
    dis[s] = 0;
    flw[s] = INT_MAX;

    while (!q.empty()) {
        int h = q.front();
        q.pop();
        vis[h] = false;

        for (int i = head[h]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (!node[i].w) {
                continue;
            }

            if (dis[v] > dis[h] + node[i].c) {
                dis[v] = dis[h] + node[i].c;
                flw[v] = std::min(flw[h], node[i].w);
                pre[v] = i;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }

    return dis[t] != 0x3f3f3f3f;
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