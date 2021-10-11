#include <cstdio>
#include <iostream>

const int MAX_N = 5000050;

int dp[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    std::string s, a;
    std::cin >> s;
    int n = s.size();

    a[0] = a[1] = '#';
    for (int i = 0; i < n; i++) {
        a[i * 2 + 2] = s[i];
        a[i * 2 + 3] = '#';
    }
    n = n * 2 + 2;
    a[n] = 0;

    int l = 0, r = 0, mid = 0, ans = 0;

    for (; l <= n; l++) {
        if (l <= r) {
            dp[l] = std::min(dp[mid * 2 - l], r - l + 1);
        }
        while (a[l - dp[l]] == a[l + dp[l]]) {
            dp[l]++;
        }

        if (dp[l] + l > r) {
            r = dp[l] - l - 1;
            mid = l;
        }
        if (dp[l] > ans) {
            ans = dp[l];
        }
    }

    std::cout << ans - 1 << '\n';

    return 0;
}
