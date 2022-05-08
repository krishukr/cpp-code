#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>

using ll = long long;

constexpr ll INF = LLONG_MAX >> 4;
constexpr int MAX_N = 10050;

int a[MAX_N], b[MAX_N];
ll dp[2][MAX_N * 600];

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
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i < n; i++) {
        b[i] = a[i + 1] - a[i];
    }
    std::sort(b + 1, b + n);

    ll s = 0;
    for (int i = 1; i < n; i++) {
        s += b[i] * i;
    }
    for (int i = 1; i <= s; i++) {
        dp[0][i] = INF;
    }

    int crt{0}, idx{0};
    for (int i = 1; i < n; i++) {
        if (!b[i]) {
            continue;
        }
        idx ^= 1;
        crt += b[i];

        for (int j = 0; j <= s; j++) {
            dp[idx][j] = INF;
            {
                const int k = j - i * b[i];
                if (k >= 0) {
                    dp[idx][j] = std::min(
                        dp[idx][j], dp[idx ^ 1][k] + 1ll * i * b[i] * b[i] +
                                        2ll * k * b[i]);
                }
            }
            {
                const int k = j - crt;
                if (k >= 0) {
                    dp[idx][j] =
                        std::min(dp[idx][j], dp[idx ^ 1][k] + 1ll * crt * crt);
                }
            }
        }
    }

    ll ans{INF};
    for (int i = 0; i <= s; i++) {
        if (dp[idx][i] != INF) {
            ans = std::min(ans, 1ll * n * dp[idx][i] - 1ll * i * i);
        }
    }
    std::cout << ans << '\n';

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