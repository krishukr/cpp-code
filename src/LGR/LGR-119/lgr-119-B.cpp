#include <cassert>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;

int a[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, c{};
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            c++;
        }
    }
    if (c) {
        for (int i = 1; i <= n; i++) {
            if (a[i] == 2) {
                c++;
                break;
            }
            if (a[i] == 1) {
                break;
            }
        }
        for (int i = n; i >= 1; i--) {
            if (a[i] == 3) {
                c++;
                break;
            }
            if (a[i] == 1) {
                break;
            }
        }
    } else {
        std::cout << 1 << '\n';
        return 0;
    }
    std::cout << c << '\n';

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