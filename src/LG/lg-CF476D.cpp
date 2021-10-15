#include <cstdio>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    std::cout << (6 * n - 1) * k << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << (6 * i + 1) * k << ' ' << (6 * i + 2) * k << ' '
                  << (6 * i + 3) * k << ' ' << (6 * i + 5) * k << '\n';
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
};