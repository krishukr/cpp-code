#include <cstdio>
#include <iostream>

using ll = long long;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, a, b;
    read(n, a, b);
    for (int i = 1; i <= n + 1; i++) {
        if (1ll * i * (n + 1 - i) == b) {
            for (int j = 1; j < i; j++) {
                std::cout << 0 << ' ';
            }
            if (n + 1 - i > 0) {
                std::cout << 1 << ' ';
            }
            for (int j = 2; j <= (n + 1 - i); j++) {
                std::cout << 0 << ' ';
            }
            std::cout << '\n';
            return 0;
        }
    }
    std::cout << -1 << '\n';

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