#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 250;
const int MOD = 1000000007;

int dp[MAX_N][MAX_N] = {1}, s[MAX_N][MAX_N];

template <typename T>
T read();

signed main() {
    // std::ios::sync_with_stdio(false);

    std::string a, b;
    int n = read<int>(), m = read<int>(), kk = read<int>();
    std::cin >> a >> b;

    for (int i = 1; i <= n; i++) {
        for (int j = m; j > 0; j--) {
            for (int k = kk; k > 0; k--) {
                if (a[i - 1] == b[j - 1]) {
                    s[j][k] = s[j - 1][k] + dp[j - 1][k - 1];
                    dp[j][k] += s[j][k];
                    dp[j][k] %= MOD;
                } else {
                    s[j][k] = 0;
                }
            }
        }
    }

    std::cout << dp[m][kk] << '\n';

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