#include <bits/stdc++.h>

using ll = long long;

constexpr ll MOD = 998244353;
constexpr int MAX_N = 35;
constexpr int MAX_M = 105;

ll C[MAX_N][MAX_N];
ll v[MAX_M], P[MAX_M][MAX_N];
ll f[MAX_M][MAX_N][MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    for (int i = 0; i <= 30; i++) {
        C[i][0] = 1;
    }
    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }

    int N, M, K;
    read(N, M, K);
    for (int i = 0; i <= M; i++) {
        read(v[i]);
        P[i][0] = 1;
        for (int j = 1; j <= N; j++) {
            P[i][j] = P[i][j - 1] * v[i] % MOD;
        }
    }

    f[0][0][0][0] = 1;
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= K; k++) {
                for (int l = 0; l <= (N >> 1); l++) {
                    for (int o = 0; o <= N - j; o++) {
                        f[i + 1][j + o][k + ((o + l) & 1)][(o + l) >> 1] +=
                            f[i][j][k][l] * P[i][o] % MOD * C[N - j][o] % MOD;
                        f[i + 1][j + o][k + ((o + l) & 1)][(o + l) >> 1] %= MOD;
                    }
                }
            }
        }
    }

    ll ans{};
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= (N >> 1); j++) {
            if (i + __builtin_popcount(j) <= K) {
                ans += f[M + 1][N][i][j];
                ans %= MOD;
            }
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