#include <cstdio>
#include <iostream>
#include <memory>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        auto a = std::make_unique<int[]>(n + 50);

        for (int i = n; i >= 1; i--) {
            std::cout << "? 1 " << n << std::endl;
            int x;
            read(x);
            std::cout << "? 2 " << x << std::endl;
            a[x] = i;
        }

        std::cout << "! ";
        for (int i = 1; i <= n; i++) {
            std::cout << a[i] << ' ';
        }
        std::cout << std::endl;
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