#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 500050;

struct Node {
    int v;
    int nxt;
    ll w;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], q[MAX_N];
int cnt = 1;
ll ans, m;
int n, s, t;

void create(int u, int v, ll w);

bool bfs();

ll dfs(int x, ll flow);

inline ll idx(ll i, ll j);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    s = n * n + 1050, t = n * n + 1051;

    for (int i = 1; i <= n; i++) {
        ll x = read<ll>();
        create(idx(i, i), idx(n, n) + x, 0x3f3f3f3f3f3f3f3f);
        create(idx(n, n) + x, idx(i, i), 0);
        create(idx(i, i), t, x);
        create(t, idx(i, i), 0);
    }
    for (int i = 1; i <= 1000; i++) {
        create(idx(n, n) + i, t, m * i * i);
        create(t, idx(n, n) + i, 0);
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ll x = read<ll>();
            if (x > 0) {
                sum += x;
                create(s, idx(i, j), x);
                create(idx(i, j), s, 0);
            } else {
                create(idx(i, j), t, -x);
                create(t, idx(i, j), 0);
            }

            if (i != j) {
                create(idx(i, j), idx(i + 1, j), 0x3f3f3f3f3f3f3f3f);
                create(idx(i + 1, j), idx(i, j), 0);
                create(idx(i, j), idx(i, j - 1), 0x3f3f3f3f3f3f3f3f);
                create(idx(i, j - 1), idx(i, j), 0);
            }
        }
    }

    while (bfs()) {
        ans += dfs(s, LLONG_MAX);
    }
    std::cout << sum - ans << '\n';

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

ll dfs(int x, ll flow) {
    if (x == t) {
        return flow;
    }
    ll tot = 0;

    for (int i = head[x]; i and flow; i = node[i].nxt) {
        int y = node[i].v;
        if (node[i].w and dep[y] == dep[x] + 1) {
            ll res = dfs(y, std::min(node[i].w, flow));
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

void create(int u, int v, ll w) {
    node[++cnt].v = v;
    node[cnt].w = w;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

inline ll idx(ll i, ll j) { return (i - 1) * n + j; }

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