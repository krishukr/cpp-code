#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;

ll a[MAX_N], s[MAX_N], dp[MAX_N][2];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
    }

    for (int i = 1; i <= n; i++) {
        s[i] = std::abs(a[i] - a[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i][0] = std::max(0ll, dp[i - 1][1] + s[i]);
        dp[i][1] = std::max(0ll, dp[i - 1][0] - s[i]);
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans = std::max(ans, std::max(dp[i][0], dp[i][1]));
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