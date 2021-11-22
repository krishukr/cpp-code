#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int x = read<int>(), y = read<int>();
        if ((x + y) & 1) {
            std::cout << "-1 -1\n";
            continue;
        }
        if (!(x & 1) and !(y & 1)) {
            std::cout << x / 2 << ' ' << y / 2 << '\n';
            continue;
        }

        if (x > y) {
            std::cout << (x + y) / 2 - y << ' ' << y << '\n';
        } else {
            std::cout << x << ' ' << (x + y) / 2 - x << '\n';
        }
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