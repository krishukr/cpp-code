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

    int n, m;
    read(n, m);
    if (m > n * 2 + 2 or n > m + 1) {
        std::cout << "-1" << '\n';
    } else {
        while (n or m) {
            if (m == n - 1) {
                std::cout << '0';
                n--;
            }
            if (m - 2 <= n * 2 and m - 2 >= 0 and n - 1 >= 0 and m - 1 > n) {
                std::cout << "110";
                m -= 2;
                n--;
            } else if (m >= n - 1 and m - 1 >= 0 and n - 1 >= 0) {
                std::cout << "10";
                m--;
                n--;
            } else if (m - 1 >= 0) {
                std::cout << '1';
                m--;
            } else if (n - 1 >= 0) {
                std::cout << '0';
                n--;
            }
        }
        std::cout << '\n';
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