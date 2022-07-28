#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;

int a[MAX_N];
int f[MAX_N][MAX_N];

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
    for (int i = 1; i <= m; i++) {
        read(a[i]);
    }
    a[0] = 0;
    a[m + 1] = n + 1;
    std::sort(a + 1, a + m + 1);

    for (int k = 1; k <= m; k++) {
        for (int i = 1, j = k; j <= m; i++, j++) {
            f[i][j] = 0x3f3f3f3f;
            for (int l = i; l <= j; l++) {
                f[i][j] = std::min(f[i][j], f[i][l - 1] + f[l + 1][j] +
                                                a[j + 1] - a[i - 1] - 2);
            }
        }
    }
    std::cout << f[1][m] << '\n';

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