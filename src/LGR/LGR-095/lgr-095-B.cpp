#include <cstdio>
#include <iostream>

const int MAX_N = 2000050;

int r[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), d = read<int>();
    if ((d / 2) > (n / 2) or d < (n / 2)) {
        std::cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            r[n / 2 + i / 2] = i;
        } else {
            r[i / 2 - 1] = i;
        }
    }

    for (int i = n / 2; i < n; i++) {
        std::cout << r[i] << ' ';
    }
    for (int i = 0; i < n / 2; i++) {
        std::cout << r[i] << ' ';
    }
    for (int i = 0; i < n / 2; i++) {
        std::cout << r[i] << ' ';
    }
    for (int i = n / 2; i < n; i++) {
        std::cout << r[i] << ' ';
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