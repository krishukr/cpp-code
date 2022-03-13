#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 2050;

ll dp[MAX_N][MAX_N];
ll frac[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), P = read<int>();
    frac[0] = 1;
    for (int i = 1; i <= n; i++) {
        frac[i] = frac[i - 1] * i % P;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] =
                (dp[i - 1][j - 1] * j % P + dp[i - 1][j] * (i - j - 1) % P) % P;
        }
        dp[i][1] += frac[i];
        dp[1][1] %= P;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dp[n][i] * i % P * (n - i) % P;
        ans %= P;
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