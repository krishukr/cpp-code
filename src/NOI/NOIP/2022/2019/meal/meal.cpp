#include <cstdio>
#include <cstring>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 105;
constexpr int MAX_M = 2050;
constexpr int MOD = 998244353;

ll s[MAX_N];
ll p[MAX_N][MAX_M], f[MAX_N][MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("meal.in", "r", stdin);
    freopen("meal.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    ll ans{1};
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(p[i][j]);
            s[i] += p[i][j];
            s[i] %= MOD;
        }
        ans *= s[i] + 1;
        ans %= MOD;
    }
    ans = (ans - 1 + MOD) % MOD;

    for (int i = 1; i <= m; i++) {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= j + j - 2; k++) {
                f[j][k] += f[j - 1][k] * (s[j] - p[j][i]) % MOD;
                f[j][k] %= MOD;
                f[j][k + 1] += f[j - 1][k];
                f[j][k + 1] %= MOD;
                f[j][k + 2] += f[j - 1][k] * p[j][i] % MOD;
                f[j][k + 2] %= MOD;
            }
        }
        for (int j = n + 1; j <= n + n; j++) {
            ans = (ans - f[n][j] + MOD) % MOD;
        }
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
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