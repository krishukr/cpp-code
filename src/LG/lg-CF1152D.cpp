#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;
constexpr int MOD = 1e9 + 7;

int f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, ans{};
    read(n);

    f[1][1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        for (int j = 1; j <= i; j++) {
            f[i][j] = (f[i - 1][j] + f[i][j - 1]) % MOD;
            if ((i + j) & 1) {
                ans += f[i][j];
                ans %= MOD;
            }
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