#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 2050;

struct I {
    int a;
    int b;
} a[MAX_N];

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
        read(a[i].a, a[i].b);
    }
    std::sort(a + 1, a + n + 1, [](const I& x, const I& y) {
        return x.a == y.a ? x.b > y.b : x.a > y.a;
    });

    memset(f, 0xaf, sizeof(f));
    f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i][j] = std::max(f[i - 1][j],
                               f[i - 1][std::max(1, j - a[i].a + 1)] + a[i].b);
        }
    }
    int ans = 0xafafafaf;
    for (int i = 0; i <= n; i++) {
        ans = std::max(ans, f[n][i]);
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