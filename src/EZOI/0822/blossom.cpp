#include <cstdio>
#include <iostream>
#include <set>

typedef long long ll;

const int MAX_N = 1000050;
const ll MOD = 1e9 + 7;

struct Node {
    int v;
    int nxt;
} node[MAX_N];

int head[MAX_N], w[MAX_N];
int cnt;

std::set<int> rq[MAX_N];

void create(int u, int v);

void dfs(int x, int f, int dep, int gf);

template <typename T>
T read();

int main() {
    freopen("blossom.in", "r", stdin);
    freopen("blossom.out", "w", stdout);

    int n = read<int>(), q = read<int>();
    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    for (int i = 1; i < n; i++) {
        int x = read<int>(), y = read<int>();
        create(x, y);
        create(y, x);
    }

    for (int i = 1; i <= n; i++) {
        dfs(i, 0, 0, i);
    }

    for (int i = 1; i <= q; i++) {
        int x = read<int>(), y = read<int>();
        w[x] = y;

        ll res = 0;
        for (auto j : rq[x]) {
            res ^= w[j];
        }
        res %= MOD;

        ans += res * i * i;
        ans %= MOD;
    }

    std::cout << ans << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int x, int f, int dep, int gf) {
    if (dep > 2) {
        return;
    }
    rq[gf].insert(x);

    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == f) {
            continue;
        }

        dfs(v, x, dep + 1, gf);
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