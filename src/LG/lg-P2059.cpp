#include <cstdio>
#include <iomanip>
#include <iostream>

constexpr int MAX_N = 55;

int a[MAX_N];
double f[MAX_N][MAX_N];

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
    f[1][1] = 1;

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            auto t = (a[j] - 1) % i + 1;
            for (int k = 1; k < i; k++) {
                t = t % i + 1;
                f[i][t] += 1.0 * f[i - 1][k] / m;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << std::fixed << std::setprecision(2) << f[n][i] * 100.0
                  << "% ";
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