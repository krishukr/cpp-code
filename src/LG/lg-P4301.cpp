#include <algorithm>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 105;

int a[MAX_N], b[32];

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
    std::sort(a + 1, a + n + 1);

    long long r{};
    for (int i = n, t = a[i]; i >= 1; i--, t = a[i]) {
        for (int j = 30; j >= 0; j--) {
            if ((t >> j) & 1) {
                if (b[j]) {
                    t ^= b[j];
                } else {
                    b[j] = t;
                    break;
                }
            }
        }
        if (t == 0) {
            r += a[i];
        }
    }
    std::cout << r << '\n';

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