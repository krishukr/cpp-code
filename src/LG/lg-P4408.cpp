#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 200050;

struct Node {
    int v;
    int nxt;
    ll w;
} node[MAX_N];

int head[MAX_N];
int cnt, l;

ll dis[MAX_N], dis2[MAX_N], dis3[MAX_N];
ll *d;

void create(int u, int v, ll w);

void dfs(int x, int f);

void dfs2(int x, int f);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>(), z = read<int>();
        create(x, y, z);
        create(y, x, z);
    }

    ll ans1, ans2;
    int s, t;

    dfs(1, 0);
    dis[l] = 0;
    s = l;
    dfs(l, 0);
    t = l;
    ans1 = dis[l];

    d = dis2;
    dfs2(s, 0);
    d = dis3;
    dfs2(t, 0);
    ans2 = 0;

    for (int i = 1; i <= n; i++) {
        ans2 = std::max(ans2, std::min(dis2[i], dis3[i]));
    }

    std::cout << ans1 + ans2 << '\n';

    return 0;
}

void create(int u, int v, ll w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void dfs(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        ll w = node[i].w;
        if (v == f) {
            continue;
        }
        dis[v] = dis[x] + w;
        if (dis[v] > dis[l]) {
            l = v;
        }
        dfs(v, x);
    }
}

void dfs2(int x, int f) {
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        ll w = node[i].w;
        if (v == f) {
            continue;
        }
        d[v] = d[x] + w;
        dfs2(v, x);
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