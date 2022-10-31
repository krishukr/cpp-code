#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 205;

int a[MAX_N];
int f[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T &t);

template <typename T, typename... Args>
void read(T &t, Args &...rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        a[n + i] = a[i];
    }
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i + l <= n * 2; i++) {
            const int j = i + l;
            for (int k = i + 1; k < j; k++) {
                f[i][j] =
                    std::max(f[i][j], f[i][k] + f[k][j] + a[i] * a[k] * a[j]);
            }
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i][n + i]);
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
void read(T &t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T &t, Args &...rest) {
    t = read<T>();
    read(rest...);
}