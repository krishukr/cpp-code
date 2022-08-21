#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1050;
constexpr int MAX_M = 200050;

int f[MAX_N][MAX_N];
int g[MAX_M];
int a[MAX_M];

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
        int x, y;
        read(x, y);
        f[x][y] = i;
    }

    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            g[std::min(f[i][j], f[j][i])]++;
        }
        for (int j = 1; j <= n; j++) {
            if (f[j][i]) {
                const auto v = f[j][i];
                for (int k = 1; k <= (j > i ? i - 1 : n); k++) {
                    f[j][k] = std::max(f[j][k], std::min(v, f[i][k]));
                }
            }
        }
    }

    a[m + 1] = n;
    for (int i = m; i >= 1; i--) {
        a[i] = a[i + 1] + g[i];
    }
    for (int i = 1; i <= m + 1; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';

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