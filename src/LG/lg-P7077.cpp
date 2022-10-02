#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_M = 1000050;
constexpr ll MOD = 998244353;

ll a[MAX_N];
int p[MAX_N], typ[MAX_N];
ll v[MAX_N];
ll mul[MAX_N], sum[MAX_N];

struct {
    int v;
    int nxt;
} node[MAX_M];

int head[MAX_N];
int cnt;

void create(int u, int v);

int ind[MAX_N], dfn[MAX_N];
int idx;

void topos();

int f[MAX_N];
int n, m;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    read(m);
    for (int i = 1; i <= m; i++) {
        read(typ[i]);
        if (typ[i] == 1) {
            read(p[i], v[i]);
            mul[i] = 1;
        } else if (typ[i] == 2) {
            read(v[i]);
            mul[i] = v[i];
        } else if (typ[i] == 3) {
            read(p[i]);
            mul[i] = 1;
            for (int j = 1; j <= p[i]; j++) {
                int x;
                read(x);
                create(i, x);
                ind[x]++;
            }
        }
    }
    topos();

    for (int j = m; j >= 1; j--) {
        const auto& x = dfn[j];
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            mul[x] *= mul[v];
            mul[x] %= MOD;
        }
    }
    {
        int q;
        read(q);
        for (int i = 1; i <= q; i++) {
            read(f[i]);
        }
        ll t{1};
        for (int j = q; j >= 1; j--) {
            const auto& x = f[j];
            sum[x] += t;
            sum[x] %= MOD;
            t *= mul[x];
            t %= MOD;
        }
        for (int i = 1; i <= n; i++) {
            a[i] *= t;
            a[i] %= MOD;
        }
    }
    for (int j = 1; j <= m; j++) {
        const auto& x = dfn[j];
        ll t{1};
        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            sum[v] += sum[x] * t % MOD;
            sum[v] %= MOD;
            t *= mul[v];
            t %= MOD;
        }
    }

    for (int i = 1; i <= m; i++) {
        if (typ[i] == 1) {
            a[p[i]] += v[i] * sum[i] % MOD;
            a[p[i]] %= MOD;
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

void topos() {
    std::queue<int> q;
    for (int i = 1; i <= m; i++) {
        if (!ind[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        const auto p = q.front();
        q.pop();
        dfn[++idx] = p;
        for (int i = head[p]; i; i = node[i].nxt) {
            int v = node[i].v;
            ind[v]--;
            if (!ind[v]) {
                q.push(v);
            }
        }
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
    }
    return x * f;
}

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}