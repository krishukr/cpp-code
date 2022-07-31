#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 205;
constexpr int MOD = 1e8;

int f[2][MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    f[1][0][0] = f[0][0][0] = 1;
    int n1, n2, k1, k2;
    read(n1, n2, k1, k2);
    for (int i = 1; i <= n1 + n2; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 1; k <= k2 and i - k >= j; k++) {
                f[1][i][j] += f[0][i - k][j];
                f[1][i][j] %= MOD;
            }
            for (int k = 1; k <= std::min(k1, std::max(i, j)); k++) {
                f[0][i][j] += f[1][i - k][j - k];
                f[0][i][j] %= MOD;
            }
        }
    }
    std::cout << ((f[0][n1 + n2][n1] + f[1][n1 + n2][n1]) % MOD) << '\n';

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