#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 100050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N];

int head[MAX_N], f[MAX_N], dis[MAX_N], c[MAX_N];
bool vis[MAX_N];
int cnt, n, m, b;

void create(int u, int v, int w);

bool spfa(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>(), b = read<int>();
    for (int i = 1; i <= n; i++) {
        f[i] = read<int>();
        c[i] = f[i];
    }

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    if (!spfa(0x3f3f3f3f)) {
        std::cout << "AFK\n";
        return 0;
    }

    std::sort(c + 1, c + n + 1);
    int l = 1, r = n, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (spfa(c[mid])) {
            ans = c[mid];
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

bool spfa(int x) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));

    std::queue<int> q;
    q.push(1);
    dis[1] = 0;

    while (!q.empty()) {
        int p = q.front();
        q.pop();
        vis[p] = false;

        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (dis[v] > dis[p] + w and f[v] <= x) {
                dis[v] = dis[p] + w;

                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }

    if (dis[n] <= b) {
        return true;
    } else {
        return false;
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