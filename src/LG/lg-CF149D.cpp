#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

const int MAX_N = 705;
const int MOD = 1000000007;

int p[MAX_N];
int dp[MAX_N][MAX_N][3][3];

void dfs(int l, int r);

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::stack<int> stk;
    std::cin >> s;

    for (int i = 1; i <= s.size(); i++) {
        if (s[i - 1] == '(') {
            stk.push(i);
        } else {
            p[i] = stk.top();
            p[stk.top()] = i;
            stk.pop();
        }
    }

    dfs(1, s.size());

    int ans = 0;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            ans += dp[1][s.size()][i][j];
            ans %= MOD;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

void dfs(int l, int r) {
    if (r == l + 1) {
        dp[l][r][0][1] = dp[l][r][0][2] = dp[l][r][1][0] = dp[l][r][2][0] = 1;
    } else if (p[l] == r) {
        dfs(l + 1, r - 1);

        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                if (i != 1) {
                    dp[l][r][1][0] += dp[l + 1][r - 1][i][j];
                    dp[l][r][1][0] %= MOD;
                }
                if (i != 2) {
                    dp[l][r][2][0] += dp[l + 1][r - 1][i][j];
                    dp[l][r][2][0] %= MOD;
                }
                if (j != 1) {
                    dp[l][r][0][1] += dp[l + 1][r - 1][i][j];
                    dp[l][r][0][1] %= MOD;
                }
                if (j != 2) {
                    dp[l][r][0][2] += dp[l + 1][r - 1][i][j];
                    dp[l][r][0][2] %= MOD;
                }
            }
        }
    } else {
        dfs(p[l] + 1, r);
        dfs(l, p[l]);
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                for (int k = 0; k <= 2; k++) {
                    for (int m = 0; m <= 2; m++) {
                        if (j == k and (j == 1 or j == 2)) {
                            continue;
                        }
                        dp[l][r][i][m] += 1ll * dp[p[l] + 1][r][k][m] *
                                          dp[l][p[l]][i][j] % MOD;
                        dp[l][r][i][m] %= MOD;
                    }
                }
            }
        }
    }
}
