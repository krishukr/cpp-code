#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 405;

int c[MAX_N << 1][MAX_N], f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(c[j][i]);
        }
    }

    int ans{};
    for (int i = 1; i < m; i++) {
        // memset(f, 0, sizeof(f));
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                f[j][k] = f[j - 1][k - 1] + (int)(c[i][j] != c[i + 1][k]);
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                f[j][k] += std::min(f[j - 1][k], f[j][k - 1]);
            }
        }
        ans += f[n][n];
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