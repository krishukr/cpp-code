#include <cstdio>
#include <iomanip>
#include <iostream>

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    long long n = read<long long>();
    std::cout << std::fixed << std::setprecision(10)
              << (double)(1.0) * n * (n + 1) / (2 * (2 * n - 1));

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