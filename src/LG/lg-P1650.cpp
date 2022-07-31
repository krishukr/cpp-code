#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 2050;

int a[MAX_N], b[MAX_N];
int G[MAX_N][MAX_N];
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
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    std::sort(a + 1, a + n + 1, std::greater<int>{});
    std::sort(b + 1, b + n + 1, std::greater<int>{});

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i] < b[j]) {
                G[i][j] = -200;
            } else if (a[i] > b[j]) {
                G[i][j] = 200;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = (int)0xafafafaf;
        }
    }

    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0] + G[n - i + 1][i];
        f[i][i] = f[i - 1][i - 1] + G[i][i];
        for (int j = 1; j < i; j++) {
            f[i][j] = std::max(f[i - 1][j] + G[n - i + j + 1][i],
                               f[i - 1][j - 1] + G[j][i]);
        }
    }

    int r{};
    for (int i = 1; i <= n; i++) {
        r = std::max(r, f[n][i]);
    }
    std::cout << r << '\n';

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