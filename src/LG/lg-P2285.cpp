#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 10050;

int ti[MAX_N], x[MAX_N], y[MAX_N], dp[MAX_N], res[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), ans = 0;

    for (int i = 1; i <= m; i++) {
        ti[i] = read<int>(), x[i] = read<int>(), y[i] = read<int>();
        dp[i] = 1;
    }

    res[1] = 1;
    for (int i = 2; i <= m; i++) {
        for (int j = i - 1; j > 0; j--) {
            if (res[j] + 1 <= dp[i]) {
                break;
            }

            if (std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]) <=
                ti[i] - ti[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }

            res[i] = std::max(res[i - 1], dp[i]);
            ans = std::max(ans, dp[i]);
        }
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