#include <cstdio>
#include <iostream>

const int MAX_N = 105;

int x[MAX_N], y[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        x[i] = read<int>();
        y[i] = read<int>();
    }

    int sum = (x[n] * y[1] - y[n] * x[1]);
    for (int i = 1; i < n; i++) {
        sum += (x[i] * y[i + 1] - y[i] * x[i + 1]);
    }
    std::cout << std::abs(sum) / 2 << '\n';

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