#include <cstdio>
#include <iostream>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int a1{0}, a2{0};
    int n, m;
    read(n);
    for (int i = 1; i <= n; i++) {
        a1 = std::max(a1, read<int>());
    }
    read(m);
    for (int i = 1; i <= m; i++) {
        a2 = std::max(a2, read<int>());
    }
    std::cout << a1 << ' ' << a2 << '\n';

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