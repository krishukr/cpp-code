#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 7150;

int a[MAX_N], q[MAX_N << 1];
ll dp[MAX_N][MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int n = read<int>();
        for (int i = 1; i <= n; i++) {
            std::fill(dp[i], dp[i] + n + 10, 0);
        }

        for (int i = 1; i <= n; i++) {
            a[i] = read<int>();
        }

        for (int r = 2; r <= n; r++) {
            int h = 1, t = 1, m = r;
            q[t] = r;
            dp[r - 1][r] = a[r - 1];

            for (int l = r - 2; l > 0; l--) {
                while (m > l and dp[l][m - 1] > dp[m][r]) {
                    m--;
                }
                dp[l][r] = dp[l][m] + a[m];

                while (h <= t and q[h] >= m) {
                    h++;
                }
                dp[l][r] = std::min(dp[l][r], dp[q[h] + 1][r] + a[q[h]]);
                while (h <= t and
                       dp[q[t] + 1][r] + a[q[t]] >= dp[l + 1][r] + a[l]) {
                    t--;
                }
                q[++t] = l;
            }
        }

        std::cout << dp[1][n] << '\n';
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