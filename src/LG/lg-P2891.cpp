#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
    long long w;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], q[MAX_N];
int cnt = 1;
long long ans;
int s, t;

void create(int u, int v, long long w);

bool bfs();

long long dfs(int x, long long flow);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), f = read<int>(), d = read<int>();
    s = 1, t = 2 * n + f + d + 2;

    for (int i = 1; i <= n; i++) {
        int xx = read<int>(), yy = read<int>();

        for (int j = 1; j <= xx; j++) {
            int x = read<int>();
            create(x, i + f, 1);
            create(i + f, x, 0);
        }
        for (int j = 1; j <= yy; j++) {
            int x = read<int>();
            create(i + n + f, 2 * n + f + x, 1);
            create(2 * n + f + x, i + n + f, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        create(i + f, i + f + n, 1);
        create(i + f + n, i + f, 0);
    }
    for (int i = 1; i <= f; i++) {
        create(s, i, 1);
        create(i, s, 0);
    }
    for (int i = 1; i <= d; i++) {
        create(2 * n + f + i, t, 1);
        create(t, 2 * n + f + i, 0);
    }

    while (bfs()) {
        ans += dfs(s, LLONG_MAX);
    }
    std::cout << ans << '\n';

    return 0;
}

bool bfs() {
    memset(dep, 0, sizeof(dep));
    int l, r;
    l = r = 1;
    q[l] = s;
    dep[s] = 1;

    while (l <= r) {
        int u = q[l++];
        for (int i = head[u]; i; i = node[i].nxt) {
            if (node[i].w and !dep[node[i].v]) {
                dep[node[i].v] = dep[u] + 1;
                q[++r] = node[i].v;
            }
        }
    }

    return dep[t];
}

long long dfs(int x, long long flow) {
    if (x == t) {
        return flow;
    }
    long long tot = 0;

    for (int i = head[x]; i and flow; i = node[i].nxt) {
        int y = node[i].v;
        if (node[i].w and dep[y] == dep[x] + 1) {
            long long res = dfs(y, std::min(node[i].w, flow));
            node[i].w -= res;
            node[i ^ 1].w += res;
            flow -= res;
            tot += res;
        }
    }

    if (tot == 0) {
        dep[x] = 0;
    }
    return tot;
}

void create(int u, int v, long long w) {
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