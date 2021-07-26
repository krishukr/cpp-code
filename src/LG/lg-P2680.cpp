#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 600050;

namespace Star {

struct Node {
    int v;
    int w;
    int nxt;
} node[MAX_N];

int head[MAX_N];
int cnt;

void create(int u, int v, int w);

}  // namespace Star

namespace HLD {

int num[MAX_N], dep[MAX_N], vis[MAX_N];
int idx;

void dfs(int x, int f);

int LCA(int x, int y);

}  // namespace HLD

struct Query {
    int x;
    int y;
    int lca;
    int dis;
} q[MAX_N];

int dis[MAX_N], tmp[MAX_N];
int fa[MAX_N][25], dp[MAX_N][25];

int n, m;

bool check(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    int sum = 0;
    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        Star::create(x, y, z);
        Star::create(y, x, z);
        sum += z;
    }

    HLD::dfs(1, 0);

    for (int i = 1; i <= m; i++) {
        q[i].x = read<int>();
        q[i].y = read<int>();
        q[i].lca = HLD::LCA(q[i].x, q[i].y);
        q[i].dis = dis[q[i].x] + dis[q[i].y] - 2 * dis[q[i].lca];
    }

    int l = 0, r = sum;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    std::cout << l << '\n';

    return 0;
}

namespace Star {

void create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

}  // namespace Star

namespace HLD {

void dfs(int x, int f) {
    using Star::head;
    using Star::node;
    num[++idx] = x;
    dep[x] = dep[f] + 1;
    vis[x] = 1;

    for (int i = 1; i < 25; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (vis[v]) {
            continue;
        }

        fa[v][0] = x;
        dis[v] = dis[x] + node[i].w;
        dfs(v, x);
    }
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) {
        std::swap(x, y);
    }

    int tmp = dep[x] - dep[y];
    for (int i = 0; i < 25; i++) {
        if ((1 << i) & tmp) {
            x = fa[x][i];
        }
    }

    if (x == y) {
        return x;
    }
    for (int i = 24; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

}  // namespace HLD

bool check(int x) {
    int cnt = 0, res = 0;
    memset(tmp, 0, sizeof(tmp));

    for (int i = 1; i <= m; i++) {
        if (q[i].dis > x) {
            tmp[q[i].x]++;
            tmp[q[i].y]++;
            tmp[q[i].lca] -= 2;
            res = std::max(res, q[i].dis - x);
            cnt++;
        }
    }

    if (!cnt) {
        return true;
    }
    for (int i = n; i >= 1; i--) {
        tmp[fa[HLD::num[i]][0]] += tmp[HLD::num[i]];
    }
    for (int i = 2; i <= n; i++) {
        if (tmp[i] == cnt and dis[i] - dis[fa[i][0]] >= res) {
            return true;
        }
    }
    return false;
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