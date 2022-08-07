#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 2050;
constexpr int MOD = 100003;

ll f[MAX_N][MAX_N], v[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int a, b, c, d, k;
    read(a, b, c, d, k);
    for (int i = 1; i <= c; i++) {
        v[i] = d;
    }
    for (int i = 1; i <= c; i++) {
        f[i][0] = 1;
    }
    for (int i = 1; i <= a; i++) {
        v[i + c] = b + d;
    }
    for (int i = 1; i <= a; i++) {
        f[i + c][0] = 1;
    }
    f[0][0] = 1;

    for (int i = 1; i <= a + c; i++) {
        for (int j = 1; j <= k; j++) {
            f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * (v[i] - j + 1)) % MOD;
        }
    }
    std::cout << f[a + c][k] << '\n';

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