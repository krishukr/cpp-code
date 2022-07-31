#include <algorithm>
#include <bitset>
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

    int c{};
    while (true) {
        int a[10]{}, s{};
        std::bitset<20050> f;
        for (int i = 1; i <= 6; i++) {
            read(a[i]);
            s += a[i] * i;
        }
        if (s == 0) {
            break;
        }
        std::cout << "Collection #" << (++c) << ":\n";

        if (s & 1) {
            std::cout << "Can't be divided.\n\n";
            continue;
        }
        f.set(0);
        [&]() {
            for (int i = 1; i <= 6; i++) {
                for (int j = 1; j <= a[i]; j++) {
                    f |= (f << i);
                    if (f[s / 2]) {
                        std::cout << "Can be divided.\n\n";
                        return;
                    }
                }
            }
            std::cout << "Can't be divided.\n\n";
        }();
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