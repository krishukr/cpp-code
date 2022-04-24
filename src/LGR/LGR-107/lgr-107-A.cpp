#include <algorithm>
#include <cstdio>
#include <iostream>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

bool get();

int main() {
    std::ios::sync_with_stdio(false);

    int n, s1{0}, s2{0};
    read(n);
    for (int i = 1; i <= n; i++) {
        s1 += get();
    }
    for (int i = 1; i <= n; i++) {
        s2 += get();
    }

    std::cout << std::abs(s2 - s1) << '\n';

    return 0;
}

bool get() {
    char ch = getchar();
    while (ch != '0' and ch != '1') {
        ch = getchar();
    }
    return ch == '1';
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