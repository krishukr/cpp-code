#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 105;

int a[MAX_N], b[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), avg = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        avg += a[i];
    }

    avg /= n;

    for (int i = 1; i <= n; i++) {
        b[i] = b[i - 1] - a[i] + avg;
    }
    std::sort(b + 1, b + n + 1);

    int mid = b[n / 2 + 1], ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += std::abs(b[i] - mid);
    }

    std::cout << ans << '\n';

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