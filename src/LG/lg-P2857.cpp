#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 50050;

struct Node {
    int v;
    int nxt;
    ll w;
} node[MAX_N];

int head[MAX_N], dep[MAX_N], q[MAX_N], dp[1050][1050], v[MAX_N];
int cnt = 1;
int n, m, s, t, b;

void create(int u, int v, ll w);

bool bfs();

ll dfs(int x, ll flow);

ll flow(int x, int y);

bool check(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), b = read<int>();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= b; j++) {
            dp[i][j] = read<int>();
        }
    }

    for (int i = 1; i <= b; i++) {
        v[i] = read<int>();
    }

    int l = 1, r = b, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
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

ll flow(int x, int y) {
    s = x, t = y;
    ll res = 0;
    while (bfs()) {
        res += dfs(s, LLONG_MAX);
    }
    return res;
}

bool check(int x) {
    for (int i = 1; i + x - 1 <= b; i++) {
        cnt = 1;
        memset(head, 0, sizeof(head));

        int xt = 0, yt = n + b + 1;
        for (int j = 1; j <= n; j++) {
            create(xt, j, 1);
            create(j, xt, 0);
        }

        for (int j = 1; j <= b; j++) {
            create(j + n, yt, v[j]);
            create(yt, j + n, 0);
        }

        for (int j = 1; j <= n; j++) {
            for (int k = i; k <= i + x - 1; k++) {
                create(j, dp[j][k] + n, 1);
                create(dp[j][k] + n, j, 0);
            }
        }

        if (flow(xt, yt) == n) {
            return true;
        }
    }
    return false;
}

void create(int u, int v, ll w) {
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