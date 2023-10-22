#include <algorithm>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1005 * 1005;
constexpr int MOD = 998244353;

struct {
    int x;
    int y;
    int a;
} P[MAX_N];
int inv[MAX_N], sx[MAX_N], sy[MAX_N], qx[MAX_N], qy[MAX_N], sf[MAX_N], f[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

#define L(x, y) ((x - 1) * m + y)

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    inv[1] = 1;
    for (int i = 2; i <= n * m; i++) {
        inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            P[L(i, j)] = {i, j, read<int>()};
        }
    }
    std::sort(P + 1, P + n * m + 1,
              [](const auto& x, const auto& y) { return x.a < y.a; });

    for (int i = 1; i <= n * m; i++) {
        qx[i] = (qx[i - 1] + P[i].x * P[i].x) % MOD;
        qy[i] = (qy[i - 1] + P[i].y * P[i].y) % MOD;
        sx[i] = (sx[i - 1] + P[i].x) % MOD;
        sy[i] = (sy[i - 1] + P[i].y) % MOD;
    }

    int bx, by;
    read(bx, by);
    for (int i = 1, j = 0; i <= n * m; i++) {
        if (P[i].a != P[i - 1].a) {
            j = i - 1;
        }
        f[i] = (f[i] + qx[j]) % MOD;
        f[i] = (f[i] + qy[j]) % MOD;
        f[i] = (f[i] - 2ll * sx[j] * P[i].x % MOD + MOD) % MOD;
        f[i] = (f[i] - 2ll * sy[j] * P[i].y % MOD + MOD) % MOD;
        f[i] = (f[i] + 1ll * j * P[i].x * P[i].x % MOD) % MOD;
        f[i] = (f[i] + 1ll * j * P[i].y * P[i].y % MOD) % MOD;
        f[i] = (f[i] + sf[j]) % MOD;
        f[i] = 1ll * f[i] * inv[j] % MOD;
        sf[i] = (sf[i - 1] + f[i]) % MOD;
        if (P[i].x == bx and P[i].y == by) {
            std::cout << f[i] << '\n';
            break;
        }
    }

    std::cout << std::flush;
    return 0;
}

#undef L

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar();
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