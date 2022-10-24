#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 305;
constexpr int MOD = 1e9 + 7;

int p[MAX_N];
int w[MAX_N][MAX_N], x[MAX_N][MAX_N];
int f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        read(p[i]);
    }
    for (int i = 1; i < n; i++) {
        w[i][0] = 1;
        for (int j = 1; j <= n - i + 1; j++) {
            if (j == n - i + 1) {
                x[i][j] = w[i][j - 1];
            } else {
                x[i][j] = 1ll * w[i][j - 1] * p[i] % MOD;
            }
            w[i][j] = 1ll * w[i][j - 1] * (1 - p[i] + MOD) % MOD;
        }
        for (int j = 2; j <= n - i + 1; j++) {
            x[i][j] += x[i][j - 1];
            x[i][j] %= MOD;
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        f[1][i] = 1;
        for (int j = 1; j < n; j++) {
            for (int k = 1; k <= i; k++) {
                if (f[j][k]) {
                    f[j + 1][k - 1] += 1ll * f[j][k] * x[j][k - 1] % MOD;
                    f[j + 1][k - 1] %= MOD;
                    f[j + 1][k] += 1ll * f[j][k] * (1 - x[j][k] + MOD) % MOD;
                    f[j + 1][k] %= MOD;
                }
            }
        }
        ans += 1ll * i * f[n][1] % MOD;
        ans %= MOD;
        memset(f, 0, sizeof(f));
    }
    std::cout << ans << '\n';

    return 0;
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