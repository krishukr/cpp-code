#include <algorithm>
#include <bitset>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 25050;

int h[MAX_N];
std::bitset<MAX_N> f, t;

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
        read(h[i]);
    }
    std::sort(h + 1, h + n + 1);

    f[0] = true;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            t |= (f << (h[j] - h[i]));
        }
        f |= t;
    }

    for (int i = 0; i <= MAX_N - 50; i++) {
        if (f[i]) {
            std::cout << i << ' ';
        }
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