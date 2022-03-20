#include <cstdio>
#include <iostream>

constexpr int u[]{6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();
    auto* d = new int[n + 10];

    for (int i = 1; i <= n; i++) {
        d[i] = d[i / 10] + u[i % 10];
    }

    int r = 0;
    int m = n / k - 4 - d[n];
    for (int i = 0, j = n; i <= j; i++, j--) {
        if (d[i] + d[j] == m) {
            r++;
        }
    }
    std::cout << r << '\n';

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