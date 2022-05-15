#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;
constexpr int MAX_K = 15;
constexpr ll MOD = 1e9 + 7;

struct Node {
    int v;
    int nxt;
} node[MAX_N << 1];

int head[MAX_N];
int cnt;

void create(int u, int v);

ll f[MAX_K][MAX_N], g[MAX_K][MAX_N];
ll aa[MAX_K][MAX_N], am[MAX_K][MAX_N];

template <typename T>
T quick_pow(T a, T b);

void dfs1(int x, int fa);

void dfs2(int x, int fa);

int n, K;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, K);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        create(x, y);
        create(y, x);
    }

    dfs1(1, 0);
    for (int i = 1; i <= K; i++) {
        aa[i][1] = f[i][1];
        am[i][1] = g[i][1];
    }
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) {
        std::cout << aa[K][i] << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << am[K][i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void create(int u, int v) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    head[u] = cnt;
}

template <typename T>
T quick_pow(T a, T b) {
    T r{1};
    while (b) {
        if (b & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

void dfs1(int x, int fa) {
    for (int i = 0; i <= K; i++) {
        f[i][x] = g[i][x] = 1;
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
        dfs1(v, x);
        for (int j = 1; j <= K; j++) {
            f[j][x] += f[j - 1][v];
            f[j][x] %= MOD;
            g[j][x] *= g[j - 1][v];
            g[j][x] %= MOD;
        }
    }
    for (int i = 1; i <= K; i++) {
        g[i][x] *= f[i][x];
        g[i][x] %= MOD;
    }
}

void dfs2(int x, int fa) {
    if (x != 1) {
        aa[0][x] = am[0][x] = 1;
        aa[1][x] = am[1][x] = f[1][x] + f[0][fa];
        for (int i = 2; i <= K; i++) {
            aa[i][x] = (aa[i - 1][fa] + f[i][x] - f[i - 2][x]) % MOD;
            am[i][x] = am[i - 1][fa] *
                       quick_pow(aa[i - 1][fa] * g[i - 2][x], MOD - 2) % MOD *
                       g[i][x] % MOD * quick_pow(f[i][x], MOD - 2) % MOD *
                       aa[i][x] % MOD * (aa[i - 1][fa] - f[i - 2][x] + MOD) %
                       MOD;
        }
    }
    for (int i = head[x]; i; i = node[i].nxt) {
        int v = node[i].v;
        if (v == fa) {
            continue;
        }
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}