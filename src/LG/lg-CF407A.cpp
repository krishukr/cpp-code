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

    int a, b;
    read(a, b);
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= 1000; j++) {
            if (i * i + j * j == a * a) {
                for (int k = 1; k <= 1000; k++) {
                    if (!(k * i % j)) {
                        const auto d = -k * i / j;
                        if (!d or k == i or d == j) {
                            continue;
                        } else if (k * k + d * d == b * b) {
                            std::cout << "YES\n0 0\n";
                            std::cout << i << ' ' << j << '\n'
                                      << k << ' ' << d << '\n';
                            return 0;
                        }
                    }
                }
            }
        }
    }
    std::cout << "NO\n";

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