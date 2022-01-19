#include <cstdio>
#include <cstring>
#include <iostream>

const int MAX_N = 10000050;

int tree[MAX_N][26], cnt[MAX_N], dp[MAX_N];
int sum, ans;

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        int c = 0;
        std::string s;
        std::cin >> s;

        for (auto it = s.rbegin(); it != s.rend(); it++) {
            if (!tree[c][*it - 'a']) {
                tree[c][*it - 'a'] = ++sum;
            }
            c = tree[c][*it - 'a'];
        }
        cnt[c]++;
    }

    for (int i = sum; i >= 0; i--) {
        dp[i] = cnt[i];
        int mx = 0, sx = 0;

        for (int j = 0; j < 26; j++) {
            if (cnt[tree[i][j]]) {
                dp[i]++;
                if (dp[tree[i][j]] - 1 > mx) {
                    sx = mx;
                    mx = dp[tree[i][j]] - 1;
                } else if (dp[tree[i][j]] - 1 > sx) {
                    sx = dp[tree[i][j]] - 1;
                }
            }
        }

        dp[i] += mx;
        ans = std::max(ans, dp[i] + sx);
    }

    std::cout << ans << '\n';

    return 0;
}