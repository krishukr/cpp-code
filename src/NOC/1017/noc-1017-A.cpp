#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 5050;

ll f[MAX_N][MAX_N], a[MAX_N];

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
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);

    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= n; i++) {
        f[i][0] = 0;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = std::min(f[i - 1][j], f[i - 2][j - 1] + a[i] - a[i - 1]);
        }
    }
    std::cout << f[n][m] << '\n';

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