#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 35;
constexpr int MAX_M = 905;

int a[MAX_N];
int f[MAX_M];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, s{};
    read(n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        read(x, y);
        a[i] = std::abs(x - y);
        s += a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = (s >> 1); j >= a[i]; j--) {
            f[j] = std::max(f[j], f[j - a[i]] + a[i]);
        }
    }
    std::cout << s - f[(s >> 1)] * 2 << '\n';

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