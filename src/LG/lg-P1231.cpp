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

    int n1 = read<int>(), n2 = read<int>(), n3 = read<int>();
    int m1 = read<int>();

    for (int i = 1; i <= m1; i++) {
        int x = read<int>(), y = read<int>();
        create(y, n2 + x, 1);
        create(n2 + x, y, 0);
    }

    int m2 = read<int>();
    for (int i = 1; i <= m2; i++) {
        int x = read<int>(), y = read<int>();
        create(n1 + n2 + x, 2 * n1 + n2 + y, 1);
        create(2 * n1 + n2 + y, n1 + n2 + x, 0);
    }

    s = 1, t = 2 * n1 + n2 + n3 + 1;

    for (int i = 1; i <= n1; i++) {
        create(n2 + i, n1 + n2 + i, 1);
        create(n1 + n2 + i, n2 + i, 0);
    }
    for (int i = 1; i <= n2; i++) {
        create(1, i, 1);
        create(i, 1, 0);
    }
    for (int i = 1; i <= n3; i++) {
        create(2 * n1 + n2 + i, t, 1);
        create(t, 2 * n1 + n2 + i, 0);
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