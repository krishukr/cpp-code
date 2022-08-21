#include <bitset>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 25;

int a[MAX_N];

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
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    int r{};
    for (int i = 0; i < (1 << n); i++) {
        if (__builtin_popcount(i) == n - m) {
            std::bitset<10000> f;
            f[0] = true;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    f |= f << a[j];
                }
            }
            r = std::max(r, (int)(f.count()));
        }
    }
    std::cout << r - 1 << '\n';

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