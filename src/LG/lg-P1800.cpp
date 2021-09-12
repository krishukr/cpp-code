#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 105;

int dp[MAX_N][MAX_N];
int d1[MAX_N], d2[MAX_N];

int n, m;

bool check(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        d1[i] = read<int>();
        d2[i] = read<int>();
    }

    int l = 1, r = 100000;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    std::cout << l << '\n';

    return 0;
}

bool check(int x) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    int res;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = j; k >= 0; k--) {
                res = x - d1[i] * (j - k);
                if (res < 0) {
                    break;
                }
                if (dp[i - 1][k]) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][k] + res / d2[i]);
                }
            }
        }
    }
    return dp[n][m] > m;
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