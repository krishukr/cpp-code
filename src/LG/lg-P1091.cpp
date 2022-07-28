#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;

int a[MAX_N];
int f[MAX_N], g[MAX_N];

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
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
    }
    for (int i = n; i > 0; i--) {
        for (int j = n + 1; j > i; j--) {
            if (a[i] > a[j]) {
                g[i] = std::max(g[i], g[j] + 1);
            }
        }
    }

    int ans{};
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, f[i] + g[i] - 1);
    }
    std::cout << n - ans << '\n';

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