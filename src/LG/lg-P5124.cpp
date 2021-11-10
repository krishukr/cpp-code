#include <cstdio>
#include <iostream>

const int MAX_N = 10050;

int a[MAX_N], dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), k = read<int>();

    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        int m = 0;
        for (int j = i; i - j + 1 <= k and j > 0; j--) {
            m = std::max(m, a[j]);
            dp[i] = std::max(dp[i], dp[j - 1] + m * (i - j + 1));
        }
    }

    std::cout << dp[n] << '\n';

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