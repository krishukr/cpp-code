#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 300050;
constexpr int MOD = 1e9 + 7;

ll fra[MAX_N], inv[MAX_N], ina[MAX_N];
int fa[MAX_N], sz[MAX_N];
ll dp[MAX_N];

ll comb(ll a, ll b);

int find(int x);

void merge(int x, int y);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, q;
    read(n, q);

    fra[0] = inv[1] = ina[0] = 1;
    for (int i = 1; i <= n; i++) {
        fra[i] = fra[i - 1] * i % MOD;
    }
    for (int i = 2; i <= n; i++) {
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    for (int i = 1; i <= n; i++) {
        ina[i] = ina[i - 1] * inv[i] % MOD;
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = sz[i] = 1;
    }

    int la{};
    while (q--) {
        int op;
        read(op);
        if (op == 1) {
            int x, y;
            read(x, y);
            x = (x + la) % n + 1;
            y = (y + la) % n + 1;
            merge(x, y);
        } else if (op == 2) {
            int x;
            read(x);
            x = (x + la) % n + 1;
            la = dp[find(x)];
            std::cout << la << '\n';
        }
    }

    return 0;
}

ll comb(ll a, ll b) { return fra[a] * ina[b] % MOD * ina[a - b] % MOD; }

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    sz[y] += sz[x];
    dp[y] = dp[y] * dp[x] % MOD * comb(sz[y] - 1, sz[x]) % MOD;
    fa[x] = y;
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