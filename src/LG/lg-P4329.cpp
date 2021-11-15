#include <cstdio>
#include <iomanip>
#include <iostream>

const int MAX_N = 25;
const int MAX_M = (1 << 20) + 5;

double a[MAX_N][MAX_N];
double dp[MAX_M];

inline int popcount(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = (double)(1.0) * read<int>() / 100.0;
        }
    }
    int m = 1 << n;

    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        int w = popcount(i);
        for (int j = 1; j <= n; j++) {
            dp[i] = std::max(dp[i], dp[i ^ (1 << (j - 1))] * a[w][j]);
        }
    }

    std::cout << std::fixed << std::setprecision(7) << dp[m - 1] * 100.0
              << '\n';

    return 0;
}

inline int popcount(int x) {
    int cnt;
    for (cnt = 0; x; cnt++) {
        x &= x - 1;
    }
    return cnt;
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
