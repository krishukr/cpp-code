#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 1e9 + 7;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N << 1], ind[MAX_N];
int cnt, s, t;
bool vis[MAX_N];

ll g[MAX_N];
ll sum = 1;

void create(int u, int v);

void dfs(int x);

ll quick_pow(ll a, ll b);

inline ll inv(ll a);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    s = read<int>(), t = read<int>();
    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        create(y, x);
        ind[y]++;
    }
    ind[1]++;

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        if (i == t) {
            ans *= (ind[i] + 1);
        } else {
            ans *= ind[i];
        }
        ans %= MOD;

        sum *= ind[i];
        sum %= MOD;
    }

    dfs(s);
    ans = (ans - g[s] + MOD) % MOD;
    std::cout << ans << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x) {
    if (vis[x]) {
        return;
    }
    vis[x] = true;

    if (x == t) {
        g[x] = 1ll * sum * inv(ind[x]);
        g[x] %= MOD;
        return;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        dfs(v);
        g[x] += g[v];
        g[x] %= MOD;
    }
    g[x] *= inv(ind[x]);
    g[x] %= MOD;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll a) { return quick_pow(a, MOD - 2); }

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