#include <cstring>
#include <iostream>

const int MAX_N = 505;

int dp1[MAX_N][MAX_N], dp2[MAX_N][MAX_N], num[MAX_N], sum[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);

    int n, max = 0, min = 0x7f7f7f7f;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> num[i];
        num[i + n] = num[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + num[i];
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= 2 * n - l + 1; i++) {
            int j = i + l - 1;
            dp1[i][j] = 0x7f7f7f7f, dp2[i][j] = 0;
            for (int k = i; k < j; k++) {
                dp1[i][j] = std::min(dp1[i][j], dp1[i][k] + dp1[k + 1][j]);
                dp2[i][j] = std::max(dp2[i][j], dp2[i][k] + dp2[k + 1][j]);
            }
            dp1[i][j] += (sum[j] - sum[i - 1]);
            dp2[i][j] += (sum[j] - sum[i - 1]);
        }
    }

    for (int i = 1; i <= n; i++) {
        min = std::min(min, dp1[i][i + n - 1]);
        max = std::max(max, dp2[i][i + n - 1]);
    }

    std::cout << min << '\n' << max << '\n';

    return 0;
}