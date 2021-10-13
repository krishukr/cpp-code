#include <cstdio>
#include <iostream>

const int MAX_N = 2050;

int w[MAX_N], dp[MAX_N], r[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        w[i] = read<int>();
    }

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            dp[j] += dp[j - w[i]];
            dp[j] %= 10;
        }
    }

    for (int i = 1; i <= n; i++) {
        r[0] = 1;
        for (int j = 1; j <= m; j++) {
            if (w[i] > j) {
                r[j] = dp[j];
            } else {
                r[j] = (dp[j] - r[j - w[i]] + 10) % 10;
            }
            std::cout << r[j];
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