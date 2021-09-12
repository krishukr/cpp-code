#include <cstdio>
#include <iostream>

const int MAX_N = 55;

int dp[MAX_N][MAX_N][MAX_N][MAX_N];
int n, ans;

template <typename T>
T read();

class M {
   public:
    int mp[MAX_N][MAX_N];

    void in() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                mp[i][j] = read<int>();
            }
        }
    }
} a, b;

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>();
    a.in(), b.in();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int l = 1; l <= n; l++) {
                    if (a.mp[i][j] == b.mp[k][l]) {
                        dp[i][j][k][l] =
                            std::min(dp[i - 1][j - 1][k - 1][l - 1],
                                     std::min(dp[i - 1][j][k - 1][l],
                                              dp[i][j - 1][k][l - 1]));

                        dp[i][j][k][l]++;
                        ans = std::max(ans, dp[i][j][k][l]);
                    }
                }
            }
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