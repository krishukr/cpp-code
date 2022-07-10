#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5050;

int s[MAX_N], f[MAX_N], g[MAX_N];

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
        s[i] = s[i - 1] + read<int>();
    }
    std::fill(f + 1, f + n + 5, 0x3f3f3f3f);
    std::fill(g + 1, g + n + 5, 0x3f3f3f3f);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (g[j] <= s[i] - s[j] and f[j] + i - j - 1 <= f[i]) {
                f[i] = f[j] + i - j - 1;
                g[i] = std::min(g[i], s[i] - s[j]);
            }
        }
    }
    std::cout << f[n] << '\n';

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