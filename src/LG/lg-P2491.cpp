#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>

const int MAX_N = 300050;

struct Node {
    int v;
    int nxt;
    int w;
} node[MAX_N << 1];

int head[MAX_N << 1];
int cnt, l, r;

int dis[MAX_N], pre[MAX_N];
bool vis[MAX_N];

void create(int u, int v, int w);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), s = read<int>();
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    std::function<void(int, int)> dfs;
    dfs = [&](int x, int f) -> void {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (v == f) {
                continue;
            }
            dis[v] = dis[x] + w;
            if (dis[l] < dis[v]) {
                l = v;
            }
            dfs(v, x);
        }
    };
    dfs(1, 0);
    dis[l] = 0;

    dfs = [&](int x, int f) -> void {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (v == f) {
                continue;
            }
            dis[v] = dis[x] + w;
            pre[v] = x;
            if (dis[r] < dis[v]) {
                r = v;
            }
            dfs(v, x);
        }
    };
    dfs(l, 0);
    std::fill(dis, dis + n + 1, 0);

    int i = r;
    vis[i] = true;
    while (i != l) {
        for (int j = head[i]; j; j = node[j].nxt) {
            int v = node[j].v, w = node[j].w;
            if (v == pre[i]) {
                vis[v] = true;
                dis[v] = dis[i] + w;
            }
        }
        i = pre[i];
    }
    i = r;

    std::function<int(int, int)> find;
    find = [&](int x, int len) -> int {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (v == pre[x] and len >= w) {
                return find(v, len - w);
            }
        }
        return x;
    };

    int ans = 0x3f3f3f3f;
    std::function<int(int, int)> work;
    work = [&](int x, int len) -> int {
        int p = find(x, len);
        return std::max(dis[x], dis[l] - dis[p]);
    };

    while (i != l) {
        ans = std::min(ans, work(i, s));
        i = pre[i];
    }
    i = r;
    ans = std::min(ans, work(l, s));
    std::fill(dis, dis + n + 1, 0);

    dfs = [&](int x, int f) -> void {
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v, w = node[i].w;
            if (vis[v] or v == f) {
                continue;
            }

            dis[v] = dis[x] + w;
            dfs(v, x);
        }
    };

    while (i != l) {
        dfs(i, 0);
        i = pre[i];
    }
    i = r;
    dfs(l, 0);

    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, dis[i]);
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