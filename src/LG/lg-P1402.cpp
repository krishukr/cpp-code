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

    int n = read<int>(), p = read<int>(), q = read<int>();
    s = 2 * n + p + q + 1, t = 2 * n + p + q + 2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            int x = read<int>();
            if (x) {
                create(j, p + i, 1);
                create(p + i, j, 0);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= q; j++) {
            int x = read<int>();
            if (x) {
                create(p + n + q + i, p + n + j, 1);
                create(p + n + j, p + n + q + i, 0);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        create(p + i, p + n + q + i, 1);
        create(p + n + p + q, p + i, 0);
    }
    for (int i = 1; i <= p; i++) {
        create(s, i, 1);
        create(i, s, 0);
    }
    for (int i = 1; i <= q; i++) {
        create(n + p + i, t, 1);
        create(t, n + p + i, 0);
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