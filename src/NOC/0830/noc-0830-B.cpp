#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 1000050;

int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, q;
    read(n, q);
    while (q--) {
        int x;
        read(x);
        ll r{};
        for (int i = 1; i <= n; i++) {
            if (x > 0) {
                a[i] = std::min(a[i] + x, i);
            } else {
                a[i] = std::max(a[i] + x, 0);
            }
            r += a[i];
        }
        std::cout << r << '\n';
    }

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